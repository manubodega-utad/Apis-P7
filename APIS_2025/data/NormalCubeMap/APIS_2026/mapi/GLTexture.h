#pragma once
#include "common.h"

using namespace std;

#define byte unsigned char


typedef struct {
    byte r;
    byte g;
    byte b;
    byte a;

}pixel_t;

typedef enum {
    texture2d=GL_TEXTURE_2D,
    textureCube=GL_TEXTURE_CUBE_MAP,
    textureColorFB= GL_RGBA,
    textureDepthFB= GL_DEPTH_COMPONENT
}textureType;

class GLTexture
{
public:
    vector<pixel_t> rawImage;
    int w;
    int h;
    string textureName;
    vector<unsigned char*> cubeTextures;

    GLuint GlTextID;
    textureType type;
    GLTexture() {};
    GLTexture(string fileName);
    GLTexture(vector<string> &fileNames);

    pixel_t& getPixel(int x, int y) { return rawImage[y * w + x]; };
    
    void updateTexture();

};

class GLTextureFB:public GLTexture {

public :

    GLTextureFB(string textureName, textureType type, int w, int h);

};

