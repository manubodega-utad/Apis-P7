#pragma once
#include "Object.h"
#include "BillBoard.h"
class Emitter :
    public Object
{
    public:
        string fileName;
        vector<Object*>* particleListActive;
        vector<Object*>* particleList;

        int rateEmision;// partículas por segundo
        float remainingParticles;
        float lifeTimeMax;
        float lifeTimeMin;

        glm::vec3 speedMax;
        glm::vec3 speedMin;

        Emitter(string fileName, int rateEmision,float lifeTimeMax,
        float lifeTimeMin,
        glm::vec3 speedMax,
        glm::vec3 speedMin);

        void step(float timeStep) override;

};

