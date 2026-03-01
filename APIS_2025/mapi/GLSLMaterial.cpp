#include "GLSLMaterial.h"
#include "System.h"


GLSLMaterial::GLSLMaterial()
    : Material(),
    color(1.0f, 1.0f, 1.0f, 1.0f)
{
    this->program = new GLSLProgram();
}

GLSLMaterial::~GLSLMaterial() {}

void GLSLMaterial::loadPrograms(vector<string>& files) {
    if (!program) {
        std::cerr << "[ERROR] GLSLMaterial::loadPrograms -> program es nullptr\n";
        return;
    }
    for (auto& file : files) {
        program->addProgram(file);
    }

    program->linkProgram();
}

void GLSLMaterial::prepare() {
    program->use();
    auto* glsl = dynamic_cast<GLSLProgram*>(program);
    if (glsl) {
        auto* world = System::getWorld();
        Camera* cam = world->getActiveCamera();

        // MATRICES
        glm::mat4 modelMatrix = System::getModelMatrix();
        glm::mat4 viewMatrix = cam->getView();
        glm::mat4 projectionMatrix = cam->getProjection();
        glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
        glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelMatrix));

        std::string MVPName = "MVP";
        glsl->setMatrix(MVPName, MVP);

        std::string modelName = "M";
        glsl->setMatrix(modelName, modelMatrix);

        std::string normalName = "N";
        glsl->setMatrix(normalName, normalMatrix);

        // MATERIAL
        std::string colorRGBAName = "mat.color";
        glsl->setVec4(colorRGBAName, getColorRGBA());

        std::string shininessName = "mat.shininess";
        glsl->setInt(shininessName, getShininess());

        // TEXTURAS
        if (colorText) {
            glsl->setInt("mat.useColorText", 1);
            glsl->bindColorTextureSampler(0, colorText);
        }
        else {
            glsl->setInt("mat.useColorText", 0);
        }

        //AMBIENTE
        std::string ambientName = "ambient";
        glsl->setFloat(ambientName, world->getAmbient());

        std::string lightingName = "useLighting";
        glsl->setInt(lightingName, this->lighting ? 1 : 0);

        // CAMARA
        std::string camPosName = "eyePos";
        glsl->setVec4(camPosName, cam->getPosition());

        // LUCES
        int i = 0;
        const int MAX_LIGHTS = 8;

        for (Light* l : System::getWorld()->getLights()) {
            if (!l) continue;
            if (i >= MAX_LIGHTS) break;

            glsl->setVec4("lights[" + std::to_string(i) + "].position", l->getPosition());
            glsl->setVec4("lights[" + std::to_string(i) + "].direction", l->getDirection());
            glsl->setVec4("lights[" + std::to_string(i) + "].color", l->getColor());
            glsl->setInt("lights[" + std::to_string(i) + "].type", static_cast<int>(l->getType()));
            glsl->setInt("lights[" + std::to_string(i) + "].enable", l->getEnable() ? 1 : 0);
            glsl->setFloat("lights[" + std::to_string(i) + "].linearAttenuation", l->getLinearAttenuation());
            glsl->setFloat("lights[" + std::to_string(i) + "].cutOff", l->getCutOff());

            i++;
        }

        glsl->setInt("activeLights", i);

		// ESTADO DE RENDER
        glsl->setCulling(this->culling);
        glsl->setDepthWrite(this->depthWrite);
        glsl->setBlendMode(this->blendMode);
    }else 
    {
        cout << "[GLSLMaterial] ERROR: No se pudo hacer dynamic_cast a GLSLProgram" << endl;
    }
}
