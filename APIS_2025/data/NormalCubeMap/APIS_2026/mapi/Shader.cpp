#include "Shader.h"

Shader::Shader(string fileName)
{
    //leer fichero
    char* code = nullptr;
    FILE* f = fopen(fileName.c_str(), "r");
    if (!f) cout << "Error Fichero " << fileName << " no existe\n";
    else{

        //determinar tipo de shader
        if (fileName.ends_with(".vert"))
            this->shaderType = GL_VERTEX_SHADER;
        if (fileName.ends_with(".frag"))
            this->shaderType = GL_FRAGMENT_SHADER;

        //compilar
            //crear identificador
        this->shaderId=glCreateShader(shaderType);
            //añadir codigo
        fseek(f, 0,SEEK_END);
        GLint fileSize = ftell(f);
        fseek(f, 0, SEEK_SET);
        code = new char[fileSize];
        fread(code, fileSize, 1, f);//leer
        fclose(f);
        
        glShaderSource(shaderId, 1, &code, &fileSize);
        glCompileShader(shaderId);

        //detectar errores de compilado
        GLint retCode;
        char errorLog[1024];
        GLint fragment_compiled;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &fragment_compiled);
        if (fragment_compiled != GL_TRUE)
        {
            GLsizei log_length = 0;
            GLchar message[1024];
            glGetShaderInfoLog(shaderId, 1024, &log_length, message);
            std::cout << "ERROR " << fileName << "\n" << message << "\n\n";
        }
        else
        {
            compiled = true;
        }
            //liberar datos
        free(code);

    }
}
