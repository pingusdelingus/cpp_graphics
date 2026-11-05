#ifndef CALLBACKS_H_
#define CALLBACKS_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

#endif // CALLBACKS_H_
