#ifndef SHADERS_H
#define SHADERS_H

#include <GL/glew.h>
//#include <string> //Why don't we need this? whatever...
#include <fstream>
#include <memory>

class shader
{
public:
    ~shader();
    shader();

    /*
      return 0 on success, -1 on error
      vertexShader - contains vertex file location
      fragmentShader - contains fragment file location
    */
    int loadFromFile(std::string vertexShader, std::string fragmentShader);

    /*
        Compiles source files to
            shader::programObject
        returns 0 on success, -1 on error
    */
    int compileShader();

    /*
      Links shader::programObject
      returns 0 on success, -1 on error
    */
    int linkShader();
    /*
      prints the opengl log of argument obj
    */
    void printLog(GLuint obj);

    /*
      openGL shader object
      can we move this to private?
    */
    GLuint vertexObject;
    GLuint fragmentObject;

    /*
      openGL program object
      pass to textures/other shit
    */
    GLuint programObject;
private:
    bool isLinked;
    bool isCompiled;
    bool isLoaded;
    GLint vertexFileLength;
    GLint fragmentFileLength;
    GLchar *vertexSource;
    GLchar *fragmentSource;
};


#endif // SHADERS_H
