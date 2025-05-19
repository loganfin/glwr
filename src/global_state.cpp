#include "global_state.hpp"

#include "GLFW/glfw3.h"

#include <stdexcept>

GlobalState G;

GlobalState::GlobalState()
{
    if (!glfwInit()) {
        throw std::runtime_error{"Failed to initialize GLFW"};
    }
}

GlobalState::~GlobalState()
{
    glfwTerminate();
}
