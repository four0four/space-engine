#include "shaders.h"

using namespace std; //Shut up, shut up, shut up.

unsigned long getFileLength(ifstream& file)
{
    if(!file.good()) return 0;
    file.seekg(0,ios::end);
    unsigned long len = file.tellg();
    file.seekg(ios::beg);

    return len;
}

void shader::printLog(GLuint obj)
{
        int infologLength = 0;
        int maxLength;

        if(glIsShader(obj))
                glGetShaderiv(obj,GL_INFO_LOG_LENGTH,&maxLength);
        else
                glGetProgramiv(obj,GL_INFO_LOG_LENGTH,&maxLength);
		char *infoLog = new char[maxLength];
        if (glIsShader(obj))
        {
                glGetShaderInfoLog(obj, maxLength, &infologLength, infoLog);
                if (infologLength > 0)
                        printf("INFO [glsl shader]:\n%s\n",infoLog);
        }
        else if(glIsProgram(obj))
        {
                glGetProgramInfoLog(obj, maxLength, &infologLength, infoLog);
                if (infologLength > 0)
                        printf("INFO [glsl program]:\n%s\n",infoLog);
        }
        else
        {
                glGetProgramInfoLog(obj, maxLength, &infologLength, infoLog);
                if (infologLength > 0)
                        printf("INFO [glsl other]:\n%s\n",infoLog);
        }

}

int shader::loadFromFile(std::string vertexShader, std::string fragmentShader)
{
    ifstream vertexFile, fragmentFile;
    unsigned int counter;
	bool failure = 0;
    vertexFile.open(vertexShader.c_str(), ifstream::in);
    fragmentFile.open(fragmentShader.c_str(), ifstream::in);

	char *fallbackVertex =
		"#version 120\n"
		"void main() {\n"
		"gl_TexCoord[0] = gl_MultiTexCoord0;\n"
		"gl_Position = ftransform();\n }\n";
	char *fallbackFragment = 
		"#version 120 \n"
		"void main(void) {\n"
		"gl_FragColor = vec4(1.0,1.0,0.0,1.0); \n}\n";

    if(!vertexFile.good()) //bail out either way
	{
		printf("ERROR: Unable to load vertex shader %s!\n", 
			vertexShader.c_str());
		failure = 1;
	}
	if(!fragmentFile.good()) //yep
	{
		printf("ERROR: Unable to load fragment shader %s!\n",
			fragmentShader.c_str());
		failure = 1;
	}

	if(!failure)
	{
		fragmentFileLength = getFileLength(fragmentFile);
		vertexFileLength = getFileLength(vertexFile);

		shader::fragmentSource = new GLchar[fragmentFileLength + 1];
		shader::vertexSource = new GLchar[vertexFileLength + 1];

		if(!shader::fragmentSource || !shader::vertexSource) //new failed
			return -1; //Bad, fixme.

		counter = 0;
		while(vertexFile.good())
		{
			vertexSource[counter] = vertexFile.get();
			counter++;
		}
		counter = 0;
		while(fragmentFile.good())
		{
			fragmentSource[counter] = fragmentFile.get();
			counter++;
		}
		//Null terminate those strings!
		shader::fragmentSource[fragmentFileLength] = 0;
		shader::vertexSource[vertexFileLength] = 0;

		fragmentFile.close();
		vertexFile.close();
	}
	else //breakage, fallback!
	{
		printf(" - Resorting to fallback shaders.\n");
	
		shader::fragmentSource = new GLchar[strlen(fallbackFragment)];
		shader::vertexSource = new GLchar[strlen(fallbackVertex)];

		memcpy(fragmentSource,fallbackFragment,strlen(fallbackFragment)); //Probably should just use fallbackFragment...
		memcpy(vertexSource,fallbackVertex,strlen(fallbackVertex));
		shader::fragmentSource[strlen(fallbackFragment)] = 0;
		shader::vertexSource[strlen(fallbackVertex)] = 0;
	}
    shader::isLoaded = true;

    return 0;
}

int shader::compileShader()
{
    if(!isLoaded) //Files must be loaded!
        return -1;
    shader::vertexObject = glCreateShader(GL_VERTEX_SHADER);
    shader::fragmentObject = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(shader::vertexObject,1,(const GLchar**)&vertexSource,NULL);
    printLog(vertexObject);
    glCompileShader(vertexObject);
    printLog(vertexObject);

    glShaderSource(shader::fragmentObject,1,(const GLchar**)&fragmentSource,NULL);
    printLog(fragmentObject);
    glCompileShader(fragmentObject);
    printLog(fragmentObject);

    shader::isCompiled = true;

    return 0;
}


int shader::linkShader()
{
    if(!isCompiled) //Must be compiled!
        return -1;
    shader::programObject = glCreateProgram();
    glAttachShader(programObject,vertexObject);
    glAttachShader(programObject,fragmentObject);
    glLinkProgram(programObject);
    shader::printLog(programObject);
    shader::isLinked = true;

    return 0;
}

void shader::useShader(bool use)
{
    if(use)
        glUseProgram(programObject);
    else
        glUseProgram(0);
}

void shader::deleteSources()
{
	if(isLoaded)
	{
		delete [] vertexSource;
		delete [] fragmentSource;
	}
    isLoaded = false;
}

shader::shader()
{

}

shader::~shader()
{
    isLinked = false;
    isCompiled = false;

    glDetachShader(shader::programObject,shader::vertexObject);
    glDetachShader(shader::programObject,shader::fragmentObject);
    glDeleteShader(shader::vertexObject);
    glDeleteShader(shader::fragmentObject);
    glDeleteProgram(shader::programObject);

    //if(isLoaded) //WTF?
    //{
    //    delete [] vertexSource;
    //    delete [] fragmentSource;
    //}
    isLoaded = false;
}
