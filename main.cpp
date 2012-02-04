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

#define VERSION "devtest"
#define RESOURCES "resources/"
#define mapresx 6000
#define mapresy 2906

//Bad, bad globals...temporary until engine class
shader test;
textureList *textures;
unsigned int ticks;
bool program_running = 1;
bool wdown, adown, sdown, ddown, qdown, edown,
        leftdown,rightdown,updown,downdown;

int main(int argc, char *argv[])
{
	float backgroundx = 0;
    float backgroundy = 0;
    int camx = 0;
	int camy = 0;
    int spritex = 0;
    int spritey=0;
    float scale = 1;
    static unsigned int frames = 0;
    static unsigned int ti = 0;
    static unsigned int tf;
    static float seconds, fps;
	unsigned long tex2;
	int videoFlags;

	SDL_Surface *surface;
    SDL_Event event;
	sprite *testy;
	sprite *tester;

    printf("LAUNCH: (%d args) %s\n",argc-1,*argv);

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

    /* get an SDL surface */
    surface = SDL_SetVideoMode(xres, yres, bpp, videoFlags);
    if (!surface)
    {
            printf("Fatal: Video mode set failed with: %s\n", SDL_GetError());
            return 1;
    }

	SDL_WM_SetCaption(VERSION, NULL);
    initGL();
	textures = new textureList;

	/* load us some resources!
		- it's much faster to store these in seperate vars */
//  tex = textures->loadTexture(RESOURCES"outline.png");
//  tex3 = textures->loadTexture(RESOURCES"ship.png");
    tex2 = textures->loadTexture(RESOURCES"hubble1.jpg");
    testy = new sprite(RESOURCES"outline.png");
    tester = new sprite(RESOURCES"ship.png");
	
	/* positions! */
    testy->setPosition(500.0,500.0);
    tester->setPosition(501.0,501.0);


    testy->setSize(501,501);
    testy->rotate(34);
    tester->setSize(250,250);

    /* redundant, but testing */
    textures->selectTexture(RESOURCES"hubble1.jpg",0);
    textures->selectTexture(tex2,0);

	/* load the shader sources */
    test.loadFromFile(RESOURCES"vertexshader.vert",
                      RESOURCES"fragmentshader.frag");
	/* prepare the shader */
    test.compileShader();
    test.linkShader();
    test.printLog(test.programObject);

	/* [TODO] assign the texture unit to the shader */
    glUniform1i(glGetUniformLocation(test.programObject,"bgl_RenderedTexture"),textures->selectTexture(RESOURCES"ship.png",true));

	/* assign the finished shader to a sprite */
    tester->setShader(test.programObject);

	/* and we're done! */
	printf("INFO: Entering main loop at %d ms.\n\n",SDL_GetTicks());


    while(program_running)
    {
        // Grab events - Setting vars prevents unnecessary polling later
        // Also - Split this into input.cpp or something later
        ticks = SDL_GetTicks();
        if (ticks%20) //every 20ms, update)
        {
            while (SDL_PollEvent(&event))
            {
				switch(event.type){
				case SDL_VIDEORESIZE:
					//surface = SDL_SetVideoMode(event.resize.w,event.resize.h,
												//bpp,videoFlags);
					if(!surface)
					{
						printf("Error resizing!\n");
						program_running = false;
					}
					resizeWindow(event.resize.w,event.resize.h);
					printf("w:%d h:%d\n",event.resize.w,event.resize.h);
					break;
				default:
					break;
				}
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
                backgroundx--;
                camx++;
            }
            if(ddown){
                camx--;
                backgroundx++;
            }
            if(wdown){
                camy--;
                backgroundy++;
            }
            if(sdown) {
                backgroundy--;
                camy++;
            }
            if(qdown)
                scale-=0.005;
            if(edown)
                scale+=0.005;
            if(rightdown)
                spritex++;
            if(leftdown)
                spritex--;
            if(updown)
                spritey++;
            if(downdown)
                spritey--;

        }

        frames++;
        {
            tf = SDL_GetTicks();
            if (tf - ti >= 1500) {
                seconds = (tf - ti) / 1000.0;
                fps = frames/seconds;
                printf("%d frames in %g seconds = %g FPS\n", frames, seconds, fps);
                ti = tf;
                frames = 0;
            }
        }
        glEnable(GL_TEXTURE_2D);
		//test.useShader(true);
        glBindTexture(GL_TEXTURE_2D, tex2);
        glPushMatrix();
        glTranslatef(backgroundx*0.4,backgroundy*0.4, 0); //offload this to the shader? probably should
        glBegin(GL_QUADS);
            glTexCoord2f(0,0); glVertex2d(0,0);
            glTexCoord2f(1,0); glVertex2d(mapresx,0);
            glTexCoord2f(1,1); glVertex2d(mapresx,mapresy);
            glTexCoord2f(0,1); glVertex2d(0,mapresy);
        glEnd();
        glPopMatrix();
		//test.useShader(false);
        testy->render();

        tester->setPosition(spritex,spritey);
        tester->render();

        glLoadIdentity();
        glScalef(scale,scale,1);
        glTranslatef(camx,camy,0);

        SDL_GL_SwapBuffers();
    }
    SDL_Quit();
    return 0;
}
