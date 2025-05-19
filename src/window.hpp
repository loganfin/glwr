#pragma once

#include "event.hpp"

#include "GLFW/glfw3.h"

#include <string>

class Window {
public:
    explicit Window(
        std::string const& title,
        uint32_t width = 1280,
        uint32_t height = 720
    );

    ~Window();

    void update();

private:
    // TODO: Convert to unique pointer to make GLFW a private dependency
    GLFWwindow* window_ = nullptr;
};

struct WindowClosedEvent : public Event {
    Window const& window;
};
