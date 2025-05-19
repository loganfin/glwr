#include "window.hpp"

#include "global_state.hpp"

#include <iostream>
#include <stdexcept>

namespace {

void on_glfw_window_close(GLFWwindow* glfw_window);

} // namespace

Window::Window(std::string const& title, uint32_t width, uint32_t height)
{
    glfwInit();

    window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!window_) {
        throw std::runtime_error("Failed to create GLFW window!");
    }

    // Set callbacks
    glfwSetWindowCloseCallback(window_, on_glfw_window_close);

    glfwMakeContextCurrent(window_);
    glfwSetWindowUserPointer(window_, this);
}

Window::~Window()
{
    glfwDestroyWindow(window_);
    glfwTerminate();
}

void Window::update()
{
    glfwSwapBuffers(window_);
    glfwPollEvents();
}

namespace {

void on_glfw_window_close(GLFWwindow* glfw_window)
{
    std::cout << "Publishing WindowClosedEvent...\n";
    auto* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
    G.event_manager.publish<WindowClosedEvent>(*window);
}

} // namespace
