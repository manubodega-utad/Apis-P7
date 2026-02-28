#include "GLSLShader.h"
#include "common.h"

GLSLShader::GLSLShader(const std::string& fileName)
    : Program(fileName){}

GLSLShader::~GLSLShader() 
{}

// Método para leer un archivo de texto
void GLSLShader::readFile() {
    std::ifstream f(fileName);
    if (f.is_open()) {
        code = std::string(std::istreambuf_iterator<char>(f), {});
    }
    else {
        std::cout << "ERROR: FICHERO NO ENCONTRADO " <<
            __FILE__ << ":" << __LINE__ << " " << fileName << "\n";
    }
}


void GLSLShader::compile() {
    // Validar si hay código cargado
    if (code.empty()) {
        readFile();
        if (code.empty()) {
            std::cout << "ERROR: Shader vacío o no leído: " << fileName << "\n";
            return;
        }
    }

    // Crear un shader de OpenGL (GL_VERTEX_SHADER o GL_FRAGMENT_SHADER)
    GLenum glType = (type == programTypes_e::vertex) ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
    idProgram = glCreateShader(glType);

    // Cargar el source
    const char* cod = code.c_str();
    GLint filesize = static_cast<GLint>(code.size());
    glShaderSource(idProgram, 1, &cod, &filesize);
    glCompileShader(idProgram);

	checkErrors();
}


// Método para averiguar si ha habido errores al compilar un shader
void GLSLShader::checkErrors() {
    GLint fragment_compiled;
    glGetShaderiv(idProgram, GL_COMPILE_STATUS, &fragment_compiled);
    if (fragment_compiled != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(idProgram, 1024, &log_length, message);
        std::cout << "ERROR " << fileName << "\n" << message << "\n\n";
    }
}

