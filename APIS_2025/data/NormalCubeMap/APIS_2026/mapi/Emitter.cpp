#include "Emitter.h"
#include "System.h"
Emitter::Emitter(string fileName,int rateEmision, float lifeTimeMax, float lifeTimeMin, glm::vec3 speedMax, glm::vec3 speedMin)
{
    this-> lifeTimeMax= lifeTimeMax;
    this->lifeTimeMin = lifeTimeMin;

    this->speedMax = speedMax;
    this->speedMin = speedMin;
    this->fileName = fileName;

    this->rateEmision = rateEmision;

    this->particleList = new vector<Object*>();
    this->particleListActive = new vector<Object*>();

}

void Emitter::step(float timeStep)
{
    //calcular partículas a emitir
  
    remainingParticles += timeStep * (float)rateEmision;;
    int particlesToEmit = (int)remainingParticles;
    remainingParticles -= particlesToEmit;
    //crear nuevas particulas en lista vacía particleList
    for (int i = 0;i < particlesToEmit;i++)
    {
        BillBoard* b = new BillBoard(fileName);
        b->pos = this->pos;
        b->speed = glm::linearRand(speedMax, speedMin);
        b->lifeTime = glm::linearRand(lifeTimeMax, lifeTimeMin);
        this->particleList->push_back(b);
      //  System::setupObject(b);
    }

    //borrar partículas muertas en listaActiva
    for (auto &p : *particleListActive)
    {
        if (((BillBoard*)p)->lifeTime > 0)
            particleList->push_back(p);
        else
            delete (p);
    }
    //intercambiar Listas
    auto aux = particleListActive; 
    particleListActive = particleList;
    particleList = aux;
    particleList->clear();

    //mover partículas
    for (auto& p : *particleListActive)
    {
        p->step(timeStep);
    }

}
