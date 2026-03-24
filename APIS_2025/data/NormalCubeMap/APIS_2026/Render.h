#pragma once
#include "mapi/common.h"
#include "GLFWKeyManager.h"
#include "BillBoard.h"

typedef struct {

    //id de array de buffers
    unsigned int arrayBufferId;
    //id de vertex array buffer
    unsigned int vertexArrayId;
    //id de vertex index buffer
    unsigned int vertexIdxArrayId;
}bo_t; //datos de buffer objects


class Render
{

public:
    map<int, vector<Object*>> objectList;
    map<int, vector<Camera*>> cameraList;
    map<int, vector<Light*>> lightList;
    map<Object*, Object*> uniqueObjectList;
    map<Light*, Light*> uniqueLightList;
    map<Camera*, Camera*> uniqueCameraList;

    map<int, bo_t> bufferObjectList; //listas de datos en GPU, indexadas por Identificador único de Objeto
    GLFWwindow* window;
    bool salir = false;

    typedef enum renderModes {
        offscreen, onscreen
    }renderModes;
    renderModes mode = onscreen;
    GLTexture* colorBuffer = nullptr;
    GLTexture* depthBuffer = nullptr;
    unsigned int backBufferId = 0;
    std::map<std::string, GLTexture*> buffers;


    class pipelineNode {
    public:
        int nodeIdx = 0;
        //<tipo, nombre>
        std::map<std::string, std::string>input;
        //<tipo, nombre>
        std::map<std::string, std::string>output;
    };
    //añadir atributo "vector de nodos pipeline" a clase System, y su cargador
    std::vector<pipelineNode> pipeline;




    Render();
    void setupFrameBuffer();
    void addObject(int step, Object* obj) { objectList[step].push_back(obj); 
                                            setupObject(obj);
                                            uniqueObjectList[obj] = obj; };
    void addLight(int step, Light* obj) { lightList[step].push_back(obj);
                                          uniqueLightList[obj] = obj;
                                        };
    void addCamera(int step, Camera* obj) { cameraList[step].push_back(obj);
                                            uniqueCameraList[obj] = obj;
                                          };


    void setupObject(Object* obj);


    void updateObjects(float timeStep);

    void drawObjects(int step);

    void mainLoop();

    void initFrameBuffers();

    void readPipeLine(std::string fileName);

    GLTexture* getBuffer(std::string bufferName);

    void setOutBuffer(std::string type, std::string bufferName);

};

