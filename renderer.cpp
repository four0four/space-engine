#include "renderer.h"

void initGL()
{
    glewInit();

    glViewport(0,0,xres, yres);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, xres, 0.0f, yres, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);//,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
}

void resizeWindow(int w, int h)
{
	if(h==0)
		h = 1;
	//glewInit();
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, w, 0.0f, h, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);//,GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_BLEND);
    //glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT);
    //glDisable(GL_DEPTH_TEST);
    //glDisable(GL_LIGHTING);
}
