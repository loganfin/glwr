#pragma once

#include "window.hpp"

#include <vector>
#include <memory>

class Application {
public:
    Application();

    void start();

private:
    bool should_exit_ = false;
    std::vector<std::unique_ptr<Window>> windows_;
};
