#include "GLSLProgram.h"
#include "GLSLShader.h"
#include "GLTexture.h"

using namespace std;
GLSLProgram::GLSLProgram() {
    idRenderProgram = 0;
}

GLSLProgram::~GLSLProgram() {
    // Liberar los shaders
    for (auto* sh : shaders) {
        delete sh;
    }
}

void GLSLProgram::addProgram(string& fileName) {
    //useProgram ??
    GLSLShader* shader = new GLSLShader(fileName);
    shader->readFile();
    shader->compile();
    shader->checkErrors();

    // Lo guardamos
    shaders.push_back(shader);
}

void GLSLProgram::linkProgram() {
    // Crear un programa
    idRenderProgram = glCreateProgram();

    for (auto* &c : shaders) {
        glAttachShader(idRenderProgram, c->getID());
    }
    // Linkar
    glLinkProgram(idRenderProgram);

    // Comprobar errores de link
    checkLinkerErrors();
    readVarList();
}

void GLSLProgram::use() {
    glUseProgram(idRenderProgram);
}

void GLSLProgram::checkLinkerErrors() {
    GLint linked;
    glGetProgramiv(idRenderProgram, GL_LINK_STATUS, &linked);
    if (linked != GL_TRUE) {
        GLsizei log_length = 0;
        char message[1024];
        glGetProgramInfoLog(idRenderProgram, 1024, &log_length, message);
        std::cout << "ERROR \n" << message << "\n\n";
    }
    else {
        std::cout << "[GLSLProgram] Programa linkado correctamente\n";
    }
}

void GLSLProgram::readVarList() {
    glUseProgram(this->idRenderProgram);
    // Leer identificadores variables Attributtes
    int numAttributes = 0;
    glGetProgramiv(idRenderProgram, GL_ACTIVE_ATTRIBUTES, &numAttributes);
    for (int i = 0; i < numAttributes; i++)
    {
        char name[101];
        int bufSize = 100, length = 0, size = 0;
        unsigned int type = -1; //GLEnum para float, char...
        glGetActiveAttrib(idRenderProgram, (GLuint)i, bufSize, &length, &size, &type, name);
        int layout = glGetAttribLocation(idRenderProgram, name);
        varList[string(name)] = layout;
    }

    // Leer identificadores variables Uniform
    int numUniforms = 0;
    glGetProgramiv(idRenderProgram, GL_ACTIVE_UNIFORMS, &numUniforms);
    for (int i = 0; i < numUniforms; i++)
    {
        char name[101];
        int bufSize = 100, length = 0, size = 0;
        unsigned int type = -1; //GLEnum para float, char...
        glGetActiveUniform(idRenderProgram, (GLuint)i, bufSize, &length, &size, &type, name);
        int layout = glGetUniformLocation(idRenderProgram, name);
        varList[std::string(name)] = layout;
    }
}

void GLSLProgram::setColorTextEnable(string name) {
    setInt("mat.use" + name, 1);
}

void GLSLProgram::setColorTextDisable(string name) {
    setInt("mat.use" + name, 0);
}

void GLSLProgram::bindColorTextureSampler(int binding, Texture* text, string name) {
    GLTexture* glTex = dynamic_cast<GLTexture*>(text);
    if (!glTex) return;
    GLuint textureId = glTex->getGLTextId();

    glActiveTexture(GL_TEXTURE0 + binding);
    if (glTex->isCubic()) {
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    } else {
        glBindTexture(GL_TEXTURE_2D, textureId);
    }
    glUniform1i(getVarLocation(name), binding);
}


unsigned int GLSLProgram::getVarLocation(std::string varName) {
    if (varList.find(varName) != varList.end())
        return varList[varName];
    else {
        std::cout << "ERROR: variable " << varName << " no encontrada en shader\n";
        return -1;
    }
}


// SETTERS
void GLSLProgram::setInt(const string& name, int val) {
    auto location = getVarLocation(name);
    if (location != (unsigned int)-1) {
        glUniform1i(location, val);
    }
}

void GLSLProgram::setFloat(const std::string& name, float val) {
    auto location = getVarLocation(name);
    if (location != (unsigned int)-1) {
        glUniform1f(location, val);
    }
}

void GLSLProgram::setVec3(const std::string& name, const glm::vec3& vec) {
    auto location = getVarLocation(name);
    if (location != (unsigned int)-1) {
        glUniform3f(location, vec.x, vec.y, vec.z);
    }
}

void GLSLProgram::setVec4(const std::string& name, const glm::vec4& vec) {
    auto location = getVarLocation(name);
    if (location != (unsigned int)-1) {
        glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
    }
}

void GLSLProgram::setMatrix(const std::string& name, const glm::mat4& mat) {
    auto location = getVarLocation(name);
    if (location != (unsigned int)-1) {
        glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
    }
}

void GLSLProgram::setCulling(bool culling) {
    culling ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
}

void GLSLProgram::setDepthWrite(bool depthWrite) {
    depthWrite ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

void GLSLProgram::setBlendMode(BlendMode blendMode) {
    switch (blendMode) {
    case BlendMode::NONE:
        glBlendFunc(GL_SRC_COLOR, GL_ZERO);
        glDisable(GL_BLEND);
        break;
    case BlendMode::ALPHA:
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        break;
    case BlendMode::MUL:
        glBlendFunc(GL_DST_COLOR, GL_ZERO);
        glEnable(GL_BLEND);
        break;
    case BlendMode::ADD:
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glEnable(GL_BLEND);
        break;
    }
}