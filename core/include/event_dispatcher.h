#pragma once

#include <functional>
#include <vector>
#include <memory>
	
#include "event_base.h"

class event_dispatcher
{
	using event_callback = std::function<void(const event_base&)>;

public:
	event_dispatcher();
	~event_dispatcher();

	template<typename EventType>
	void subscribe(const std::function<void(const EventType&)>& callback);

	/// Defer event updates
	inline void process_events()
	{
		/// process only this frames added events
		std::swap(m_pending_events, m_processing_events);
		for (auto& [event_id, pending_event] : m_processing_events)
		{
			auto& listeners = m_listeners.at(event_id);
			for (auto& callback : listeners)
			{
				callback(*pending_event);
			}
		}
		m_processing_events.clear(); 
	}
	template<typename EventType>
	void dispatch(const EventType& event);

private:
	std::unordered_map<size_t, std::vector<event_callback>> m_listeners;

	std::vector<std::pair<size_t, std::unique_ptr<event_base>>> m_pending_events;

	/// used for handling occasions when pending events dispatch other events
	/// that recursivey are added to the queue 
	std::vector<std::pair<size_t, std::unique_ptr<event_base>>> m_processing_events;
};

template<typename EventType>
void event_dispatcher::subscribe(const std::function<void(const EventType&)>&callback)
{
	auto wrapper = [callback](const event_base& event)
		{
			callback(reinterpret_cast<const EventType&>(event));
		};

	m_listeners[typeid(EventType).hash_code()].push_back(wrapper);
}

template<typename EventType>
void event_dispatcher::dispatch(const EventType& event)
{
	/// Find if event typeid in the map
	size_t event_id = typeid(EventType).hash_code();
	if (!m_listeners.contains(event_id))
	{
		return;
	}

	m_pending_events.push_back({ event_id, std::make_unique<EventType>(event) });
}

