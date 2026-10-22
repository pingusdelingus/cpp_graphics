#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


std::string readShader(const char* filepath)
{
    std::string res;

    res += std::cin >> filepath;



    return res;
}



int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set OpenGL options for macOS Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS

    // Create a window
    GLFWwindow* window = glfwCreateWindow(800, 600, "da window", NULL, NULL);

    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    GLuint program = glad_glCreateProgram();
    auto vertShdr = glad_glCreateShader( GL_VERTEX_SHADER );
    glad_glShaderSource( vertShdr, vertElem.text );


    auto fragShdr = glad_glCreateShader( GL_FRAGMENT_SHADER );
    glad_glAttachShader(program, vertShdr );
    glad_glAttachShader(program, fragShdr );



    // Main Render Loop
    while (!glfwWindowShouldClose(window)) {
        // Clear screen with a color (Dark Teal)
        glClearColor(0.1f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
