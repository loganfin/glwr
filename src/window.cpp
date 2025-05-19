#include "window.hpp"

#include "global_state.hpp"

#include <iostream>
#include <stdexcept>

namespace {

void on_glfw_window_closed(GLFWwindow* glfw_window);
void on_glfw_window_resized(
    GLFWwindow* glfw_window,
    int new_width,
    int new_height
);

} // namespace

Window::Window(std::string const& title, uint32_t width, uint32_t height)
{
    window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!window_) {
        throw std::runtime_error("Failed to create GLFW window!");
    }

    // Set callbacks
    glfwSetWindowCloseCallback(window_, on_glfw_window_closed);
    glfwSetWindowSizeCallback(window_, on_glfw_window_resized);

    glfwSetWindowUserPointer(window_, this);
}

Window::~Window()
{
    glfwDestroyWindow(window_);
}

void Window::update()
{
    glfwMakeContextCurrent(window_);
    glfwSwapBuffers(window_);
    glfwPollEvents();
}

std::string Window::get_title() const
{
    return {glfwGetWindowTitle(window_)};
}

namespace {

Window* get_window(GLFWwindow* glfw_window);

void on_glfw_window_closed(GLFWwindow* glfw_window)
{
    std::cout << "Publishing WindowClosedEvent...\n";
    auto* window = get_window(glfw_window);
    G.event_manager.publish<WindowClosedEvent>(window);
}

void on_glfw_window_resized(
    GLFWwindow* glfw_window,
    int new_width,
    int new_height
)
{
    std::cout << "Publishing WindowResizedEvent...\n";
    auto* window = get_window(glfw_window);
    G.event_manager.publish<WindowResizedEvent>(window, new_width, new_height);
}

Window* get_window(GLFWwindow* glfw_window)
{
    return static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
}

} // namespace
