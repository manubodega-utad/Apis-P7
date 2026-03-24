#include "Object.h"
#include "GLFWKeyManager.h"
#include "pugixml.hpp"

Object::Object()
{
   /* this->objectId = objectCounter++;
    Mesh3d msh;
    msh.vertexList = 
    { 
      {{ 0.5f, 0.5f,0.0f,1.0f},{ 1.0f,0.0f,0.0f,1.0f},{0,0,0,0},{1,1}},//superior derecha
      {{-0.5f, 0.5f,0.0f,1.0f},{ 1.0f,0.0f,0.0f,1.0f},{0,0,0,0},{0,1}},//superior izquierda
      {{-0.5f,-0.5f,0.0f,1.0f},{ 1.0f,0.0f,1.0f,1.0f},{0,0,0,0},{0,0}},//inferior izquierda 
      {{ 0.5f,-0.5f,0.0f,1.0f},{ 0.0f,0.0f,1.0f,1.0f},{0,0,0,0},{1,0}} //inferior derecha
    }; //posiciones de vertices

    msh.vertexIndexList = { 2,1,0, 2,0,3 };

    this->pos = { 0.0f,0.0f,0.0f,1.0f };
    this->rot = { 0.0f,0.0f,0.0f,1.0f };
    this->scaling = { 1.0f,1.0f,1.0f,1.0f };

    //crear programa de dibujado
    msh.material = new Material();
    msh.material->renderProgram = new Program();
    msh.material->renderProgram->addShader("data/shader.vert"); //añadir codigo de renderizado
    msh.material->renderProgram->addShader("data/shader.frag");
    msh.material->renderProgram->linkProgram(); //compilar/linkar

    msh.material->texture = new GLTexture("data/ship.png");

    this->meshList.push_back(msh);
    recomputeNormals();*/
}

Object::Object(string mshFile):mshFile(mshFile)
{
    this->objectId = objectCounter++;

    this->pos = { 0.0f,0.0f,0.0f,1.0f };
    this->rot = { 0.0f,0.0f,0.0f,1.0f };
    this->scaling = { 1.0f,1.0f,1.0f,1.0f };


    loadFile(mshFile);
}

glm::mat4 Object::getModelMatrix()
{
    glm::mat4  model= glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(pos));//aplicar posicion

    model = glm::rotate(model, glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f)); //rotar x
    model = glm::rotate(model, glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f)); //rotar y
    model = glm::rotate(model, glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f)); //rotar z

    model = glm::scale(model, glm::vec3(scaling));//aplicar posicion


    return model;
}

void Object::step(float timeStep)
{
    float vel = 0.1f; //unidadesGl segundo
    float velRot = 40.0f;
    /*if (GLFWKeyManager::keyboardState[GLFW_KEY_D])
        this->pos.x += vel * timeStep;
    if (GLFWKeyManager::keyboardState[GLFW_KEY_A])
        this->pos.x -= vel * timeStep;
    if (GLFWKeyManager::keyboardState[GLFW_KEY_W])
        this->pos.y += vel * timeStep;
    if (GLFWKeyManager::keyboardState[GLFW_KEY_S])
        this->pos.y -= vel * timeStep;
        */
    if (GLFWKeyManager::keyboardState[GLFW_KEY_R])
        this->rot.x += velRot * timeStep;
    if (GLFWKeyManager::keyboardState[GLFW_KEY_T])
        this->rot.x -= velRot * timeStep;

}

void Object::loadFile(string mshFile)
{


    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(mshFile.c_str());
    if (result) {
        // Cargado correctamente, podemos analizar su contenido ...
        pugi::xml_node buffersNode = doc.child("mesh").child("buffers");

        for (pugi::xml_node bufferNode = buffersNode.child("buffer");
            bufferNode;
            bufferNode = bufferNode.next_sibling("buffer"))
        {
            // Iteramos por todos los buffers
            auto materialNode = bufferNode.child("material");
            Material* material = new Material();
            
            auto textureNode = materialNode.child("texture");
            if (textureNode)
            {
                //layers
                //añadir nueva textura
                string textureType = textureNode.attribute("type").as_string();
                if (textureType == "color2D")
                { //por cada layer
                    for (pugi::xml_node layerNode = textureNode.child("layer");
                        layerNode;
                        layerNode = layerNode.next_sibling("layer"))
                    {
                        string layerName = layerNode.attribute("name").as_string();
                        auto t= new GLTexture(layerNode.text().as_string());
                        t->textureName = layerName;
                        material->textureList[layerName] = t;
         
                    }
                }
                if (textureType == "cubeMap")
                {
                    pugi::xml_node layerNode = textureNode.child("layer");
                    auto fileList = splitString<string>(textureNode.child("layer").text().as_string(),',');
                    string layerName = layerNode.attribute("name").as_string();
                    auto t = new GLTexture(fileList);
                    t->textureName = layerName;
                    material->textureList[layerName] = t;

                }

            }
            auto shaderNode = materialNode.child("shader");
            if (shaderNode)
            {
                material->renderProgram = new Program();
                auto shaderList = splitString<string>(shaderNode.text().as_string(), ',');
                for (auto& s : shaderList) {
                    material->renderProgram->addShader(s);
                }
                material->renderProgram->linkProgram();
            }

            auto shiniNode = materialNode.child("shininess");
            if (shiniNode)
            {
                //layers
                //añadir nueva textura
                material->shininess = shiniNode.text().as_int();
            }
            auto lightNode = materialNode.child("light");
            if (lightNode)
            {
                //layers
                //añadir nueva textura
                material->lightEnable = lightNode.text().as_bool();
            }
            auto reflectionNode = materialNode.child("reflection");
            if (reflectionNode)
            {
                //layers
                //añadir nueva textura
                material->reflection = reflectionNode.text().as_bool();
            }
            auto refractionNode = materialNode.child("refraction");
            if (refractionNode)
            {
                //layers refractIndex
                //añadir nueva textura
                material->refraction = refractionNode.text().as_bool();
                material->refractionIndex= materialNode.child("refractIndex").text().as_float();
            }

            string meshData = bufferNode.child("meshData").text().as_string();
            loadObj(meshData, material);
        }

    }
    else {
        // No se ha podido cargar
        std::cout << result.description() << std::endl;
    }
}


