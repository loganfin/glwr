#include "application.hpp"

#include "global_state.hpp"

#include <iostream>

Application::Application() : window_{"glwr"}
{
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
    }

    std::cout << "Exiting...\n";
}
