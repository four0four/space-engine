#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <FreeImage.h>

class textureNode
{
public:
    /* filename - used to avoid duplicates
    */
    char filename[1024];
    /* keeps track of the objects using this
       texture. when it reaches 0, the texture
       is deleted
    */
    int usages;
    /*
       unique openGL-assigned ID
    */
    unsigned int textureObject;
    /*
       x and y size coords
    */
    unsigned int xsize, ysize;
    /*
      this is a linked list, after all
    */
    textureNode *next;
};

class textureList
{
private:
//    unsigned int currentPosition;
//    unsigned int totalElements;
//    void append(textureNode *tex); //to public?
//    void insert(textureNode *tex, unsigned int position); //remove/modify?
//    void remove(textureNode *tex);
//    textureNode *searchList(std::string imagename);
public:
    textureNode *top;
    textureNode *bottom;
    textureNode *current;
    /*
      loads a texture from the image at filename and returns the ID
      if filename has already been loaded, returns that texture ID
    */
    unsigned int loadTexture(std::string filename);
	void init();
    void unloadTexture(std::string filename);
    void unloadTexture(unsigned int texID);
    void forceUnloadTexture(std::string filename);
    void forceUnloadTexture(unsigned int texID);
    unsigned int selectTexture(std::string filename, bool reserve);
    unsigned int selectTexture(unsigned int texID, bool reserve);
    textureList();
    ~textureList();
};

unsigned int LoadTexture(std::string image);

#endif // FILEIO_H
