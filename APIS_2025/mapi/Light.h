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

public:
    Light();

    Type getType() const;
    void setType(Type t);

    const glm::vec4& getColor() const;
    void setColor(const glm::vec4& c);

    const glm::vec4& getDirection() const;
    void setDirection(const glm::vec4& d);

    float getLinearAttenuation() const;
    void setLinearAttenuation(float att);

    bool getEnable() const;
    void setEnable(bool e);

    virtual void step(float timeStep) override {}
};
