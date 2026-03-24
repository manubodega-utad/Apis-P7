#pragma once
#include "mapi/common.h"

typedef struct  {
    double xPos;
    double yPos;
    std::map<int, bool> buttonState;
}mouseStats_t;

class GLFWKeyManager
{ 
    public:
        static inline GLFWwindow* window;//referencia a ventana de eventos
        static inline std::map<int, bool> keyboardState;
        static inline mouseStats_t mouseState;
        static void initKeyManager(GLFWwindow* window);
        static void setKMCursorPos(double x, double y); //mueve ratón a una posición
        static void windowKeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int
            mods);
        static void mousePosEvent(GLFWwindow* window, double xpos, double ypos);
        static void mouseButtonEvent(GLFWwindow* window, int button, int action, int mods);
        static void updateEvents();
};

