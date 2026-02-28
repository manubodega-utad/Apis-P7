#include "GLTexture.h"
#include "GLSLShader.h"

// Constructor
GLTexture::GLTexture() : Texture(), glTextId(0) {}

// Constructor
GLTexture::GLTexture(const std::string& fileName) : Texture(fileName), glTextId(0) {
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

    std::cout << "[INFO] Textura subida a la GPU con ID: " << glTextId << std::endl;
}
