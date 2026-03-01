#pragma once
#include "Entity.h"
#include "Particle.h"
#include <list>
#include <string>
#include <glm/glm.hpp>

class Emitter : public Entity {
private:
    std::string mshFile;
    bool autoFade;
    
    float minRate, maxRate;
    glm::vec3 minVelocity, maxVelocity = glm::vec3(0);
    float minSpinVelocity, maxSpinVelocity;
    float minScale, maxScale;
    float minLifeTime, maxLifeTime;
    glm::vec4 minColor, maxColor;

    bool emitBool;
    float remainingParticles;
    std::list<Particle*> particleList;

public:
    // Constructor
    Emitter(std::string mshFile, glm::vec4 position, bool autofade,
        float minRate, float maxRate,
        float minLife, float maxLife,
        glm::vec3 minVel, glm::vec3 maxVel,
        float minSpin, float maxSpin,
        float minScale, float maxScale,
        glm::vec4 minCol, glm::vec4 maxCol);

    // Destructor
    virtual ~Emitter();

	// Getters
    bool isEmitting();
    std::list<Particle*>& getParticleList();

    // Setters
    void setRateRange(float min, float max);
    void setVelocityRange(const glm::vec3& min, const glm::vec3& max);
    void setSpinVelocityRange(float min, float max);
    void setScaleRange(float min, float max);
    void setLifetimeRange(float min, float max);
    void setColorRange(const glm::vec4& min, const glm::vec4& max);
    void emit(bool enable);

    // Métodos
    virtual void step(float deltaTime) override;
};