/*
  DISCLAIMER: Anything in main.cpp is hackish and probably poor practice. This is not to say
  that the other files are perfect, but main.cpp is simply a testing framework. It will
  probably not work on your computer. In fact, it will probably break horribly.
*/

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "fileIO.h"
#include "renderer.h"
#include "shaders.h"
#include "sprite.h"

#define RESOURCES "resources/"

//Bad, bad globals...temporary until engine class

bool program_running = 1;

bool wdown, adown, sdown, ddown, qdown, edown,
        leftdown,rightdown,updown,downdown;

unsigned int ticks;

shader test;
textureList *textures;

#define mapresx 6000
#define mapresy 2906


int main(int argc, char *argv[])
{


    int videoFlags;
    SDL_Surface *surface;
    SDL_Event event;
    textures = new textureList;

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
	  make windows like it
    */
   /* char *filepath;
    std::string runningdir;
    long size;
    size = pathconf(".", _PC_PATH_MAX);
    filepath = new char[size];
    getcwd(filepath, (size_t)size);
    runningdir = filepath;
    delete [] filepath;
    printf("LOG: launch dir: %s\n",runningdir.c_str()); */

    /* it's much faster to store these in seperate vars */
//    unsigned long tex = textures->loadTexture(RESOURCES"outline.png");
    unsigned long tex2 = textures->loadTexture(RESOURCES"hubble1.jpg");
//    unsigned long tex3 = textures->loadTexture(RESOURCES"ship.png");

    int backgroundx = 0;
    int backgroundy = 0;
    int camx, camy;
    int spritex = 0;
    int spritey=0;
    float scale = 1;

    float texx,texy;
    sprite *testy = new sprite(RESOURCES"outline.png");
    sprite *tester = new sprite(RESOURCES"outline.png");
    testy->setPosition(0.0,0.0);
    tester->setPosition(501.0,501.0);
//    testy->setSizeToTexture();
    testy->setSize(501,501);
    tester->setSize(501,501);
    /* redundant, but testing */
    textures->selectTexture(RESOURCES"hubble1.jpg");
    textures->selectTexture(tex2);

    texx = (float)xres/textures->current->xsize;
    texy = (float)yres/textures->current->ysize;

    test.loadFromFile(RESOURCES"vertexshader.vert",
                      RESOURCES"fragmentshader.frag");

    test.compileShader();
    test.linkShader();
    test.printLog(test.programObject);

//    glUniform1i(glGetUniformLocation(test.programObject,"bgl_RenderedTexture"),tex);

//    glUniform1i(glGetUniformLocation(test.programObject,"texture"),GL_TEXTURE1);

    while(program_running)
    {
        // Grab events - Setting vars prevents unnecessary polling later
        // Also - Split this into input.cpp or something later
    ticks = SDL_GetTicks();
        if (ticks%20) //every 20ms, update)
        {
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
                    case SDLK_e:
                        edown = !edown;
                        break;
                    case SDLK_q:
                        qdown = !qdown;
                        break;
                    case SDLK_UP:
                        updown = !updown;
                        break;
                    case SDLK_DOWN:
                        downdown = !downdown;
                        break;
                    case SDLK_LEFT:
                        leftdown = !leftdown;
                        break;
                    case SDLK_RIGHT:
                        rightdown = !rightdown;
                        break;
                    case SDLK_ESCAPE:
                        program_running = false;
                    default:
                        break;
                }
            }

            if(adown){
                backgroundx+=1;
                camx++;
            }
            if(ddown){
                camx--;
                backgroundx-=1;
            }
            if(wdown){
                camy--;
                backgroundy-=1;
            }
            if(sdown) {
                backgroundy+=1;
                camy++;
            }
            if(qdown)
                scale-=0.001;
            if(edown)
                scale+=0.001;
            if(rightdown)
                spritex++;
            if(leftdown)
                spritex--;
            if(updown)
                spritey++;
            if(downdown)
                spritey--;

        }

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex2);
        glPushMatrix();
        glTranslatef(backgroundx/2, backgroundy/2, 0); //offload this to the shader? probably should
//        test.useShader(true);
        glBegin(GL_QUADS);
//            glTexCoord2f(0,0); glVertex2d((-1*mapresx),(-1*mapresy));
//            glTexCoord2f(1,0); glVertex2d(mapresx,(-1*mapresy));
//            glTexCoord2f(1,1); glVertex2d(mapresx,mapresy);
//            glTexCoord2f(0,1); glVertex2d((-1*mapresx),mapresy);
            glTexCoord2f(0,0); glVertex2d(0,0);
            glTexCoord2f(1,0); glVertex2d(mapresx,0);
            glTexCoord2f(1,1); glVertex2d(mapresx,mapresy);
            glTexCoord2f(0,1); glVertex2d(0,mapresy);
//            glTexCoord2f(0,0); glVertex2d(0,0);
//            glTexCoord2f(texx,0); glVertex2d(xres,0);
//            glTexCoord2f(texx,texy); glVertex2d(xres,yres);
//            glTexCoord2f(0,texy); glVertex2d(0,yres);
        glEnd();
        glPopMatrix();
        test.useShader(false);

        testy->render();
        tester->setPosition(spritex,spritey);
        tester->render();

        glLoadIdentity();
        glScalef(scale,scale,1);
        glTranslatef(camx,camy,0);

        glFlush();
        glFinish();
        SDL_GL_SwapBuffers();

    }
    SDL_Quit();

    return 0;
}
