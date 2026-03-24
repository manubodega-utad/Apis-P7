#pragma once
#include "mapi/common.h"
#include "vertex.h"
#include "Material.h"


typedef struct {

    int meshId;
    Material* material;
    std::vector<vertex_t> vertexList;
    std::vector<int>      vertexIndexList;

}Mesh3d;

class Object
{

public:
    static inline int objectCounter = 0;
    static inline int meshIdCounter=0;

    int objectId;

    glm::vec4  pos;
    glm::vec4  rot;
    glm::vec4  scaling;
    
    vector<Mesh3d> meshList;

    string mshFile = "";

    Object();
    Object(string mshFile);

    virtual glm::mat4 getModelMatrix();

    virtual void step(float timeStep);

    void loadFile(string mshFile);
    void recomputeNormals();
    void loadObj(string objFile, Material* mat);
};

