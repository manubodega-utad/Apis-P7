#define GLAD_BIN

#include "mapi/common.h"
#include "mapi/System.h"
#include "mapi/Factory.h"
#include "mapi/CameraKeyboard.h"
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

    // 3.- Camara Keyboard
    CameraKeyboard* camera = new CameraKeyboard(
        projectionType_e::PERSPECTIVE,
        glm::vec3(0.0f, 0.0f, 10.0f),   // posicion
        glm::vec3(0.0f, 1.0f, 0.0f),    // up
        glm::vec3(0.0f, 0.0f, 0.0f),    // lookAt
        5.0f                            // speed
    );

    System::getWorld()->addCamera(camera);
    System::getWorld()->setActiveCamera(0);


    // 4.- Ambiente
    System::getWorld()->setAmbient(0.4f);

    // 5.- Luces
    OrbitalLight* orbLight = new OrbitalLight(
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),  // centro
        10.0f,                              // radio
        0.8f                                // velocidad
    );
    orbLight->setColor(glm::vec4(1.0f, 0.95f, 0.8f, 1.0f));
    orbLight->setLinearAttenuation(0.01f);
    System::getWorld()->addLight(orbLight);

    // 6.- Skybox
    Object3D* skybox = new Object3D(
        "data/skybox1/skybox_obj.msh",
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(100.0f, 100.0f, 100.0f, 1.0f)
    );
    System::getWorld()->addObject(skybox);

    // 7.- Mono Suzanne
    Object3D* suzanne = new Object3D(
        "data/suzanne/glassSuzanne.msh",
        glm::vec4(3.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
    );
    System::getWorld()->addObject(suzanne);

    // 8.- Tetera metalica
    Object3D* teapot = new Object3D(
        "data/teapot/metalTeapot.msh",
        glm::vec4(-3.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
    );
    System::getWorld()->addObject(teapot);

    // 9.- Cubo ladrillo
    Object3D* normalCube = new Object3D(
        "data/normalMap/normalMapCubeObj.msh",
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
    );
    System::getWorld()->addObject(normalCube);

    // 10.- Loop
    System::mainLoop();

    return 0;
}