void Object::recomputeNormals()
{
    for (auto& m : meshList) {
        for (auto& v : m.vertexList) //por cada vértice, resetear sus normales
            v.vNormal = { 0,0,0,0 };
        for (auto it = m.vertexIndexList.begin(); it != m.vertexIndexList.end();)//recorrer la lista de índices de vértices
        {
            vertex_t& v1 = m.vertexList[*it]; it++; //cada tres vértices, una faceta
            vertex_t& v2 = m.vertexList[*it]; it++;
            vertex_t& v3 = m.vertexList[*it]; it++;
            glm::vec3 l1 = glm::normalize(v2.vPosition - v1.vPosition); //obtener dos aristas
            glm::vec3 l2 = glm::normalize(v2.vPosition - v3.vPosition);
            glm::vec3 norm = glm::normalize(glm::cross(l2, l1)); //obtener la normal
            v1.vNormal = glm::normalize(v1.vNormal + glm::vec4(norm, 0.0f)); //acumular la normal, en caso de ser vértices compartidos
            v2.vNormal = glm::normalize(v2.vNormal + glm::vec4(norm, 0.0f));
            v3.vNormal = glm::normalize(v3.vNormal + glm::vec4(norm, 0.0f));
        }
    }
}

void Object::loadObj(string objFile,Material* mat)
{

        std::ifstream f(objFile, std::ios_base::in);
        std::vector<glm::vec4> vPos;
        std::vector<glm::vec2> vTC;
        std::vector<glm::vec4> vNorm;
        std::vector<glm::vec4> vTan;
        std::string line;
        Mesh3d m;
        m.material = nullptr;
        int vertexOffset = 0;
        bool computeNormals = false;
        while (std::getline(f, line, '\n')) {
            std::istringstream str(line);
            std::string key;
            str >> key;
            if (key[0] != '#' || key == "#vta") {
                if (key == "o")
                {
                    if (m.material) {
                        m.meshId =meshIdCounter++;
                        meshList.push_back(m);
                    }
                    m.material = mat;
                    m.vertexIndexList.clear();
                    m.vertexList.clear();
                    vertexOffset = vPos.size();
                }
                else if (key == "#vta")
                {
                    glm::vec4 v(0.0f);
                    str >> v.x >> v.y >> v.z;
                    vTan.push_back(v);
                }
                else if (key == "v")
                {
                    glm::vec4 v(1.0f);
                    str >> v.x >> v.y >> v.z;
                    vPos.push_back(v);
                    m.vertexList.push_back(vertex_t{});
                }
                else if (key == "vn")
                {
                    glm::vec4 v(0);
                    str >> v.x >> v.y >> v.z;
                    vNorm.push_back(v);
                }

                else if (key == "vt")
                {
                    glm::vec2 v(0);
                    str >> v.x >> v.y;
                    vTC.push_back(v);
                }
                else if (key == "f")
                {
                    std::string vert;
                    vertex_t v[3];
                    int vIndex[3] = { 0 };
                    for (int i = 0; i < 3; i++)
                    {
                      /*  str >> vert;
                        auto indexes = splitString<int>(vert, '/');
                        v[i] = { vPos[indexes[0] - 1],{0,0,0,0},//vNorm[indexes[2] -m1],
                            vTC[indexes[1] - 1] };
                        this->vertexList[indexes[0] - 1 - vertexOffset] = v[i];
                        this->vertexIndexList.push_back(indexes[0] - 1 - vertexOffset);
                        */
                        str >> vert;
                        auto indexes = splitString<int>(vert, '/');
                        if (indexes.size() == 3) //si hay tres índices por faceta, se carga la información de normales y textura
                        {
                            v[i] = { vPos[indexes[0] - 1],{0,0,0,0},vNorm[indexes[2] - 1],{ 0,0,0,0 },vTC[indexes[1] - 1] };
                        }
                        else if (indexes.size() == 1)//si no, no hay textura y sólo se carga el dato de posición de vértice
                        {
                            v[i] = { vPos[indexes[0] - 1],{0,0,0,0}, { 0,0,0,0 },{ 0,0,0,0 } ,{0,0} };
                            computeNormals = true; //se deben recalcular las normales al acabar de cargar información
                        }

                        if (vTan.size() != 0)
                        {
                            v[i].vTan = vTan[indexes[0] - 1];
                        }

                        m.vertexList[indexes[0] - 1 - vertexOffset] = v[i];
                        m.vertexIndexList.push_back(indexes[0] - 1 - vertexOffset);
                    }
                }
            }
        }
        if (computeNormals)
            this->recomputeNormals();
        if (m.material)
        {
            m.meshId = meshIdCounter++;
            meshList.push_back(m);
        }
}




