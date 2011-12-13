#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include "shaders.h"
#include "fileIO.h"

extern textureList *textures; // :(

class sprite
{
public:
    sprite(std::string imagename);
    ~sprite();
    void setTexture(std::string imagename);
    void setShader(unsigned int toSet);
    void rotate(int degrees);
    void setPosition(double x, double y);
    void setPivot(unsigned int x, unsigned int y);
    void setSizeToTexture();
    void setSize(int x, int y);
    void render();
private:
    unsigned int texture; //Currently assigned opengl texture
    unsigned int spriteShader; //Currently assigned opengl shader (add moar?)
    bool shaderUse;
    double xposition, yposition; //Raw position, from lower left corner (0,0)
    unsigned int pivotx, pivoty; //Points from which the sprite can pivot
    int angle; //Rotation
//    unsigned int texwidth, texheight; //Another instance of more memory -> faster
    int width, height;
//    float texx, texy; //Again. Also, might remove. Oh, and they're for texels
};

#endif // SPRITE_H
