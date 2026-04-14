#pragma once

#include "Texture.h"

class GLTexture : public Texture {
private:
    GLuint glTextId; // ID de textura en OpenGL

public:
    // Constructor y Destructor
    GLTexture();
    GLTexture(const std::string& fileName);
    GLTexture(const std::string& left, const std::string& right,
              const std::string& front, const std::string& back,
              const std::string& top, const std::string& bottom);
    ~GLTexture();

    // Getters y Setters
    GLuint getGLTextId() const;
    void setGLTextId(GLuint id);
    bool isCubic() const { return cubemap; }

    // Métodos
    void update() override;
};
