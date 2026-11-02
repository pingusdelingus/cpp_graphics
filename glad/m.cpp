#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <array>
#include "./rstdlib.hpp"
#include "PVMat.hpp"






std::string readShader(const char* filepath)
{
    std::ifstream file (filepath);

    if (!file.is_open()){
        return "";
    }

 std::string res((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());

    return res;
}


PV4 vertices[] = {
   PV4(-1.0, -0.5, 0.5, 1),
   PV4(-0.5, 0.5, 0.5, 1),
   PV4(0.5, 0.5, 0.5, 1),
   PV4(0.5, -0.5, 0.5, 1),
};

std::array<PV4, 4> verts = {
   PV4(-0.5, -0.5, 0.5, 1),
   PV4(-0.5, 0.5, 0.5, 1),
   PV4(0.5, 0.5, 0.5, 1),
   PV4(0.5, -0.5, 0.5, 1),
};


b8 dummy = 1;


void k_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_K && action == GLFW_PRESS) {
        // 'K' was just pressed down
        dummy = !dummy;
    }
}


int main()
{
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
    glfwSetKeyCallback(window, k_callback);

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
    GLuint vertShdr = glad_glCreateShader( GL_VERTEX_SHADER );
    std::string vertContent = readShader("./vertex_shader.glsl");
    const char* rawVert = (vertContent.c_str() );
    GLint vertLen = vertContent.size();
    glad_glShaderSource( vertShdr, 1, (&rawVert) , (&vertLen));
    glCompileShader(vertShdr);
    GLint success;
    char infoLog[512];
    glGetShaderiv(vertShdr, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertShdr, 512, NULL, infoLog);
        std::cerr << "ERROR::VERTEX_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    std::string fragContent = readShader("./fragment_shader.glsl");
    GLint fragLen = fragContent.size();
    const char* rawFrag = (fragContent.c_str() );
    GLuint fragShdr = glad_glCreateShader( GL_FRAGMENT_SHADER );
    glad_glShaderSource( fragShdr, 1, (&rawFrag) , (&fragLen));
    glCompileShader(fragShdr);
    glGetShaderiv(fragShdr, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragShdr, 512, NULL, infoLog);
        std::cerr << "ERROR::FRAGMENT_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glad_glAttachShader(program, vertShdr );
    glad_glAttachShader(program, fragShdr );

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glad_glUseProgram( program );

    GLuint vao; // vertex array object...
    glGenVertexArrays(1, &vao);
    glad_glBindVertexArray(vao);

    GLuint buffer_id;
    glad_glGenBuffers(1, &buffer_id);

    glad_glBindBuffer( GL_ARRAY_BUFFER, buffer_id );
    glad_glBufferData(GL_ARRAY_BUFFER, sizeof(PV4) * verts.size() , std::data(verts), GL_STATIC_DRAW);

    GLuint vPosition = glad_glGetAttribLocation(program, "vPosition");

    glad_glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE , 0,(void*) 0 );
    glad_glEnableVertexAttribArray(vPosition);

    GLuint dummyLoc = glad_glGetUniformLocation(program, "dummy");

    // Main Render Loop
    while (!glfwWindowShouldClose(window)) {
        // Clear screen with a color (Dark Teal)
//        glClearColor(0.1f, 0.4f, 0.4f, 1.0f);
        glad_glClear(GL_COLOR_BUFFER_BIT);
        glad_glUniform1f(dummyLoc, dummy);
        glad_glDrawArrays(GL_TRIANGLE_FAN, 0, verts.size() );
        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glad_glDeleteVertexArrays(1, &vao);
    glfwTerminate();
    return 0;
}// end of main
