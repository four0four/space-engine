/*
  DISCLAIMER: Anything in main.cpp is hackish and probably poor practice. This is not to say
  that the other files are perfect, but main.cpp is simply a testing framework. It will
  probably not work on your computer. In fact, it will probably break horribly.
*/
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "fileIO.h"
#include "renderer.h"
#include "shaders.h"

#define RESOURCES "./resources/"

bool program_running = 1;

bool wdown, adown, sdown, ddown;

shader test;

#define mapresx 6000
#define mapresy 2906

int main(int argc, char *argv[])
{
    sf::Window mainwin(sf::VideoMode(xres,yres,32),"devtest");
    gl_init();

    textureList *textures = new textureList;

    /* it's much faster to store these in seperate vars */
    unsigned long tex = textures->loadTexture(RESOURCES"outline.png");
    unsigned long tex2 = textures->loadTexture(RESOURCES"hubble1.jpg");
    unsigned long tex3 = textures->loadTexture(RESOURCES"outline.png");
    int backgroundx = 0;
    int backgroundy = 0;

    test.loadFromFile("/home/galen/programming/devtest/vertexshader.vert",
                      "/home/galen/programming/devtest/fragmentshader.frag");

    test.compileShader();
    test.linkShader();
    test.printLog(test.programObject);

    mainwin.EnableVerticalSync(false);

    while(program_running)
    {
        // Grab events - Setting vars prevents unnecessary polling later
        if (sf::Keyboard::IsKeyPressed(sf::Keyboard::A))
            adown = 1;
        else
            adown = 0;
        if (sf::Keyboard::IsKeyPressed(sf::Keyboard::S))
            sdown = 1;
        else
            sdown = 0;
        if (sf::Keyboard::IsKeyPressed(sf::Keyboard::W))
            wdown = 1;
        else
            wdown = 0;
        if (sf::Keyboard::IsKeyPressed(sf::Keyboard::D))
            ddown = 1;
        else
            ddown = 0;
        if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Escape))
            program_running = 0;
        if(sf::Keyboard::IsKeyPressed(sf::Keyboard::P))
            printf("backgroundx: %d, backgroundy: %d\n",backgroundx,backgroundy);

        if(adown)
            backgroundx++;
        if(ddown)
            backgroundx--;
        if(wdown)
            backgroundy--;
        if(sdown)
            backgroundy++;

        if(backgroundx > 0)
            backgroundx = 0;
        if(backgroundy > 0)
            backgroundy = 0;
        if(backgroundy < -2100)
            backgroundy = -2100;
        if(backgroundx < -4600)
            backgroundx = -4600;

        glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, tex2);
        glPushMatrix();
        glTranslatef(backgroundx, backgroundy, 0); //offload this to the shader? probably should
        glBegin(GL_QUADS);
//            glTexCoord2f(0,0); glVertex2d((-1*mapresx),(-1*mapresy));
//            glTexCoord2f(1,0); glVertex2d(mapresx,(-1*mapresy));
//            glTexCoord2f(1,1); glVertex2d(mapresx,mapresy);
//            glTexCoord2f(0,1); glVertex2d((-1*mapresx),mapresy);
            glTexCoord2f(0,0); glVertex2d(0,0);
            glTexCoord2f(1,0); glVertex2d(mapresx,0);
            glTexCoord2f(1,1); glVertex2d(mapresx,mapresy);
            glTexCoord2f(0,1); glVertex2d(0,mapresy);
        glEnd();
        glPopMatrix();
        glUseProgram(0);

        glBindTexture( GL_TEXTURE_2D, tex);
        glBegin(GL_QUADS);
            glTexCoord2i(0.0,0.0); glVertex2d(50.0,50.0);
            glTexCoord2i(1.0,0.0); glVertex2d(250.0,50.0);
            glTexCoord2i(1.0,1.0); glVertex2d(250.0,250.0);
            glTexCoord2i(0.0,1.0); glVertex2d(50.0,250.0);
        glEnd();

        glUseProgram(test.programObject);
        glUniform1i(glGetUniformLocation(test.programObject,"texture"),GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex3);
        glBegin(GL_QUADS);
            glTexCoord2i(0.0,0.0); glVertex2d(500.0,500.0);
            glTexCoord2i(1.0,0.0); glVertex2d(700.0,500.0);
            glTexCoord2i(1.0,1.0); glVertex2d(700.0,700.0);
            glTexCoord2i(0.0,1.0); glVertex2d(500.0,700.0);
        glEnd();
        glUseProgram(0);

        mainwin.Display();
    }

    return 0;
}
