#define GLAD_BIN

#include "mapi/common.h"
#include "mapi/System.h"
#include "mapi/Factory.h"
#include "mapi/CameraOrbital.h"
#include "mapi/Object3D.h"
#include "mapi/Light.h"
#include "mapi/OrbitalLight.h"
using namespace std;

int main() {
    // 1.- Inicializar el backend OpenGL 4.0 y el input manager
    Factory::setSelectedGraphicsBackend(GraphicsBackend::GL4);
    Factory::setSelectedInputBackend(InputBackend::GLFW);

    // 2.- Inicializar la clase System
    System::initSystem();

    // 3.- Camara Orbital
    CamaraOrbital* camera = new CamaraOrbital(
        projectionType_e::PERSPECTIVE,
        glm::vec3(0.0f, 15.0f, 25.0f),      // position inicial
        glm::vec3(0.0f, 1.0f, 0.0f),        // up
        glm::vec3(0.0f, 0.0f, 0.0f),        // lookAt
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),  // centro de rotación
        25.0f,                              // radio
        0.5f                                // speed de rotación
    );

	// 4.- Agregar la cámara al mundo y activarla
    System::getWorld()->addCamera(camera);
    System::getWorld()->setActiveCamera(0);


    // 4) Ambiente
    System::getWorld()->setAmbient(0.1f);

    // 5) Luces
    Light* pointLight = new Light(
        Light::Type::POINT,
        glm::vec4(1.0f, 0.9f, 0.7f, 1.0f),
        glm::vec4(0.0f, 2.0f, 5.0f, 1.0f)
    );
    System::getWorld()->addLight(pointLight);

    // 6) Totem
    Object3D* totem = new Object3D(
        "data/column/column.msh",               // Archivo MSH
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),      // Posición
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),      // Rotación
        glm::vec4(0.01f, 0.01f, 0.01f, 1.0f)    // Escala
    );
    System::getWorld()->addObject(totem);

    // 7) Emisores de partículas

    // Emisor de humo
    Emitter* smoke = new Emitter(
        "data/column/smoke.msh",
        glm::vec4(0.0f, 8.0f, 0.0f, 1.0f), true,
        5.0f, 10.0f,
        1.0f, 5.0f,
        glm::vec3(-0.1f, 1.0f, -0.1f), glm::vec3(0.1f, 4.0f, 0.1f),
        30.0f, 60.0f,
        0.05f, 0.1f,
        glm::vec4(1.0f), glm::vec4(1.0f)
    );
    System::getWorld()->addEmitter(smoke);

    // Emisor de Fuego
    Emitter* fire = new Emitter(
        "data/column/flame.msh",
        glm::vec4(0.0f, 8.0f, 0.0f, 1.0f), true,
        10.0f, 25.0f,
        0.5f, 0.5f,
        glm::vec3(-1.0f, 5.0f, -1.0f), glm::vec3(1.0f, 10.0f, 1.0f),
        0.0f, 0.0f,
        0.025f, 0.1f,
        glm::vec4(1.0f), glm::vec4(1.0f) 
    );
    System::getWorld()->addEmitter(fire);

    // 7) Loop
    System::mainLoop();

    return 0;
}

