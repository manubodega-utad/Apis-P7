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

    // 5) LUCES
    // LUZ 1: Direccional (Blanco suave)
    Light* dirLight = new Light(
        Light::Type::DIRECTIONAL,
        glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),
        glm::vec4(0.0f, 1.0f, -1.0f, 0.0f)
    );
    System::getWorld()->addLight(dirLight);

    // LUZ 2: Puntual (Roja)
    Light* pointLight = new Light(
        Light::Type::POINT,
        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(0.0f),
        glm::vec3(5.0f, 2.0f, 0.0f),
        true, 0.05f
    );
    System::getWorld()->addLight(pointLight);

    // LUZ 3: Focal/Spot (Azul)
    Light* spotLight = new Light(
        Light::Type::SPOT,
        glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
        glm::vec4(-0.5f, -1.0f, -1.0f, 0.0f),
        glm::vec3(0.6f, 2.0f, 1.5f),
        true, 0.02f, 15.0f
    );
    System::getWorld()->addLight(spotLight);

    // 6) Cargar Feng_Shui.msh (P5)
    auto dataFile = "data/feng_shui/Feng_Shui.msh";
    Object3D* objeto = new Object3D(dataFile);
    objeto->setScale(glm::vec4(0.005f, 0.005f, 0.005f, 1.0f));
    objeto->computeModelMatrix();

    System::getWorld()->addObject(objeto);

    // 7) Loop
    System::mainLoop();

    return 0;
}

