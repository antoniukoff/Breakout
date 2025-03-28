#pragma once
#include "component_manager.h"
#include <queue>

/**
 * @class registry
 *
 * @brief Entity Component System (ECS) registry class; responsible for managing entities and their components
 *
 * @tparam Cs Components
 */
template<typename ... Cs>
class registry
{
private:
	static constexpr size_t m_registered_components = sizeof...(Cs); // Number of registered components

	using bit_mask = std::bitset<m_registered_components>;
	using signature_map = std::unordered_map<bit_mask, std::vector<entity_id>>;

private:
	std::tuple<component_manager<Cs>...> m_component_pools; // Tuple of component pools
	std::queue<entity_id> m_available_ids; // Stores available ids
	std::vector<bit_mask> m_entities_to_signatures; // Maps entities to their assigned components
	signature_map m_entities; // Maps component signatures to entities containing them them

public:
	registry()
		: m_entities_to_signatures(g_max_entities)
	{
		// Populate the queue with entityIDs
		for (size_t i = 0; i < g_max_entities; ++i)
		{
			m_available_ids.push(i);
		}
	}

	/// Generates new Entity ID
	entity_id create_entity()
	{
		if (m_available_ids.empty())
		{
			return -1;
		}

		size_t new_id = m_available_ids.front();
		m_available_ids.pop();
		return new_id;
	}

	/**
	 * @brief Deletes entities data from component pools and frees the entity index to be reused
	 * @param e
	*/
	void destroy(entity_id e)
	{
		reflecs::constexpr_loop::execute<m_registered_components, remove_entity_wrapper>(this, e, m_entities_to_signatures[e]);
		m_available_ids.push(e);
	}

	/**
	* @brief Fetches entity data for a specified set of components
	*
	* @tparam C Current component type used in creating a handle
	* @tparam ...Cs Remaining Components
	*/
	template<typename C, typename ... Cs>
	auto unpack(entity_id e_id)
	{
		// Recusively concatenates a tuple at compile-time until the size of the tail hits 0
		if constexpr (sizeof...(Cs) < 1)
		{
			return std::make_tuple(create_handle<C>(e_id));
		}
		else
		{
			return std::tuple_cat(std::make_tuple(create_handle<C>(e_id)), unpack<Cs...>(e_id));
		}
	}

	/**
	* @brief Adds the component data to the fields' pools
	*
	* @tparam C - Component
	*
	* @param e_id - Entity's id
	* @param args - Plain component data
	*/
	template<typename C, typename ... Args>
	void add(entity_id e_id, Args&& ... args)
	{
		if (e_id == -1)
		{
			return;
		}

		component_manager<C>& mgr = retrieve_pool<C>();

		mgr.add(e_id, std::forward<Args>(args)...);

		update_mask<C>(e_id, true);
	}

	void reset()
	{
		m_entities_to_signatures.clear();
		m_entities_to_signatures.resize(g_max_entities);
		// Populate the queue with entityIDs
		std::queue<entity_id> new_queue;
		for (size_t i = 0; i < g_max_entities; ++i)
		{
			new_queue.push(i);
		}
		std::swap(m_available_ids, new_queue);
		m_entities.clear();
		reflecs::constexpr_loop::execute<m_registered_components, reset_wrapper>(this);
	}

	template<typename C>
	bool has(entity_id e_id)
	{
		component_manager<C>& mgr = retrieve_pool<C>();
		return mgr.contains(e_id);
	}

	/**
	* @brief Function to iterate over entity vectors
	*		 that have the specified set of components.
	*
	* @tparam ... Cs  Components
	* @tparam F Function type
	* @param function Function object (lambda/functor)
	*/
	template<typename ... Cs, typename F>
	void for_each(F&& function)
	{
		static auto target_mask = create_signature<Cs...>();

		for (auto& [bit_mask, entity_vec] : m_entities)
		{
			if ((bit_mask & target_mask) != target_mask)
			{
				continue;
			}
			for (auto entity_id : entity_vec)
			{
				function(entity_id, create_handle<Cs>(entity_id)...);
			}
		}
	}

	/**
	 * @brief Removes entity from the component pool
	 * @tparam C Component
	 * @param e_id Entity's ID
	*/
	template<typename C>
	void remove(entity_id e_id)
	{
		component_manager<C>& mgr = retrieve_pool<C>();
		mgr.remove(e_id);

		update_mask<C>(e_id, false);
	}

private:
	/**
	 * @brief Removes/Adds component's ID to entity's component bit mask
	 * @tparam C Component
	 * @param e_id Entity's ID
	 * @param add Set or unset the bit
	*/
	template<typename C>
	void update_mask(entity_id e_id, bool add)
	{
		auto s = m_entities_to_signatures[e_id];
		m_entities[s].erase(std::remove(m_entities[s].begin(), m_entities[s].end(), e_id), m_entities[s].end());
		s.set(reflecs::type_utils::get_component_type_id<C, Cs...>(), add);
		m_entities_to_signatures[e_id] = s;
		m_entities[s].push_back(e_id);
	}

	/**
	* @brief Creates a bit mask for the given set of components
	*
	* @tparams ...Cs Components
	*/
	template<typename ... Ts>
	constexpr auto create_signature()
	{
		bit_mask signatures;

		(signatures.set(reflecs::type_utils::get_component_type_id<Ts, Cs...>()), ...); // fold expresion since C++ 17; applies same operation for all template aruments 
		return signatures;
	}

	/**
	* @brief Creates a handle for a components to access its fields.
	* Component handle needs to be partially specialized and defined to work
	*
	* @tparam C Component
	*/
	template<typename C>
	component_handle<C> create_handle(entity_id e_id)
	{
		component_manager<C>& mgr = retrieve_pool<C>();

		return mgr.retrieve(e_id);
	}

	/**
	 * @brief Returns a pointer to the pool of a component's type
	 * @tparam C Component
	 * @return Component pool pointer
	*/
	template<typename C>
	component_manager<C>& retrieve_pool()
	{
		return std::get<component_manager<C>>(m_component_pools);
	}

	/**
	 * @brief Compile-time helper method to remove the entity from assigned pool
	 * @tparam Position of a bit in a bit_mask
	 * @param e_id Entity's ID
	 * @param bit_mask Entity's bit mask
	*/
	template<size_t index>
	void remove_entity_from_pool(entity_id e_id, bit_mask& bit_mask)
	{
		if (bit_mask[index])
		{
			remove<reflecs::type_utils::component_type_at_index<index, Cs...>>(e_id);
		}
	}

	/**
	 * @brief Dummy class with a defined functor to invoke the remove_entity_from_pool()
	 * @tparam index Position of a bit in a bit_mask
	*/
	template<size_t index>
	struct remove_entity_wrapper
	{
		void operator()(registry* parent, entity_id e_id, bit_mask& bit_mask)
		{
			parent->remove_entity_from_pool<index>(e_id, bit_mask);
		}
	};

	/**
	 * @brief Compile-time helper method to remove the entity from assigned pool
	 * @tparam Position of a bit in a bit_mask
	 * @param e_id Entity's ID
	 * @param bit_mask Entity's bit mask
	*/
	template<size_t index>
	void reset_pools()
	{
		auto& component_pool = std::get<index>(m_component_pools);
		component_pool.reset();
	}

	/**
	 * @brief Dummy class with a defined functor to invoke the remove_entity_from_pool()
	 * @tparam index Position of a bit in a bit_mask
	*/
	template<size_t index>
	struct reset_wrapper
	{
		void operator()(registry* parent)
		{
			parent->reset_pools<index>();
		}
	};
};

