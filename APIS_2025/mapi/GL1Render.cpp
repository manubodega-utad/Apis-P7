#include "GL1Render.h"
#include <iostream>

// Constructor
GL1Render::GL1Render(int width, int height) : Render() {
    this->width = width;
    this->height = height;
    this->window = nullptr;
}

// Destructor
GL1Render::~GL1Render() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

// Getters
int GL1Render::getWidth() const {
    return width;
}

int GL1Render::getHeight() const {
    return height;
}

GLFWwindow* GL1Render::getWindow() const {
    return window;
}

//Setters
void GL1Render::setWidth(int newWidth) {
    width = newWidth;
}

void GL1Render::setHeight(int newHeight) {
    height = newHeight;
}

// Métodos
void GL1Render::init() {
    if (glfwInit() != GLFW_TRUE) {
        cout << "Error GLFWINIT " << __FILE__ << ":" << __LINE__ << endl;
    }
    else {
        // Crear ventana
        window = glfwCreateWindow(width, height, "APIS Demo1", NULL, NULL);
        if (!window) {
            cout << "Error WINDOW " << __FILE__ << ":" << __LINE__ << endl;
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPos(window, 0.0, 0.0);
        gladLoadGL(glfwGetProcAddress);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    }
}

void GL1Render::setupObject(Object* obj)
{
    if (!obj) return;

    // Validar que el objeto tiene malla
    if (!obj->getMesh()) {
        std::cerr << "[Render] Objeto sin malla, no se puede dibujar\n";
        return;
    }
}

void GL1Render::removeObject(Object* obj)
{
    if (!obj)
    {
        std::cerr << "[GL4Render] Error: Objeto no válido en removeObject\n";
        return;
    }
}

// Dibuja una lista de objetos en pantalla
void GL1Render::drawObjects(const std::vector<Object*>* objs) {
    // Limpiar buffer
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto& obj : *objs) {
        Mesh3D* mesh = obj->getMesh();
        if (!mesh) continue;

        auto vertexList = mesh->getVertexList();

        glm::mat4 model = obj->getModel();

        // Dibujar Triangulos
        glBegin(GL_TRIANGLES);
        for (auto v : *vertexList) {
            v.vPos = model * v.vPos;
            glVertex3f(v.vPos.x, v.vPos.y, v.vPos.z);
        }
        glEnd();

    }
}

void GL1Render::clearBuffers() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GL1Render::swapBuffers() {
    glfwPollEvents();
    glfwSwapBuffers(window);
}

bool GL1Render::isClosed() const {
    return glfwWindowShouldClose(window);
}