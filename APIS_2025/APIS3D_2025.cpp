#define GLAD_BIN

#include "mapi/common.h"
#include "mapi/System.h"
#include "mapi/Factory.h"
#include "mapi/TrianguloRot.h"
using namespace std;

int main() {
    // 1.- Inicializar el backend de la clase “FactoryEngine” para poder usar OpenGL 4.0 y el input manager por defecto.
    Factory::setSelectedGraphicsBackend(GraphicsBackend::GL4); // Cambiado a OpenGL 4.0
    Factory::setSelectedInputBackend(InputBackend::GLFW);

    // 2.- Inicializar la clase System
    System::initSystem();

    // 3.- Crear un objeto de tipo “TrianguloRot” en la posición <0,0,0>, y añadirlo al sistema
    auto* triangulo = new TrianguloRot();
    triangulo->setPosition(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    // 4.- Crear un objeto “World” y añadir el triángulo creado anteriormente
    auto* world = new World();
    world->addObject(triangulo);

    // 5.- Añadir el objeto World a System
    System::setWorld(world);

    // 6.- Ejecutar el mainLoop del sistema, hasta que el usuario presione la tecla “e”
    System::mainLoop();

    return 0;
}

