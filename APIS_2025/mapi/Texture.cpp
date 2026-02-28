#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../data/stb_image.h"

// Constructor
Texture::Texture() : textID(0), size(0, 0), cubemap(false), bilinear(false), repeat(true)
{
}

Texture::Texture(const std::string& fileName) : Texture()
{
	load(fileName);
    this->fileName = fileName;
}

// Getters
uint32_t Texture::getTextID() const {
    return textID;
}

glm::ivec2 Texture::getSize() const {
    return size;
}

bool Texture::isCubemap() const {
    return cubemap;
}

const std::vector<pixel_t>& Texture::getRawImage() const {
    return rawImage;
}

const std::string& Texture::getFileName() const {
    return fileName;
}

bool Texture::isBilinear() const {
    return bilinear;
}

bool Texture::isRepeat() const {
    return repeat;
}


// Setters
void Texture::setBilinear(bool value) {
    bilinear = value;
}

void Texture::setRepeat(bool value) {
    repeat = value;
}


// Métodos
void Texture::load(const std::string& filename) {
    int width, height;
    int channels = 0;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 4);

    if (data) {
        size = glm::ivec2(width, height);
		rawImage.resize(width * height);
		memcpy(rawImage.data(), data, width * height * 4);

        stbi_image_free(data);
        std::cout << "[INFO] Textura cargada desde: " << filename << " (" << width << "x" << height << ")" << std::endl;
    }
    else {
        std::cerr << "[ERROR] No se pudo cargar la textura: " << filename << std::endl;
    }

    
}

