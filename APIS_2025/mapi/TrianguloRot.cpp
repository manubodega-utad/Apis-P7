#include "TrianguloRot.h"

// Constructor
TrianguloRot::TrianguloRot() {
    // Crear la malla
    auto* mesh = new Mesh3D();

    // Coordenadas de los vértices del triángulo
    mesh->addVertex({ glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f) }); // Vértice 1
    mesh->addVertex({ glm::vec4(0.5f, -0.5f, 0.0f, 1.0f) });  // Vértice 2
    mesh->addVertex({ glm::vec4(0.0f, 0.5f, 0.0f, 1.0f) });   // Vértice 3

    mesh->addTriangle(0, 1, 2);

    // Material
    Material* material = Factory::getNewMaterial();

    // Cargar los shaders en el material
    vector<string> shaderFiles = {
        "vertex_shader.vert",
        "fragment_shader.frag"
    };
    material->loadPrograms(shaderFiles);

    // Asignar el material a la malla
    mesh->setMaterial(material);

    // Asignar la malla
    setMesh(mesh);
}

// Destructor
TrianguloRot::~TrianguloRot() {
    delete getMesh();
}

void TrianguloRot::loadDataFromFile(const std::string& file) {
    // TODO
}

// Actualización del triángulo
void TrianguloRot::step(double deltaTime) {
    // Rotar
    glm::vec4 currentRotation = getRotation();
    currentRotation.y += glm::radians(90.0f) * deltaTime;
    setRotation(currentRotation);

    // Llamar a computeModelMatrix()
    computeModelMatrix();

    // Verificar tecla E mediante glfwGetKey
    /*
    if (System::inputManager->isPressed(GLFW_KEY_E)) {
        System::exit();
    }*/
    //LO HAGO AQUI A PELO HASTA QUE SE DESARROLLE EL CALLBACK DE GLFWINPUTMANAGER
    if (auto* glRender = dynamic_cast<GL1Render*>(System::render)) {
        GLFWwindow* window = glRender->getWindow();
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            System::exit();
        }
    }
}
