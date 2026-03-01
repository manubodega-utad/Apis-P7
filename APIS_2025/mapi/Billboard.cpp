#include "Billboard.h"
#include "System.h"
#include <glm/gtc/matrix_transform.hpp>

Billboard::Billboard() : Object3D("", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), spin(0.0f)
{
}

// Getters
float Billboard::getSpin() const
{
    return spin;
}

// Setters
void Billboard::setSpin(float spin)
{
    this->spin = spin;
}

void Billboard::computeModelMatrix()
{
    this->model = glm::transpose(System::getWorld()->getActiveCamera()->getView());

    model[0][3] = 0;
    model[1][3] = 0;
    model[2][3] = 0;
    model[3] = glm::vec4(glm::vec3(getPosition()), 1.0f);

    model = glm::rotate(model, rot.z, { 0,0,1 });
    model = glm::scale(model, glm::vec3(scale));

}

void Billboard::step(float deltatime)
{
}