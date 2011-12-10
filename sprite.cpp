#include "sprite.h"

sprite::sprite(std::string imagename)
{
    this->texture = textures->loadTexture(imagename);
    this->xposition = 0;
    this->yposition = 0;
    this->pivotx = 0;
    this->pivoty = 0;
    this->angle = 0;
    textures->selectTexture(this->texture);
//    this->texwidth = textures->current->xsize;
//    this->texheight = textures->current->ysize;
}

sprite::~sprite()
{
    //this->FUCK SHIT UP
}

void sprite::setTexture(std::string imagename)
{
    this->texture = textures->loadTexture(imagename);
}

void sprite::rotate(int degrees)
{
    this->angle = degrees;
    this->angle%=360;
}

void sprite::setPivot(unsigned int x, unsigned int y)
{
    if(x > this->pivotx || x < this->pivotx)
        x = this->pivotx;
    if(y > this->pivoty || y < this->pivoty)
        y = this->pivoty;
    this->pivotx = x;
    this->pivoty = y;
}

void sprite::setPosition(unsigned int x, unsigned int y)
{
    this->xposition = x;
    this->yposition = y;
}

void sprite::setSizeToTexture() //change to scaling?
{
    textures->selectTexture(this->texture);
    this->width = textures->current->xsize;
    this->height = textures->current->ysize;
}

void sprite::render()
{
//    texx = (float)this->xposition/this->texwidth;
//    texy = (float)this->yposition/this->texheight;

    glBindTexture(GL_TEXTURE_2D,this->texture);
    glPushMatrix();
    glTranslatef(this->xposition,this->yposition,0);

    glBegin(GL_QUADS); //MAKE THIS BETTER
    glTexCoord2f(0,0); glVertex2d(this->xposition,this->yposition);
    glTexCoord2f(1,0); glVertex2d(this->xposition+this->width,this->yposition);
    glTexCoord2f(1,1); glVertex2d(this->xposition+this->width,this->yposition+this->height);
    glTexCoord2f(0,1); glVertex2d(this->xposition,this->yposition+this->height);
    glEnd();
    glPopMatrix();
}

//Add sprite::update() ?
