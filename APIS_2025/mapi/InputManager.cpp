#include "InputManager.h"

mouseState_t InputManager::mouseState = { 0.0, 0.0, {} };

bool InputManager::isPressed(int key) const {
    auto it = keyState.find(key);
    if (it != keyState.end()) {
        return it->second;
    }
    return false;
}

bool InputManager::isMousePressed(int button) {
    auto it = mouseState.button.find(button);
    return it != mouseState.button.end() ? it->second : false;
}

double InputManager::getMouseX() {
    return mouseState.x;
}

double InputManager::getMouseY() {
    return mouseState.y;
}