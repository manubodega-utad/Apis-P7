#pragma once
#include "common.h"

#define byte unsigned char
typedef struct {
    byte r, g, b, a;
}pixel_t;

class Texture {
protected:
    uint32_t textID; // ID de la textura en OpenGL
    glm::ivec2 size; // Tamaño en pixeles de la textura a lo largo de los ejes X/Y
    bool cubemap; // Indica si la textura es un cúbica (De momento false)
    std::vector<pixel_t> rawImage; // Bytes de la textura cargada en memoria
    std::vector<std::string> fileNames; // Archivos de textura
    bool bilinear; // Variable que indideca si se debe aplicar un filtro bilinear
    bool repeat; // Variable que indica si las coordenadas de textura mayores que 1.0 o menores que 

public:
    // Constructores
    Texture();
    Texture(const std::string& fileName);
    Texture(const std::string& left, const std::string& right,
            const std::string& front, const std::string& back,
            const std::string& top, const std::string& bottom);
    virtual ~Texture() {}

    // Métodos de carga
    void load(const std::string& filename);
    void load(const std::string& left, const std::string& right,
              const std::string& front, const std::string& back,
              const std::string& top, const std::string& bottom);
    virtual void update() {}

    // Getters
    uint32_t getTextID() const;
    glm::ivec2 getSize() const;
    bool isCubemap() const;
    bool isCubic() const { return cubemap; }
    const std::vector<pixel_t>& getRawImage() const;
    const std::string& getFileName() const;
    bool isBilinear() const;
    bool isRepeat() const;
    pixel_t getPixel(int x, int y) const;

    // Setters
    void setBilinear(bool value);
    void setRepeat(bool value);
};
