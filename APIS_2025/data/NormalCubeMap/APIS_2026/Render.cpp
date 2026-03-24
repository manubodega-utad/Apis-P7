#include "Render.h"

Render::Render()
{
	if (glfwInit() != GLFW_TRUE)
	{
		std::cout << "ERROR iniciando glfw\n";
	}
	else {


		//iniciar opengl
#ifdef __APPLE__
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

		this->window = glfwCreateWindow(640, 480, "Tutorial APIS3D", nullptr, nullptr);
		glfwMakeContextCurrent(window);


		gladLoadGL(glfwGetProcAddress);

		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);//activa función de mezclado de color
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		glBlendFunc(GL_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//selecciona modo de mezclado


		//iniciar eventos
		GLFWKeyManager::initKeyManager(window);
		this->salir = false;
		initFrameBuffers();
	}
}

void Render::setupFrameBuffer()
{
	if (mode == offscreen)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, backBufferId);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GLenum drawBuf = GL_COLOR_ATTACHMENT0;
		glDrawBuffers(1, &drawBuf);
	}
	if (mode == onscreen)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}


void Render::setupObject(Object* obj)
{
	for (auto& mesh : obj->meshList) {
		if(bufferObjectList.find(mesh.meshId)== bufferObjectList.end())
		{
			bo_t bo = { 0,0,0 };

			//crear buffers objects
			glGenVertexArrays(1, &bo.arrayBufferId);
			glGenBuffers(1, &bo.vertexArrayId);
			glGenBuffers(1, &bo.vertexIdxArrayId);
			//copiar datos a GPU
			glBindVertexArray(bo.arrayBufferId); //activar lista de arrays
			glBindBuffer(GL_ARRAY_BUFFER, bo.vertexArrayId);//activar lista de vértices
			int numElements = mesh.vertexList.size();
			glBufferData(GL_ARRAY_BUFFER, numElements * sizeof(vertex_t), mesh.vertexList.data(), GL_STATIC_DRAW); //copiar vertices

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.vertexIdxArrayId);//activar lista de indices de vértices
			numElements = mesh.vertexIndexList.size();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, numElements * sizeof(unsigned int), mesh.vertexIndexList.data(), GL_STATIC_DRAW); //copiar indices de vertices
			//guardar ids de buffers
			bufferObjectList[mesh.meshId] = bo;
		}
	}

}





void Render::updateObjects(float timeStep)
{

	//por cada objeto
		//actualizar eventos

	for (auto& cam : uniqueCameraList)
	{
		cam.second->step(timeStep);
	}
	for (auto& obj : uniqueObjectList)
	{
		obj.second->step(timeStep);
	}
	/*for (auto& obj : System::emitterList)
	{
		obj->step(timeStep);
	}*/

}




void Render::drawObjects(int step)
{

	//ordenar por distancia a la cámara
	map<float, Object*> orderedMap;//auxiliar para ordenación

	vector<Object*> orderedObjectList; //lista final ordenada

	Camera* cam = cameraList[step][0];
	//ordenar por distancia a la cámara
	for (auto& obj : objectList[step])
	{
		float dist = glm::distance(obj->pos, cam->pos);
		orderedMap[dist] = obj;
	}
	if (orderedMap.size() > 0) {
		auto obj = orderedMap.end();
		do
		{
			obj--;
			orderedObjectList.push_back(obj->second);
		} while (obj != orderedMap.begin());
		//dibujar
		orderedObjectList.push_back(obj->second);
	}



	//por cada objeto
		//dibujar
	for (auto& obj : orderedObjectList)
	{
		//calcular matriz modelo
		auto model = obj->getModelMatrix();
		for (auto& mesh : obj->meshList) {
			Material* mat = mesh.material;

			mat->renderProgram->activate();

			mat->renderProgram->setMVP(cam->cameraProjection * cam->cameraView * model);
			mat->renderProgram->setM(model);
			mat->renderProgram->setComputeLight(mat->lightEnable);
			mat->renderProgram->setReflection(mat->reflection);
			mat->renderProgram->setRefraction(mat->refraction, mat->refractionIndex);


			//activar buffers de datos
			auto bo = bufferObjectList[mesh.meshId]; //recuperar ids de buffers de este objeto
			glBindVertexArray(bo.arrayBufferId); //activar lista de arrays
			glBindBuffer(GL_ARRAY_BUFFER, bo.vertexArrayId);//activar lista de vértices
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.vertexIdxArrayId);//activar lista de indices de vértices
			//describir buffers
			mat->renderProgram->setAttributeMetaData("vPos", 4, GL_FLOAT, false, sizeof(vertex_t), (void*)offsetof(vertex_t, vPosition));
			mat->renderProgram->setAttributeMetaData("vColor", 4, GL_FLOAT, false, sizeof(vertex_t), (void*)offsetof(vertex_t, vColor));
			mat->renderProgram->setAttributeMetaData("vNormal", 4, GL_FLOAT, false, sizeof(vertex_t), (void*)offsetof(vertex_t, vNormal));
			mat->renderProgram->setAttributeMetaData("vTan", 4, GL_FLOAT, false, sizeof(vertex_t), (void*)offsetof(vertex_t, vTan));

			mat->renderProgram->setAttributeMetaData("vTexCoord", 2, GL_FLOAT, false, sizeof(vertex_t), (void*)offsetof(vertex_t, vTexCoord));



			//si hay textura, activarla
			mat->renderProgram->resetTextureData();
			int textureUnitCounter = 0;
			for (auto& texture : mat->textureList)
			{
				auto t = texture.second;
				auto name = texture.first;
				mat->renderProgram->setTextureData(textureUnitCounter++,
					t->GlTextID, 
					t->type,
					name,
					t->textureName == "textureNormal");

			}
			

			mat->renderProgram->setLight(*(lightList[step][0]));
			mat->renderProgram->setCamera(*cam);

			mat->renderProgram->setShininess(mat->shininess);

			//si el material usa depthWrite, activar/desactivar
			//glDisable(GL_DEPTH_TEST);

			glEnable(GL_BLEND);//activa función de mezclado de color
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//selecciona modo de mezclado

			//ordenar a dibujar
			glDrawElements(GL_TRIANGLES, mesh.vertexIndexList.size(), GL_UNSIGNED_INT, nullptr);
		}
	}
}


