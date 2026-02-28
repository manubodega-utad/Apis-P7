// GL4Render.cpp
#include "GL4Render.h"
#include "System.h"

// Constructor
GL4Render::GL4Render(int width, int height) : GL1Render(width, height)
{
}

// Destructor
GL4Render::~GL4Render()
{
    for (auto& pair : boList)
    {
        auto bo = pair.second;

        glDeleteBuffers(1, &bo.vbo);
        glDeleteBuffers(1, &bo.idxbo);
        glDeleteVertexArrays(1, &bo.id);
    }

    boList.clear();
}

// Métodos

void GL4Render::init()
{
    GL1Render::init();

    std::cout << "[DEBUG] Inicializando OpenGL 4.0..." << std::endl;
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    std::cout << "[DEBUG] OpenGL 4.0 inicializado correctamente." << std::endl;
}

void GL4Render::setupObject(Object* obj) {
	GL1Render::setupObject(obj);

    for (Mesh3D* mesh : obj->getMeshes()) {
        if (!mesh) continue;
        // Obtener Objeto Mesh3D
        int meshID = mesh->getMeshId();

        // Verificar si ya existe el buffer object
        if (boList.find(meshID) != boList.end()) {
            std::cerr << "[GL4Render] Advertencia: El Buffer Object ya existe para este MeshID\n";
            return;
        }

        // Crear buffer objects
        boIDS_t bo = { 0, 0, 0 };
        glGenVertexArrays(1, &bo.id);
        glGenBuffers(1, &bo.vbo);
        glGenBuffers(1, &bo.idxbo);

        // Copiar datos a GPU
        glBindVertexArray(bo.id); // Activar lista de arrays
        glBindBuffer(GL_ARRAY_BUFFER, bo.vbo); // Activar lista de vertices
        int numElements = mesh->getVertexList()->size();
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * numElements, mesh->getVertexList()->data(), GL_STATIC_DRAW); //Copiar vértices

        // Guardar Ids de Buffers
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.idxbo); // Activar lista de índices de vértices
        numElements = mesh->getTriangleIdxList()->size();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::uint32) * numElements, mesh->getTriangleIdxList()->data(), GL_STATIC_DRAW); //Copiar índices de vértices

        // Position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vPos));

        // Color
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vColor));

        // Normal
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vNorm));

        // Texture
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vTextCoords));

        // Guardar Ids de Buffers
        boList[meshID] = bo;
    }
}

// Implementación de removeObject
void GL4Render::removeObject(Object* obj) {

	GL1Render::removeObject(obj);

    for (Mesh3D* mesh : obj->getMeshes()) {
        if (!mesh) {
            std::cerr << "[GL4Render] Error: Mesh no válido en removeObject\n";
            return;
        }

        // Buscar y eliminar el buffer object
        int meshID = mesh->getMeshId();
        auto bo = boList[meshID];


        glDeleteBuffers(1, &bo.vbo);
        glDeleteBuffers(1, &bo.idxbo);
        glDeleteVertexArrays(1, &bo.id);
        boList.erase(meshID);
    }
}

// Implementación de drawObjects
void GL4Render::drawObjects(const vector<Object*>* objs)
{
    // Limpiar buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto& obj : *objs) {
        for (Mesh3D* mesh : obj->getMeshes()) {
            if (!mesh) continue;

            // Calcular matriz modelo
            glm::mat4 model = obj->getModel();

            // Setear Matriz modelo del objeto actual
            System::setModelMatrix(obj->getModel());

            //Activar material
            Material* material = mesh->getMaterial();
            if (material) {
                material->prepare();
            }

            // Activar Buffer de Datos
            auto bo = boList[mesh->getMeshId()];
            glBindVertexArray(bo.id); // Activar lista de arrays
            glBindBuffer(GL_ARRAY_BUFFER, bo.vbo); // Activar lista de vertices
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.idxbo); // Activar lista de índices de vértices

            // Ordenar a Dibujar
            glDrawElements(GL_TRIANGLES, mesh->getTriangleIdxList()->size(), GL_UNSIGNED_INT, nullptr);
        }
    }
}
