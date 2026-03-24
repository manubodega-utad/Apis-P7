#pragma once
#include "common.h"
#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include "Emitter.h"
#include "Render.h"

class System
{
public:

	//static inline vector< Emitter*> emitterList;
	static inline Render* render;

	 static void init()
	 {
		 render = new Render();
		 render->readPipeLine("data/pipeline.pipe");
		 //cargar escenario
		 
		 Object* obj1 = new Object("data/skybox1/skybox_obj.msh");
		 obj1->scaling = vec4(100, 100, 100, 100);
		 obj1->pos.z += 0.001;
		 //Object* obj1 = new Object("data/lightBox/texturedCube.msh");
		 Object* obj2 = new Object("data/teapot/metalTeapot.msh");
		 Object* obj3 = new Object("data/suzanne/glassSuzanne.msh");
		 Object* obj4 = new Object("data/normalMap/normalMapCubeObj.msh");

		 obj3->pos = vec4(2.0f, 0, 0, 1);
		 obj4->pos = vec4(4.0f, 0, 0, 1);

		 render->addObject(0,obj1); //añadir un nuevo objeto cargado de fichero
		 render->addObject(0,obj2); //añadir un nuevo objeto cargado de fichero
		 render->addObject(0,obj3); //añadir un nuevo objeto cargado de fichero
		 render->addObject(0,obj4); //añadir un nuevo objeto cargado de fichero
	 
		 Object* screen = new Object("data/plane2D/plane2D.msh");
		 render->addCamera(0, new Camera(glm::vec4(3, 5, 3, 1), glm::vec4(0, 0, 0, 1)));
		 render->addCamera(1, new Camera(glm::vec4(0, 0, 3, 1), glm::vec4(0, 0, 0, 1)));
		 render->addLight(0, new Light({ 0, 0, 3, 1 }, { 0,0,0,0 }, { 1,1,1 }));
		 render->addLight(1, new Light({ 0, 0, 3, 1 }, { 0,0,0,0 }, { 1,1,1 }));
		 render->addObject(1, screen); //añadir un nuevo objeto cargado de fichero

	 }


};

