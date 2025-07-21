#pragma once

#include "Window.h"

namespace Bob {

class Engine {
    public:
        Engine(void);
        ~Engine(void);

        Window *window;
};

} // namespace Bob
