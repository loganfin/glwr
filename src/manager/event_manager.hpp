#pragma once

#include "event.hpp"

#include <functional>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace {

// Events that don't define their own constructors require the base class to be
// initialized
template <typename EventType, typename... Args>
    requires(std::derived_from<EventType, Event>) &&
            std::is_aggregate_v<EventType>
EventType create_event_type(Args&&... args)
{
    return {{}, std::forward<Args>(args)...};
}

// This is used for Events that define their own constructors
template <typename EventType, typename... Args>
    requires(std::derived_from<EventType, Event>) &&
            (!std::is_aggregate_v<EventType>)
EventType create_event_type(Args&&... args)
{
    return {std::forward<Args>(args)...};
}

} // namespace

class EventManager {
public:
    template <typename EventType, typename... Args>
        requires(std::derived_from<EventType, Event>)
    void publish(Args&&... args)
    {
        auto event = create_event_type<EventType>(std::forward<Args>(args)...);

        auto& handlers = get_handlers<EventType>();

        for (auto& handler : handlers) {
            handler(event);
        }
    }

    template <typename EventType>
        requires(std::derived_from<EventType, Event>)
    void subscribe(std::function<void(EventType const&)> const& handler)
    {
        auto& handlers = get_handlers<EventType>();

        handlers.push_back([handler](Event const& event) {
            handler(static_cast<EventType const&>(event));
        });
    }

private:
    std::unordered_map<
        std::type_index,
        std::vector<std::function<void(Event const&)>>>
        handlers_;

    template <typename EventType>
        requires(std::derived_from<EventType, Event>)
    std::vector<std::function<void(Event const&)>>& get_handlers()
    {
        auto type = std::type_index(typeid(EventType));

        if (handlers_.find(type) == handlers_.end()) {
            handlers_[type] = std::vector<std::function<void(Event const&)>>{};
        }

        return handlers_[type];
    }
};
