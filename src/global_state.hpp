#pragma once

#include "event_manager.hpp"

struct GlobalState {
    EventManager event_manager;

    GlobalState();
    ~GlobalState();
};

extern GlobalState G;
