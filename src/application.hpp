#pragma once

#include "window.hpp"

class Application {
public:
    Application();

    void start();

    void update();

private:
    bool should_exit_ = false;
    Window window_;
};
