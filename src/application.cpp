#include "application.hpp"

#include "global_state.hpp"

#include <algorithm>
#include <iostream>

Application::Application()
{
    int const num_windows = 2;

    for (auto i = 0; i < num_windows; i++) {
        windows_.push_back(std::make_unique<Window>(std::to_string(i)));
    }

    // Subscribe to window events
    G.event_manager.subscribe<WindowResizedEvent>([](auto const& event) {
        std::cout << "Window " << event.window->get_title() << " resized to ("
                  << event.new_width << ", " << event.new_height << ").\n";
    });

    G.event_manager.subscribe<WindowClosedEvent>([this](auto const& event) {
        auto window =
            std::ranges::find_if(windows_, [event](auto const& window) {
                return event.window == window.get();
            });
        if (window != windows_.end()) {
            windows_.erase(window);
        }

        if (windows_.size() == 0) {
            should_exit_ = true;
        }
    });
}

void Application::start()
{
    while (!should_exit_) {
        for (auto& window : windows_) {
            window->update();
        }
    }

    std::cout << "Exiting...\n";
}
