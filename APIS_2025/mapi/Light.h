#pragma once
#include "Entity.h"

class Light : public Entity {
public:
    enum class Type { DIRECTIONAL, POINT, SPOT };

private:
    Type type;
    glm::vec4 color = { 0,0,0,1 };;
    glm::vec4 direction = { 0,0,0,0 };
    bool enabled;
    float linearAttenuation;
    float cutOff;

public:
    Light(Type type = Type::DIRECTIONAL,
        glm::vec4 color = glm::vec4(1.0f),
        glm::vec4 direction = glm::vec4(0.0f, -1.0f, 0.0f, 0.0f),
        glm::vec3 position = glm::vec3(0.0f),
        bool enable = true,
        float linearAttenuation = 0.09f,
        float cutOffAngle = 12.5f);

    Type getType() const;
    void setType(Type t);

    const glm::vec4& getColor() const;
    void setColor(const glm::vec4& c);

    const glm::vec4& getDirection() const;
    void setDirection(const glm::vec4& d);

    float getLinearAttenuation() const;
    void setLinearAttenuation(float att);

    float getCutOff() const;
    void setCutOff(float angle);

    bool getEnable() const;
    void setEnable(bool e);

    virtual void step(float timeStep) override {}
};
