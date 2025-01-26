// GL4Render.cpp
#include "GL4Render.h"

// Constructor
GL4Render::GL4Render(int width, int height) : GL1Render(width, height)
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
}

// Destructor
GL4Render::~GL4Render()
{
    for (auto& pair : boList)
    {
        glDeleteBuffers(1, &pair.second.vbo);
        glDeleteBuffers(1, &pair.second.idxbo);
        glDeleteVertexArrays(1, &pair.second.id);
    }
}

// Métodos
void GL4Render::setupObject(Object* obj) {
    if (!obj || !obj->getMesh()) {
        std::cerr << "[GL4Render] Error: Objeto o Mesh no válido en setupObject\n";
        return;
    }

    Mesh3D* mesh = obj->getMesh();
    int meshID = mesh->getMeshId();

    // Verificar si ya existe el buffer object
    if (boList.find(meshID) != boList.end()) {
        std::cerr << "[GL4Render] Advertencia: El Buffer Object ya existe para este MeshID\n";
        return;
    }

    // Crear buffer objects
    boIDS_t bo = { 0, 0, 0 };
    glGenVertexArrays(1, &bo.id);
    glBindVertexArray(bo.id);

    // Configurar Vertex Buffer Object (VBO)
    glGenBuffers(1, &bo.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, bo.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * mesh->getVertexList()->size(),
        mesh->getVertexList()->data(), GL_STATIC_DRAW);

    // Configurar Index Buffer Object (IBO)
    glGenBuffers(1, &bo.idxbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.idxbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(glm::uint32) * mesh->getTriangleIdxList()->size(),
        mesh->getTriangleIdxList()->data(), GL_STATIC_DRAW);

    // Almacenar el buffer object en el mapa
    boList[meshID] = bo;
}

// Implementación de removeObject
void GL4Render::removeObject(Object* obj) {
    if (!obj || !obj->getMesh()) {
        std::cerr << "[GL4Render] Error: Objeto o Mesh no válido en removeObject\n";
        return;
    }

    Mesh3D* mesh = obj->getMesh();
    int meshID = mesh->getMeshId();

    // Buscar y eliminar el buffer object
    auto it = boList.find(meshID);
    if (it != boList.end()) {
        glDeleteBuffers(1, &it->second.vbo);
        glDeleteBuffers(1, &it->second.idxbo);
        glDeleteVertexArrays(1, &it->second.id);
        boList.erase(it);
    }
}

// Implementación de drawObjects
void GL4Render::drawObjects(const vector<Object*>* objs)
{
    if (!objs) return;

    for (const auto& obj : *objs)
    {
        if (!obj) continue;

        Mesh3D* mesh = obj->getMesh();
        if (!mesh) continue;

        int meshID = mesh->getMeshId();

        auto it = boList.find(meshID);
        if (it == boList.end())
        {
            std::cerr << "[GL4Render] ERROR: Buffer objects para meshID " << meshID << " no encontrados.\n";
            continue;
        }

        boIDS_t boIDs = it->second;

        // Vincular el VAO
        glBindVertexArray(boIDs.id);

        // Obtener el material y activar el shader correspondiente
        Material* material = mesh->getMaterial();
        if (material)
        {
            material->prepare(); // Asegúrate de que 'prepare' activa el shader y setea los uniforms
        }

        // Dibujar el triángulo
        glDrawElements(GL_TRIANGLES, mesh->getTriangleIdxList()->size(), GL_UNSIGNED_INT, 0);

        // Desvincular el VAO
        glBindVertexArray(0);
    }

    // Swap de buffers y poll de eventos
    glfwSwapBuffers(getWindow());
    glfwPollEvents();
}
