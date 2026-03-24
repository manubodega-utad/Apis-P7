#include "BillBoard.h"
#include "System.h"

glm::mat4 BillBoard::getModelMatrix()
{
        glm::mat4  model = glm::mat4(1.0f);
        /*
        model = glm::transpose(System::cam.cameraView);
        model[0][3] = 0;
        model[1][3] = 0;
        model[2][3] = 0;
        model[3] = this->pos;*/
        return model;
}

void BillBoard::step(float timeStep)
{


    this->pos += timeStep * vec4(speed,0);
    this->lifeTime -= timeStep;

}
