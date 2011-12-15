#include "sprite.h"

sprite::sprite(std::string imagename)
{
    this->texture = textures->loadTexture(imagename);
    this->xposition = 0;
    this->yposition = 0;
    this->pivotx = 0;
    this->pivoty = 0;
    this->angle = 0;
    textures->selectTexture(this->texture,0);
    this->height = textures->current->ysize;
    this->width = textures->current->xsize;
}

sprite::~sprite()
{
    //this->FUCK SHIT UP
}

void sprite::setTexture(std::string imagename)
{
    this->texture = textures->loadTexture(imagename); //Add better error handling. Enough segfaults
}

void sprite::setShader(unsigned int toSet)
{
    this->spriteShader = toSet;
    this->shaderUse = true;
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

void sprite::setPosition(double x, double y)
{
    this->xposition = x/2;//merp? UGLY
    this->yposition = y/2;
}

void sprite::setSizeToTexture() //change to scaling?
{
    textures->selectTexture(this->texture,0);
    this->width = textures->current->xsize;
    this->height = textures->current->ysize;
}

void sprite::setSize(int x, int y)
{
    this->width = x;
    this->height = y;
}

void sprite::render()
{
    glBindTexture(GL_TEXTURE_2D,this->texture);
    glPushMatrix();
    glTranslatef(this->xposition,this->yposition,0);
//    glRotated(this->angle,1,0,0);
    glUseProgram(this->spriteShader);
    glBegin(GL_QUADS); //MAKE THIS BETTER
        glTexCoord2f(0,0); glVertex2d(this->xposition,this->yposition);
        glTexCoord2f(1,0); glVertex2d(this->xposition+this->width,this->yposition);
        glTexCoord2f(1,1); glVertex2d(this->xposition+this->width,this->yposition+this->height);
        glTexCoord2f(0,1); glVertex2d(this->xposition,this->yposition+this->height);
    glEnd();
    glUseProgram(0);
    glPopMatrix();
}

//Add sprite::update() ?
