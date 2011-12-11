#include "fileIO.h"



unsigned int textureList::loadTexture(std::string imagename)
{
    printf("INFO: Loading texture: %s\n",imagename.c_str());

    if(imagename.size() > 1023) //fix this later
    {
        printf("stop overflowing!\n");
        return -1;
    }
    current = bottom;
    while(current)
    {
        if(strcmp(imagename.c_str(),current->filename))
            current = current->next;
        else
        {
            current->usages++;
            printf("- Duplicate of ID #%d found - Usages: %d\n",current->textureObject,current->usages);
            return current->textureObject;
            break;
        }
    }

    current = bottom;
    while(current->next)
        current = current->next;

    current->next = new textureNode;
    //For now, leave the anchor alone
//    if(strcmp(current->filename,"first")) //If the list is empty, use the anchor
        current = current->next;
    current->next = NULL;
    strcpy(current->filename,imagename.c_str());

    unsigned int texture;
    FREE_IMAGE_FORMAT format;

    if((format = FreeImage_GetFileType(imagename.c_str(),0)) == -1)
    {
        printf("ERROR: Unable to load texture %s!\n",imagename.c_str()); //Set some flag?
        return -1;
    }

    FIBITMAP * imagedata = FreeImage_Load(format, imagename.c_str(),0);
    imagedata = FreeImage_ConvertTo32Bits(imagedata);

    int height = FreeImage_GetHeight(imagedata);
    int width = FreeImage_GetWidth(imagedata);

    GLubyte* pixels = new GLubyte[4*width*height];

    GLubyte * pixelraw = FreeImage_GetBits(imagedata);

    // FreeImage loads in BGR, so we need to flip the bytes - OpenGL is not playing nice...
    for(int i = 0; i < width*height; i++)
    {
            pixels[i*4+0]= pixelraw[i*4+2];
            pixels[i*4+1]= pixelraw[i*4+1];
            pixels[i*4+2]= pixelraw[i*4+0];
            pixels[i*4+3]= pixelraw[i*4+3];
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,pixels);
    glGenerateMipmap(GL_TEXTURE_2D); //Hmmm...
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    // clean up a bit
    delete[] pixels;
    FreeImage_Unload(imagedata);

    printf("- %s loaded\n",current->filename);
    current->textureObject = texture;
    current->usages = 1;
    current->ysize = height;
    current->xsize = width;
    return texture;
}

void textureList::unloadTexture(std::string filename)
{
    char found = 0;
    unsigned int iter=0;
    current = bottom;
    while(current)
    {
        if(!(strcmp(filename.c_str(),current->filename)))
        {
            printf("!found!\n");
            found = 1;
            break;
        }
        current = current->next;
        iter++;
    }
    if(found == 1)
    {
        current->usages--;
        if(current->usages == 0)
        {
            textureNode *tmp = new textureNode;
            tmp = bottom;
            while(iter > 1)
            {
                iter--;
                tmp = tmp->next;
            }
            tmp->next = current->next;
            glDeleteTextures(1,&(current->textureObject));
            delete [] current;
        }
    }
    else
        printf("ERROR: Texture %s not loaded\n - Unable to unload\n",filename.c_str());
    return;
}

void textureList::unloadTexture(unsigned int texID)
{
    char found = 0;
    unsigned int iter=0;
    current = bottom;
    while(current)
    {
        if(texID == current->textureObject)
        {
            found = 1;
            break;
        }
        current = current->next;
        iter++;
    }
    if(found == 1)
    {
        current->usages--;
        if(current->usages == 0)
        {
            textureNode *tmp = new textureNode;
            tmp = bottom;
            while(iter > 1)
            {
                iter--;
                tmp = tmp->next;
            }
            tmp->next = current->next;
            glDeleteTextures(1,&(current->textureObject));
            delete [] current;
        }
    }
    else
        printf("ERROR: Texture %d not loaded\n - Unable to unload\n",texID);
    return;
}

void textureList::selectTexture(std::string filename)
{
    bool found = 0;
    current = bottom;
    while(current)
    {
        if(!(strcmp(filename.c_str(),current->filename)))
        {
            found = 1;
            break;
        }
        current = current->next;
    }
    if(found == 0)
    {
        printf("ERROR: Texture %s not loaded\n - Supposed to be loaded\n",filename.c_str());
        return;
    }
}

void textureList::selectTexture(unsigned int texID)
{
    bool found = 0;
    current = bottom;
    while(current)
    {
        if(texID == current->textureObject)
        {
            found = 1;
            break;
        }
        current = current->next;
    }
    if(found == 0)
    {
        printf("ERROR: Texture %d not loaded\n - Supposed to be loaded\n",texID);
        return;
    }
}

textureList::textureList()
{
    bottom = new textureNode;
    current = bottom;
    top = NULL;
    current->next = NULL;
    strcpy(bottom->filename,"first");
}

textureList::~textureList()
{
    /* stupid c++ stupidly deletes the memory before calling this
       don't call this
    */
//    current = bottom->next;
//    while (current)
//    {
//        printf("unloaded #%d",current->textureObject);
//        unloadTexture(current->textureObject);
//    }
//    unloadTexture(bottom->textureObject);
}
