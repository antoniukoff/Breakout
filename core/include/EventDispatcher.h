#pragma once
#include "Event.h"
#include <functional>
#include <vector>
#include <memory>
#include <algorithm>
#include <utility>
#include <iostream>
	
class EventDispatcher
{
	using EventCallback = std::function<void(const Event&)>;

public:
	EventDispatcher();
	~EventDispatcher();

	template<typename EventType>
	void subscribe(const EventCallback& callback);

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
private:
	std::unordered_map<size_t, std::vector<EventCallback>> m_listeners;

	std::vector<std::pair<size_t, std::unique_ptr<Event>>> m_pending_events;

	/// used for handling occasions when pending events dispatch other events
	/// that recursivey are added to the queue 
	std::vector<std::pair<size_t, std::unique_ptr<Event>>> m_processing_events;
};

template<typename EventType>
void EventDispatcher::subscribe(const EventCallback& callback)
{
	m_listeners[typeid(EventType).hash_code()].push_back(callback);
}

template<typename EventType>
void EventDispatcher::dispatch(const EventType& event)
{
	/// Find if event typeid in the map
	size_t event_id = typeid(EventType).hash_code();
	if (!m_listeners.contains(event_id))
	{
		return;
	}

	m_pending_events.push_back({ event_id, std::make_unique<EventType>(event) });
}

