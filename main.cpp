/*
  DISCLAIMER: Anything in main.cpp is hackish and probably poor practice. This is not to say
  that the other files are perfect, but main.cpp is simply a testing framework. It will
  probably not work on your computer. In fact, it will probably break horribly.
*/
//#include <SFML/Window.hpp>
//#include <SFML/Graphics.hpp>
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <unistd.h>
#include "fileIO.h"
#include "renderer.h"
#include "shaders.h"

#define RESOURCES "/resources/"

bool program_running = 1;

bool wdown, adown, sdown, ddown;

shader test;

#define mapresx 6000
#define mapresy 2906


int main(int argc, char *argv[])
{
    int videoFlags;
    SDL_Surface *surface;
    SDL_Event event;
    textureList *textures = new textureList;

    /* initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Fatal: Video initialization failed at init() with %s\n", SDL_GetError());
        return 1;
    }

    /* the flags to pass to SDL_SetVideoMode */
    videoFlags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
    videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
    videoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */
    videoFlags |= SDL_RESIZABLE;       /* Enable window resizing */


    SDL_WM_SetCaption("devtest", NULL);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    /* get a SDL surface */
    surface = SDL_SetVideoMode(xres, yres, bpp,
                                videoFlags);
    if (!surface)
        {
            printf("Fatal: Video mode set failed with: %s\n", SDL_GetError());
            return 1;
        }
    initGL();


    /*
      HACK ALERT!
      move to init fxn (when created)
    */
    char *filepath;
    std::string runningdir;
    long size;
    size = pathconf(".", _PC_PATH_MAX);
    filepath = new char[size];
    getcwd(filepath, (size_t)size);
    runningdir = filepath;
    delete [] filepath;
    printf("LOG: launch dir: %s\n",runningdir.c_str());

    /* it's much faster to store these in seperate vars */
    unsigned long tex = textures->loadTexture(runningdir + RESOURCES"outline.png");
    unsigned long tex2 = textures->loadTexture(runningdir + RESOURCES"hubble1.jpg");
    unsigned long tex3 = textures->loadTexture(runningdir + RESOURCES"outline.png");
    int backgroundx = 0;
    int backgroundy = 0;

    test.loadFromFile(runningdir + RESOURCES"vertexshader.vert",
                      runningdir + RESOURCES"fragmentshader.frag");

    test.compileShader();
    test.linkShader();
    test.printLog(test.programObject);

    glUniform1i(glGetUniformLocation(test.programObject,"bgl_RenderedTexture"),tex);

    glUniform1i(glGetUniformLocation(test.programObject,"texture"),GL_TEXTURE1);

    while(program_running)
    {
        // Grab events - Setting vars prevents unnecessary polling later
        // Also - Split this into input.cpp or something later

        while (SDL_PollEvent(&event))
        {
            switch(event.key.keysym.sym){
                case SDLK_w:
                    wdown = !wdown;
                    break;
                case SDLK_s:
                    sdown = !sdown;
                    break;
                case SDLK_a:
                    adown = !adown;
                    break;
                case SDLK_d:
                    ddown = !ddown;
                    break;
                default:
                    break;
            }

        }

        if(adown)
            backgroundx+=1;
        if(ddown)
            backgroundx-=1;
        if(wdown)
            backgroundy-=1;
        if(sdown)
            backgroundy+=1;

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
        test.useShader(true);
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
        test.useShader(false);

        glBindTexture( GL_TEXTURE_2D, tex);
        glBegin(GL_QUADS);
            glTexCoord2i(0.0,0.0); glVertex2d(50.0,50.0);
            glTexCoord2i(1.0,0.0); glVertex2d(250.0,50.0);
            glTexCoord2i(1.0,1.0); glVertex2d(250.0,250.0);
            glTexCoord2i(0.0,1.0); glVertex2d(50.0,250.0);
        glEnd();


        test.useShader(true);
        glBindTexture(GL_TEXTURE_2D, tex3);
        glBegin(GL_QUADS);
            glTexCoord2i(0.0,0.0); glVertex2d(500.0,500.0);
            glTexCoord2i(1.0,0.0); glVertex2d(700.0,500.0);
            glTexCoord2i(1.0,1.0); glVertex2d(700.0,700.0);
            glTexCoord2i(0.0,1.0); glVertex2d(500.0,700.0);
        glEnd();
        test.useShader(false);

        SDL_GL_SwapBuffers();

    }
    SDL_Quit();

    return 0;
}
