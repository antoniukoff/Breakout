#pragma once

namespace reflecs::utils
{
	namespace internal
	{
		template<uint32_t Iter, template<uint32_t Idx> typename FunctionToExecuteWrapperClass, typename Parent, typename ... Args>
		struct for_each
		{
			template<uint32_t Idx>
			static void loop(Parent* parent, Args&& ... args)
			{
				if constexpr (Idx >= Iter)
				{
					return;
				}
				else
				{
					FunctionToExecuteWrapperClass<Idx> wrapper = FunctionToExecuteWrapperClass<Idx>();

					wrapper(parent, args...);

					for_each<Iter, FunctionToExecuteWrapperClass, Parent, Args ...>::template loop<Idx + 1>(parent, args...);
				}
			}
		};

		template<typename... Ts>
		struct type_list {};

		template<size_t Idx, typename List>
		struct get_type_at_index;

		/// Recursively get the desired type based on the index until it hits the 0th base case
		template<size_t Idx, typename Head, typename... Tail>
		struct get_type_at_index<Idx, type_list<Head, Tail...>>
		{
			using type = typename get_type_at_index<Idx - 1, type_list<Tail...>>::type;
		};

		/// Base case
		template<typename Head, typename... Tail>
		struct get_type_at_index<0, type_list<Head, Tail...>>
		{
			using type = Head;
		};
	}
	
	template<uint32_t Iter, template<uint32_t N> typename FunctionToExecuteWrapperClass, typename Parent, typename ... Args>
	inline void unroll_func(Parent* parent, Args&& ... args)
	{
		internal::for_each<Iter, FunctionToExecuteWrapperClass, Parent, Args...>::template loop<0>(parent, args...); // Index of starting Pos?
	}

	/// Get type of component at index
	template<size_t Idx, typename ... Ts>
	using cmp_type_at_index = typename internal::get_type_at_index<Idx, internal::type_list<Ts...>>::type;

	/**
	* @brief Returns the index of the component in the component list
	* @tparam C Component
	* @tparam Head First component in the list
	* @tparam Tail Remaining components
	* @param index Index of the component
	*/
	template<typename C, typename Head, typename ... Tail>
	constexpr size_t get_component_type_id(size_t index = 0)
	{
		if constexpr (std::is_same<C, Head>::value)
		{
			return index;
		}
		else
		{
			if constexpr (sizeof...(Tail) > 0)
			{
				return get_component_type_id<C, Tail...>(++index);
			}
			else
			{
				return -1; /// compile-error
			}
		}
	}
}

namespace reflecs::cmp_metadata
{
	/// Compile-Time field count
	template<typename ComponentType>
	struct get_member_count;

	/// Compile-Time field type based on its position within the struct
	template<typename ComponentType, size_t N>
	struct get_type;

	/// Helps identify the correct type of the pointer of the field within a class
	template<typename T, size_t N>
	struct get_pointer_to_member_type
	{
		using type = typename get_type<T, N>::type T::*;// pointer to member
	};

	/// Used to get the handle to the member within the pool
	template<typename T, size_t N>
	typename get_pointer_to_member_type<T, N>::type get_pointer_to_member() {};
}

template<typename T>
class cmp_handle;

#define ANNOTATE(ComponentName, MemberCount, ...)											\
																								\
		template<> struct reflecs::cmp_metadata::get_member_count<ComponentName>			\
		{																						\
			constexpr static uint32_t count = MemberCount;											\
		};																						\
																								\
		__VA_ARGS__																				\
																								\

#define DEFINE_COMPONENT_MEMBER(ComponentName, Index, MemberType, MemberName)				\
		template<> struct reflecs::cmp_metadata::get_type<ComponentName, Index>			\
		{																						\
			using type = MemberType;															\
		};																						\
																								\
	template<> inline typename reflecs::cmp_metadata::get_pointer_to_member_type<ComponentName, Index>::type   \
							   reflecs::cmp_metadata::get_pointer_to_member<ComponentName, Index>()   \
							   {																		    \
									return &ComponentName::MemberName;									    \
							   }																		    \
																											\


#define COMPONENT_HANDLE_ACCESSOR(index, type, name) \
		inline type& name() { return mgr.get_member_buffer<index>(e_id); }\


#define DEFINE_COMPONENT_HANDLE(ComponentType, ...)						\
	template<>															\
	class cmp_handle<ComponentType>										\
	{																	\
	public:																\
		reflecs::component_manager<ComponentType>& mgr;					\
		entity_id e_id;	     											\
																		\
	public:																\
		cmp_handle() = default;										    \
																		\
		cmp_handle(reflecs::component_manager<ComponentType>& mgr,	    \
						entity_id e_id)									\
			: mgr(mgr), e_id(e_id) {}									\
																		\
																		\
		__VA_ARGS__														\
	};

