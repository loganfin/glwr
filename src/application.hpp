#pragma once

#include "window.hpp"

class Application {
public:
    Application();

    void start();

private:
    bool should_exit_ = false;
    Window window_;
};
