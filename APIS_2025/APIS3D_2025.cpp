#define GLAD_BIN

#include "mapi/common.h"
#include "mapi/System.h"
#include "mapi/Factory.h"
#include "mapi/CameraFPS.h"
#include "mapi/Object3D.h"
#include "mapi/Light.h"
using namespace std;

int main() {
    // 1.- Inicializar el backend de la clase “FactoryEngine” para poder usar OpenGL 4.0 y el input manager por defecto.
    Factory::setSelectedGraphicsBackend(GraphicsBackend::GL4);
    Factory::setSelectedInputBackend(InputBackend::GLFW);

    // 2.- Inicializar la clase System
    System::initSystem();

    // 3.- Crear un objeto de tipo Camera
    CameraFPS* camera = new CameraFPS(
        projectionType_e::PERSPECTIVE,
        glm::vec3(0.6f, 1.0f, 0.9f),          // position
        glm::vec3(0.0f, 1.0f, 0.0f),          // up
        glm::vec3(-0.54f, -0.93f, -1.0f),     // lookAt
        1.0f,
        0.01f
    );

	// 4.- Agregar la cámara al mundo y establecerla como cámara activa
    System::getWorld()->addCamera(camera);
    System::getWorld()->setActiveCamera(0);


    // 4) Ambient (P5)
    System::getWorld()->setAmbient(0.2f);

    // 5) UNA LUZ direccional blanca (P5 punto 5)
    Light* dirLight = new Light();
    dirLight->setEnable(true);
    dirLight->setType(Light::Type::DIRECTIONAL);
    dirLight->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    dirLight->setDirection(glm::vec4(0.0f, 1.0f, -1.0f, 0.0f)); // w=0

    System::getWorld()->addLight(dirLight);

    // 6) Cargar Feng_Shui.msh (P5)
    auto dataFile = "data/feng_shui/Feng_Shui.msh";
    Object3D* objeto = new Object3D(dataFile);

    // Escala del enunciado
    objeto->setScale(glm::vec4(0.005f, 0.005f, 0.005f, 1.0f));
    objeto->computeModelMatrix();

    System::getWorld()->addObject(objeto);

    // 7) Loop
    System::mainLoop();

    return 0;
}