void Render::mainLoop()
{
	float newTime = static_cast<float>(glfwGetTime());
	float deltaTime = 0;
	float lastTime = newTime;
	while (!salir)
	{
		newTime = static_cast<float>(glfwGetTime());
		deltaTime = newTime - lastTime;
		lastTime = newTime;

		//capturar eventos
		GLFWKeyManager::updateEvents();
		//actualizar estado aplicacion
		//limpiar buffer de imagen
		int stepNumber = 0;
		updateObjects(deltaTime);

		for (auto step : pipeline)
		{
			//enlazar objetos entrada/salida
			for (auto& bufferName : step.input) {
				auto readBackBuffer =
					this->getBuffer(bufferName.second);
				auto& stepList = objectList[stepNumber];
				for (auto& obj : stepList) {
					for (auto& mesh : obj->meshList)
					{
						mesh.material->textureList[bufferName.second] = readBackBuffer;
					}
				}
			}
			//activar buffers de salida en render
			for (auto& bufferName : step.output) {
				this->
					setOutBuffer(bufferName.first, bufferName.second);
			}
			setupFrameBuffer();

			drawObjects(stepNumber++);

			/*for (auto& e : System::emitterList) {

				drawObjects(*(e->particleListActive), System::cam);

			}*/
			//dibujar
		}
		glfwSwapBuffers(window);//una vez dibujado, intercambiar buffer de imagen en ventana
		salir = glfwWindowShouldClose(window);

	}
	//cerrar librerías gráficas

	glfwTerminate();
}


void Render::initFrameBuffers() {
	colorBuffer = new GLTextureFB("textureColor",textureColorFB, 640, 480);
	colorBuffer->textureName = "textureColor";
	depthBuffer = new GLTextureFB("textureDepth",textureDepthFB, 640, 480);
	depthBuffer->textureName = "textureDepth";
	glGenFramebuffers(1, &backBufferId); //crear el identificador de frameBuffer
	glBindFramebuffer(GL_FRAMEBUFFER, backBufferId); //asociar la textura anterior a ese nuevo framebuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer->GlTextID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBuffer->GlTextID, 0);
	glDrawBuffer(GL_NONE); //no se generarán datos de pantalla
	glReadBuffer(GL_NONE);
	//volver al principal
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//check errores
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("ERROR\n");
	}
}

#include "pugixml.hpp"

void Render::readPipeLine(std::string fileName)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(fileName.c_str());
	if (result) {
		// Cargado correctamente, podemos analizar su contenido ...
		pugi::xml_node pipelineTree = doc.child("pipeline");
		for (pugi::xml_node stepNode = pipelineTree.child("step");
			stepNode;
			stepNode = stepNode.next_sibling("step"))
		{
			pipelineNode p;
			auto inputNode = stepNode.child("input");
			if (inputNode)
				for (auto input : inputNode.children())
					p.input[input.name()] = input.text().as_string();
			auto outputNode = stepNode.child("output");
			if (outputNode)
				for (auto output : outputNode.children())
					p.output[output.name()] = output.text().as_string();
			pipeline.push_back(p);
		}
	}
}



GLTexture* Render::getBuffer(std::string bufferName) {
	return buffers[bufferName];
}
void Render::setOutBuffer(std::string type, std::string bufferName) {
	mode = offscreen;
	if (type == "color")//guardar los buffers de salida con un nuevo nombre
		buffers[bufferName] = colorBuffer;
	if (type == "depth")
		buffers[bufferName] = depthBuffer;
	if (type == "screen")//si se activa el modo pantalla
		mode = onscreen;
}
