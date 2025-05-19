#pragma once

#include "event_manager.hpp"

struct GlobalState {
    EventManager event_manager;
};

extern GlobalState G;
