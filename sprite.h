#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include "fileIO.h"

class sprite
{
public:
    sprite(std::string imagename);
    void setTexture(std::string imagename);
    void rotate(int degrees);
    void setPosition(unsigned int x, unsigned int y);
    void setPivot(unsigned int x, unsigned int y);
    void render();
private:
    unsigned int texture; //Currently assigned opengl texture
    unsigned int xposition, yposition; //Raw position, from lower left corner (0,0)
    unsigned int pivotx, pivoty; //Points from which the sprite can pivot
    int angle; //Rotation

};

#endif // SPRITE_H
