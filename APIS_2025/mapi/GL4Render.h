#pragma once

#include "GL1Render.h"
#include "Mesh3D.h"
#include <map>

typedef struct boIDS_t
{
    unsigned int id;
    unsigned int vbo;
    unsigned int idxbo;
} boIDS_t;

class GL4Render : public GL1Render
{
private:
    // Mapa para almacenar buffer objects por ID de malla
    std::map<int, boIDS_t> boList;

public:
    // Constructor
    GL4Render(int width, int height);
    // Destructor
    ~GL4Render() override;

    // Métodos virtuales reimplementados
    void setupObject(Object* obj) override;
    void removeObject(Object* obj) override;
    void drawObjects(const std::vector<Object*>* objs) override;
};
