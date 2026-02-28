#pragma once

#include "Texture.h"

class GLTexture : public Texture {
private:
    GLuint glTextId; // ID de textura en OpenGL

public:
    // Constructor y Destructor
    GLTexture();
    GLTexture(const std::string& fileName);
    ~GLTexture();

	// Getters y Setters
    GLuint getGLTextId() const;
    void setGLTextId(GLuint id);

    // Métodos
    void update() override;
};
