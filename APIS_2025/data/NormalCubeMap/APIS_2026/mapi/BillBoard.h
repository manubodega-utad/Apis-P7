#pragma once
#include "Object.h"
#include "common.h"
class BillBoard : public Object
{
public:

    float lifeTime = 0;
    glm::vec3 speed = { 0,0,0 };

    BillBoard(string mshFile) :Object(mshFile)
    {
    }
    virtual glm::mat4 getModelMatrix() override;
    virtual void step(float timeStep) override ;


};

