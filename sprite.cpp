#include "sprite.h"

sprite::sprite(std::string imagename)
{
    texture = LoadTexture(imagename);
    xposition = 0;
    yposition = 0;
    pivotx = 0;
    pivoty = 0;
    angle = 0;
}
