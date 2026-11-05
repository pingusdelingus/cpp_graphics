#ifndef INITSHADERS_H_
#define INITSHADERS_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <array>
#include "./rstdlib.hpp"
#include "PVMat.hpp"
void init_shader(GLuint prog, GLuint vert, GLuint frag, const char* vertPath, const char* fragPath );

std::string readShader(const char* filepath);

#endif // INITSHADERS_H_
