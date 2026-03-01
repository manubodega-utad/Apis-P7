#include "Emitter.h"
#include "System.h"
#include "GL4Render.h"

Emitter::Emitter(std::string mshFile, glm::vec4 position, bool autofade,
    float minRate, float maxRate,
    float minLife, float maxLife,
    glm::vec3 minVel, glm::vec3 maxVel,
    float minSpin, float maxSpin,
    float minScale, float maxScale,
    glm::vec4 minCol, glm::vec4 maxCol)
{
    this->mshFile = mshFile;
    this->pos = glm::vec4(position);
    this->autoFade = autofade;
    this->emitBool = true;
    this->remainingParticles = 0.0f;

    this->minRate = minRate;           this->maxRate = maxRate;
    this->minLifeTime = minLife;       this->maxLifeTime = maxLife;
    this->minVelocity = minVel;        this->maxVelocity = maxVel;
    this->minSpinVelocity = minSpin;   this->maxSpinVelocity = maxSpin;
    this->minScale = minScale;         this->maxScale = maxScale;
    this->minColor = minCol;           this->maxColor = maxCol;
}

Emitter::~Emitter()
{
    // Limpieza de memoria al destruir el emisor
    for (Particle* p : particleList) {
        System::getWorld()->removeObject(p);
        delete p;
    }
    particleList.clear();
}

// Getters
bool Emitter::isEmitting()
{
    return emitBool;
}

std::list<Particle*>& Emitter::getParticleList()
{
    return particleList;
}

// Setters
void Emitter::setRateRange(float min, float max)
{
    minRate = min;
    maxRate = max;
}

void Emitter::setVelocityRange(const glm::vec3& min, const glm::vec3& max)
{
    minVelocity = min;
    maxVelocity = max;
}

void Emitter::setSpinVelocityRange(float min, float max)
{
    minSpinVelocity = min;
    maxSpinVelocity = max;
}

void Emitter::setScaleRange(float min, float max)
{
    minScale = min;
    maxScale = max;
}

void Emitter::setLifetimeRange(float min, float max)
{
    minLifeTime = min;
    maxLifeTime = max;
}

void Emitter::setColorRange(const glm::vec4& min, const glm::vec4& max)
{
    minColor = min;
    maxColor = max;
}

void Emitter::emit(bool enable)
{
    emitBool = enable;
}

// Métodos
void Emitter::step(float deltaTime)
{
    // 1. GENERACIÓN DE PARTÍCULAS
    if (emitBool) {
        float rateEmision = glm::linearRand(minRate, maxRate);
        remainingParticles += rateEmision * deltaTime;
        int particlesToEmit = (int)(remainingParticles);
        remainingParticles -= particlesToEmit;

        for (int i = 0; i < particlesToEmit; i++)
        {
            glm::vec3 velocity = glm::linearRand(minVelocity, maxVelocity);
            float spinVelocity = glm::linearRand(minSpinVelocity, maxSpinVelocity);
            float lifeTime = glm::linearRand(minLifeTime, maxLifeTime);

            Particle* p = new Particle(mshFile, velocity, spinVelocity, lifeTime, autoFade);
            p->setPosition(this->pos);

            p->computeModelMatrix();

            particleList.push_back(p);
            System::addObject(p);
        }
    }

    // 2. ACTUALIZACIÓN Y DESTRUCCIÓN DE PARTÍCULAS
    for (auto it = particleList.begin(); it != particleList.end(); )
    {
        Particle* p = *it;
        p->step(deltaTime);

        if (p->getRemainingLifetime() <= 0.0f)
        {
            System::getWorld()->removeObject(p);
            delete p;
            it = particleList.erase(it);
        }
        else
        {
            it++;
        }
    }
}
