#include "application.hpp"

#include "global_state.hpp"

#include <iostream>

Application::Application() : window_{"glrw"}
{
    // Subscribe to window events
    G.event_manager.subscribe<WindowResizedEvent>([](auto const& event) {
        std::cout << "Window " << event.window.get_title() << " resized to ("
                  << event.new_width << ", " << event.new_height << ").\n";
    });

    G.event_manager.subscribe<WindowClosedEvent>([this](auto const& event) {
        if (&event.window == &window_) {
            should_exit_ = true;
        }
    });
}

void Application::start()
{
    while (!should_exit_) {
        window_.update();
        update();
    }

    std::cout << "Exiting...\n";
}

void Application::update()
{
}
