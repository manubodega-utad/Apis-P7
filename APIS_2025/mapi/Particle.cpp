#include "Particle.h"
#include "Mesh3D.h"
#include "Material.h"
#include <iostream>

Particle::Particle(std::string mshFile, const glm::vec3& vel, float spinVel, double lifetime, bool autofade)
    : Billboard()
{
    loadDataFromFile(mshFile);
    this->vel = glm::vec4(vel, 0.0f);
    this->setSpin(spinVel);

    this->lifeTime = lifetime;
    this->remainingLifeTime = lifetime;
    this->autoFade = autofade;
}

Particle::~Particle()
{
}

// Getters

float Particle::getRemainingLifetime() const
{
    return static_cast<float>(remainingLifeTime);
}

// Métodos
void Particle::step(float deltaTime)
{
    // 1. Reducir el tiempo de vida
    remainingLifeTime -= deltaTime;

    // 2. Actualizar la posición
    pos += vel * static_cast<float>(deltaTime);

    // 3. Aplicar el spin
    rot.z += getSpin() * static_cast<float>(deltaTime);

    computeModelMatrix();

    // 4. AutoFade
    if (autoFade && !meshes.empty()) {
        Material* mat = meshes[0]->getMaterial();
        if (mat) {
            glm::vec4 color = mat->getColorRGBA();
            double alpha = remainingLifeTime / lifeTime;
            color.a = alpha;
            mat->setColorRGBA(color);
        }
    }
}