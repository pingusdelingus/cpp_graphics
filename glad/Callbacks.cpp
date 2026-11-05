#include "Callbacks.hpp"
#include "./rstdlib.hpp"
#include <iostream>
#include "PVMat.hpp"

extern b8 isClicked;
extern f32 clickX;
extern f32 clickY;
extern b8 dummy;
extern PV4 translation_vec;
extern b8 using_perspecive;


const f32 TRANSLATION_SIZE = 0.1f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    std::cout << "Valid key clicked : " << key << "\n";


    switch(key){
        case GLFW_KEY_K:
            if (action == GLFW_PRESS)
                dummy = !dummy;
            break;

        case GLFW_KEY_W:
            translation_vec.y += TRANSLATION_SIZE;
            break;

        case GLFW_KEY_S:
            translation_vec.y -= TRANSLATION_SIZE;
            break;

        case GLFW_KEY_A:
            translation_vec.x -= TRANSLATION_SIZE;
            break;
        case GLFW_KEY_D:
            translation_vec.x += TRANSLATION_SIZE;
            break;
        case GLFW_KEY_P:
            std::cout << "Turning on 'Perspective' mode \n";
            using_perspective = true;

    }

}// end of key_callback



void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // Left mouse button was clicked
        std::cout << "Left click detected!" << std::endl;

        // Optional: Get the exact coordinates of the click
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        clickX = static_cast<f32>(xpos);
        clickY = static_cast<f32>(ypos);
        std::cout << "Clicked at canvas(: " << clickX <<", " << clickY <<" )\n";
        isClicked = true;

    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        // Right mouse button was clicked
        std::cout << "Right click detected!" << std::endl;

    }
}
