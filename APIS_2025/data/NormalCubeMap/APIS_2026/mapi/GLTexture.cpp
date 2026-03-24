#include "GLTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


GLTexture::GLTexture(string fileName): textureName(fileName)
{
    //cargar imagen de fichero
    int componentes = 0;
    this->type = texture2d;
    unsigned char* data = stbi_load(textureName.c_str(), &w, &h, &componentes, 4);
    if(data){
        rawImage.resize(w * h);
        memcpy(rawImage.data(), data, w * h * 4);
    //cargar imagen en GPU
        //generar id de textura de OPENGL
        glGenTextures(1, &GlTextID);
        glBindTexture(GL_TEXTURE_2D, GlTextID);
        //activar filtros
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//filtros
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //configurar uso
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        //cargar en GPU datos de textura
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, rawImage.data());
        //generar mipmaps
        glGenerateMipmap(GL_TEXTURE_2D);
     //liberar datos de cpu
        stbi_image_free(data);
    }
    else {
        cout << "ERROR: Fichero " << fileName << " no encontrado\n";
    }
}

GLTexture::GLTexture(vector<string>& fileNames)
{
    this->type = textureCube;

    //cargar las 6 imágenes en 6 arrays de datos: dright,dleft,dfront,dback,dtop,dbottom
    unsigned char* dright, * dleft, * dfront, * dback, * dtop, * dbottom;
    int components=0;
    dleft = stbi_load(fileNames[0].c_str(), &w, &h, &components, 4);
    dright= stbi_load(fileNames[1].c_str(),&w,&h,&components,4);
    dfront= stbi_load(fileNames[2].c_str(),&w,&h,&components,4);
    dback= stbi_load(fileNames[3].c_str(),&w,&h,&components,4);
    dtop= stbi_load(fileNames[4].c_str(),&w,&h,&components,4);
    dbottom= stbi_load(fileNames[5].c_str(),&w,&h,&components,4);

    cubeTextures = { dright,dleft,dfront,dback,dtop,dbottom };


    glGenTextures(1, &GlTextID);
    //activar para modificaciones
    glBindTexture(GL_TEXTURE_CUBE_MAP, GlTextID);
    //modificaciones
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //copiar bytes
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, dright);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, dleft);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, dbottom);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, dtop);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, dback);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, dfront);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

}

void GLTexture::updateTexture()
{
    switch (type) {
        case texture2d: {
            glBindTexture(GL_TEXTURE_2D, GlTextID);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, rawImage.data());
        }break;
        case textureCube: {
            glBindTexture(GL_TEXTURE_CUBE_MAP, GlTextID);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, cubeTextures[0]);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, cubeTextures[1]);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,cubeTextures[2]);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, cubeTextures[3]);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,cubeTextures[4]);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, cubeTextures[5]);
        }break;
    }
}

GLTextureFB::GLTextureFB(string textureName, textureType type, int w, int h)
{
        this->type = type;
        this->w = w;
        this->h = h;
        glGenTextures(1, &this->GlTextID);
        glBindTexture(GL_TEXTURE_2D, GlTextID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        switch (type)
        {
        case textureColorFB:
        {
            //color
            //al reservar el espacio de la textura, no se inician los colores (nullptr)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        }break;
        case textureDepthFB:
        {
            //profundidad
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, w, h, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);
        }break;
        }
    }
