#include "GLTexture.h"
#include "GLSLShader.h"
#include "../data/stb_image.h"

// Constructor
GLTexture::GLTexture() : Texture(), glTextId(0) {}

// Constructor 2D
GLTexture::GLTexture(const std::string& fileName) : Texture(fileName), glTextId(0) {
    update();
}

// Constructor Cubemap
GLTexture::GLTexture(const std::string& left, const std::string& right,
                     const std::string& front, const std::string& back,
                     const std::string& top, const std::string& bottom)
    : Texture(left, right, front, back, top, bottom), glTextId(0)
{
    update();
}

// Destructor
GLTexture::~GLTexture() {
    if (glTextId) {
        glDeleteTextures(1, &glTextId);
    }
}

// Getters y Setters
GLuint GLTexture::getGLTextId() const {
    return glTextId;
}

void GLTexture::setGLTextId(GLuint id) {
    glTextId = id;
}


// Método para subir la textura a la GPU
void GLTexture::update() {
    if (cubemap) {
        // Cargar las 6 imagenes en memoria (orden: left, right, front, back, top, bottom)
        int w, h, components = 0;
        unsigned char* faces[6];
        for (int i = 0; i < 6; i++)
            faces[i] = stbi_load(fileNames[i].c_str(), &w, &h, &components, 4);

        // Subir cubemap a la GPU
        glGenTextures(1, &glTextId);
        glBindTexture(GL_TEXTURE_CUBE_MAP, glTextId);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Copiar bytes de cada cara: [0]=left/-X  [1]=right/+X  [2]=front/+Z  [3]=back/-Z  [4]=top/+Y  [5]=bottom/-Y
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, faces[1]);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, faces[0]);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, faces[4]);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, faces[5]);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, faces[2]);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, faces[3]);

        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

        for (int i = 0; i < 6; i++)
            stbi_image_free(faces[i]);

        std::cout << "[INFO] Cubemap subido a GPU con ID: " << glTextId << std::endl;
    }
    else {
        // Textura 2D normal
        if (rawImage.empty()) {
            std::cerr << "[ERROR] No hay datos de textura para cargar en OpenGL." << std::endl;
            return;
        }
        // Generar Id de textura de OpenGL
        glGenTextures(1, &glTextId);
        glBindTexture(GL_TEXTURE_2D, glTextId);


        // Activar Filtros
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, bilinear ? GL_LINEAR : GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, bilinear ? GL_LINEAR : GL_NEAREST);
        // Configurar uso
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE);

        //Cargar en GPU datos de textura
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, rawImage.data());
        
        // Generar Mipmaps
        glGenerateMipmap(GL_TEXTURE_2D);

        std::cout << "[INFO] Textura 2D subida a la GPU con ID: " << glTextId << std::endl;
    }
}
