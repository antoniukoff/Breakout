#pragma once
#include "Event.h"
#include <functional>
#include <vector>

class EventDispatcher
{
	using EventCallback = std::function<void(const Event&)>;

public:
	EventDispatcher();
	~EventDispatcher();

	template<typename EventType>
	void subscribe(const EventCallback& callback);

	template<typename EventType>
	void dispatch(const EventType& event);

private:
	std::unordered_map<int, std::vector<EventCallback> > m_listeners;
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
	int event_id = typeid(EventType).hash_code();
	if (!m_listeners.contains(event_id))
	{
		return;
	}
	auto& listener_vec = m_listeners.at(event_id);
	for (auto& callback : listener_vec)
	{
		callback(event);
	}
}

