#include "Object3D.h"
#include "Factory.h"
#include "System.h"
#include "Mesh3D.h"

#include <iostream>
#include "pugixml.hpp"
#include "common.h"

using namespace std;

// Constructor
Object3D::Object3D(string mshFile) : Object() 
{
    loadDataFromFile(mshFile);
}

// Destructor
Object3D::~Object3D() {}

void Object3D::loadDataFromFile(const string& file) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file.c_str());

    if (result) {
        // Cargado correctamente
        // Buscar el nodo raíz 'mesh'
        pugi::xml_node meshNode = doc.child("mesh");
        if (!meshNode) {
            std::cerr << "[ERROR] No se encontró nodo <mesh> en " << file << std::endl;
            return;
        }

        pugi::xml_node buffersNode = meshNode.child("buffers");
        if (!buffersNode) {
            std::cerr << "[ERROR] No se encontró nodo <buffers> en " << file << std::endl;
            return;
        }

        // Iterar sobre cada buffer del archivo
        for (pugi::xml_node bufferNode = buffersNode.child("buffer"); 
            bufferNode; 
            bufferNode = bufferNode.next_sibling("buffer")) 
        {

            Mesh3D* mesh = new Mesh3D();

            // Nodo del material
            pugi::xml_node materialNode = bufferNode.child("material");
            Material* material = Factory::getNewMaterial();

            // Nodo de la textura
            pugi::xml_node textureNode = materialNode.child("texture");

            // Carga de textura si existe
            if (textureNode) {
                string textureFile = textureNode.child("layer").text().as_string();
                Texture* texture = Factory::getNewTexture();
                texture->load(textureFile);
                texture->update();
                material->setColorText(texture);
            }

            // Nodo del color
            pugi::xml_node colorNode = materialNode.child("color");
            if (colorNode) {
                std::string colorText = colorNode.text().as_string();
                auto comps = splitString<std::string>(colorText, ',');
                if (comps.size() >= 3) {
                    float r = std::stof(comps[0]);
                    float g = std::stof(comps[1]);
                    float b = std::stof(comps[2]);
                    float a = (comps.size() >= 4) ? std::stof(comps[3]) : 1.0f;
                    material->setColorRGBA(glm::vec4(r, g, b, a));
                }
            }

            // Nodo del shader
            pugi::xml_node shaderNode = materialNode.child("shader");
            if (shaderNode) {
                std::string shadersText = shaderNode.text().as_string();
                auto shaderFiles = splitString<std::string>(shadersText, ',');
                if (!shaderFiles.empty()) {
                    material->loadPrograms(shaderFiles);
                }
                else {
                    std::cerr << "[ERROR] <shader> vacío en " << file << std::endl;
                }
            }
            else {
                std::cerr << "[WARN] No hay <shader> en material (" << file << ")." << std::endl;
            }

            // Nodo shininess
            pugi::xml_node shininessNode = materialNode.child("shininess");
            if (shininessNode) {
                int s = shininessNode.text().as_int();
                material->setShininess(s);
            }


            mesh->setMaterial(material);

            // Cargar la geometría usando loadObj
            string meshData = bufferNode.child("meshData").text().as_string();
            if (!loadObj(meshData, mesh)) {
                std::cerr << "[ERROR] No se pudo cargar el archivo .obj: " << meshData << endl;
                delete mesh;
                continue;
            }

            // Añadir la malla al objeto
            setMesh(mesh);
        } 
        
    }
    else {
        std::cerr << "[ERROR] XML cargado incorrectamente: " << result.description() << endl;
        return;
    }

    std::cout << "[INFO] Carga de malla desde " << file << " completada exitosamente." << endl;
}

bool Object3D::loadObj(string obj, Mesh3D* mesh)
{
    std::ifstream f(obj, std::ios_base::in);
    std::vector<glm::vec4> vPos;
    std::vector<glm::vec2> vTC;
    std::vector<glm::vec4> vNorm;
    bool computeNormals = false;
    std::string line;

    while (std::getline(f, line, '\n')) {
        std::istringstream str(line);
        std::string key;
        str >> key;

        if (key[0] != '#') {
            /*if (key == "o")
            {
                if (mesh) meshes.push_back(mesh);
                mesh = new Mesh3D();
                mesh->setMaterial();
                vertexOffset = vPos.size();
            }*/
            if (key == "v") {
                glm::vec4 v(1.0f);
                str >> v.x >> v.y >> v.z;
                vPos.push_back(v);
            }
            else if (key == "vn") {
                glm::vec4 v(0);
                str >> v.x >> v.y >> v.z;
                vNorm.push_back(v);
            }
            else if (key == "vt") {
                glm::vec2 v(0);
                str >> v.x >> v.y;
                vTC.push_back(v);
            }
            else if (key == "f") {
                std::string vert;
                vertex_t v[3];

                for (int i = 0; i < 3; i++) {
                    str >> vert;
                    auto indexes = splitString<int>(vert, '/');
                    if (indexes.size() == 3) {
                        v[i].vPos = vPos[indexes[0] - 1];
						v[i].vColor = glm::vec4(0);
                        v[i].vNorm = vNorm[indexes[2] - 1];
                        v[i].vTextCoords = vTC[indexes[1] - 1];
                    }
                    else if (indexes.size() == 1) {
                        v[i].vPos = vPos[indexes[0] - 1];
						v[i].vColor = glm::vec4(0);
                        v[i].vNorm = glm::vec4(0);
                        v[i].vTextCoords = glm::vec2(0);
                        computeNormals = true;
                    }
                    mesh->addVertex(v[i]);
                }

                int numVerts = mesh->getVertexList()->size();
                mesh->addTriangle(numVerts - 3, numVerts - 2, numVerts - 1);
            }
        }
    }

    if (computeNormals) recomputeNormals();
    f.close();

    return true;
}


void Object3D::recomputeNormals()
{
    for (auto* m : meshes)
    {
        auto* idx = m->getTriangleIdxList();
        auto* vtx = const_cast<std::vector<vertex_t>*>(m->getVertexList());

        // reset normales
        for (auto& v : *vtx) v.vNorm = glm::vec4(0.0f);

        // recorrer triángulos (cada 3 índices)
        for (size_t i = 0; i + 2 < idx->size(); i += 3)
        {
            vertex_t& v1 = (*vtx)[(*idx)[i]];
            vertex_t& v2 = (*vtx)[(*idx)[i + 1]];
            vertex_t& v3 = (*vtx)[(*idx)[i + 2]];

            glm::vec3 l1 = glm::normalize(glm::vec3(v2.vPos - v1.vPos));
            glm::vec3 l2 = glm::normalize(glm::vec3(v2.vPos - v3.vPos));
            glm::vec3 n = glm::normalize(glm::cross(l2, l1));

            v1.vNorm = glm::normalize(v1.vNorm + glm::vec4(n, 0.0f));
            v2.vNorm = glm::normalize(v2.vNorm + glm::vec4(n, 0.0f));
            v3.vNorm = glm::normalize(v3.vNorm + glm::vec4(n, 0.0f));
        }
    }
}


void Object3D::step(float deltaTime) {
    // No hace nada por ahora
}
