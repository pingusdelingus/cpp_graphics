#include "InitShaders.hpp"
#include <glad/glad.h>
#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <array>
#include "./rstdlib.hpp"
#include "PVMat.hpp"
#include "InitShaders.hpp"
#include <GLFW/glfw3.h>
std::string readShader(const char* filepath)
{
    std::ifstream file (filepath);

    if (!file.is_open()){
        std::cerr << "ERROR::SHADER::FILE_NOT_FOUND: " << filepath << std::endl;
        return "";
    }

 std::string res((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());

    return res;
}

void init_shader(GLuint prog, GLuint vert, GLuint frag, const char* vertPath, const char* fragPath )
{

std::string vertContent = readShader(vertPath);
const char* rawVert = (vertContent.c_str() );
GLint vertLen = vertContent.size();
glad_glShaderSource( vert, 1, (&rawVert) , (&vertLen));
glCompileShader(vert);
GLint success;
char infoLog[512];
glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
if (!success) {
    glGetShaderInfoLog(vert, 512, NULL, infoLog);
    std::cerr << "ERROR::VERTEX_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
}

std::string fragContent = readShader(fragPath);
GLint fragLen = fragContent.size();
const char* rawFrag = (fragContent.c_str() );
glad_glShaderSource( frag, 1, (&rawFrag) , (&fragLen));
glCompileShader(frag);
glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
if (!success) {
    glGetShaderInfoLog(frag, 512, NULL, infoLog);
    std::cerr << "ERROR::FRAGMENT_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
}

glad_glAttachShader(prog, vert );
glad_glAttachShader(prog, frag );

glLinkProgram(prog);

glGetProgramiv(prog, GL_LINK_STATUS, &success);
if (!success) {
    glGetProgramInfoLog(prog, 512, NULL, infoLog);
    std::cerr << "ERROR::PROG::LINKING_FAILED\n" << infoLog << std::endl;
}

}// end of init_shaders
