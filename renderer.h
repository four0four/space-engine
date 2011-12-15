#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GL/gl.h>

#define xres 1366
#define yres 768
#define bpp 32

void initGL();
void resizeWindow(int w, int h);

#endif // RENDERER_H
