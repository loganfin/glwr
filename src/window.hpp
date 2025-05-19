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

    std::string get_title() const;

    // TODO: Future window actions
    // set_window_title(std::string const& title);
    // set_window_hint(std::string const& hint);
    // set_window_icon(std::filesystem::path const& icon);
    // request_attention();
    // bool get_minimized() const;
    // bool get_width() const;
    // bool get_height() const;

private:
    // TODO: Hide this to make GLFW a private dependency
    GLFWwindow* window_ = nullptr;
};

struct WindowClosedEvent : public Event {
    Window const* window;
};

struct WindowResizedEvent : public Event {
    Window const* window;
    int new_width;
    int new_height;
};

// TODO: Future events
// struct WindowMaximizedEvent : public Event {};
// struct WindowScaleChangedEvent : public Event {};
// struct WindowPositionChangedEvent : public Event {};
// struct WindowMinimizedEvent : public Event {};
// struct WindowMaximizedEvent : public Event {};
// struct WindowFocusedEvent: public Event {};
