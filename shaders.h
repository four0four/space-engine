#ifndef SHADERS_H
#define SHADERS_H

#include <GL/glew.h>
//#include <string> //Why don't we need this? whatever...
#include <fstream>
#include <memory> //Do not remember including this. Needed?
#include <string.h>

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
      enable or disable the shader
    */
    void useShader(bool use);

    /*
      delete the shader source code buffers
      saves some memory
    */
    void deleteSources();

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
    GLuint vertexObject;
    GLuint fragmentObject;
};


#endif // SHADERS_H
