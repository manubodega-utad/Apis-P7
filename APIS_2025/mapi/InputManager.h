#pragma once
#include "common.h"

typedef struct mouseState_t {
    double x;
    double y;
    std::map<int, bool> button;
} mouseState_t;

class InputManager {
protected:
    std::map<int, bool> keyState;

public:
    static mouseState_t mouseState;
    // Constructor
    InputManager() = default;

    // Destructor
    virtual ~InputManager() = default;

    // Métodos
    virtual void init() = 0;
    virtual bool isPressed(int key) const;
    static bool isMousePressed(int button);
    static double getMouseX();
    static double getMouseY();
};
