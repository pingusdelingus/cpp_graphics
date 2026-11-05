#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <array>
#include <cassert>
#include "./rstdlib.hpp"
#include "PVMat.hpp"
#include "InitShaders.hpp"
#include "Callbacks.hpp"
#include "Tux.hpp" // contains tux model


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


    std::array<PV4, 3>tri_colors = {
        PV4(1.0, 0.0 ,0.0, 1.0), // Red
        PV4(0.0, 1.0 ,0.0, 1.0), // Green
        PV4(0.0, 0.0 ,1.0, 1.0), // Blue
    };


std::array<PV4, 3> tri_verts = {
        PV4{ -0.75, -0.75,  0.5,1},
        PV4{  0.75, -0.75,  0.5 ,1},
        PV4{  0.0,   0.25, -0.5, 1 }
};



constexpr u32 HEIGHT = 9 * 66.6f;
constexpr u32 WIDTH = 16 * 66.6f;
constexpr u32 STRIDE = 0;

b8 dummy = 1;
f32 theta = 0.0f;
b8 using_perspective = false;


b8 isClicked = false;
f32 clickX = 0.0f;
f32 clickY = 0.0f;

constexpr Mat canvas2clip =
    Mat::translation(PV4{-1.0, +1.0, 0.0, 0.0}) *
    Mat::scale(PV4 {2.0 / WIDTH, -2.0 / HEIGHT, 1, 1 });
constexpr Mat clip2canvas =
    Mat::scale(PV4{WIDTH / 2.0, -(HEIGHT / 2.0), 1, 1}) *
    Mat::translation(PV4{+1, -1, 0, 0});

Mat proj2clip{};
Mat clip2proj{};

Mat view2proj{};
Mat proj2view{};

Mat view2world{};
Mat world2view{};

Mat world2rotated{};
Mat rotated2world{};

Mat rotated2object{};
Mat object2rotated{};

Mat object2model{};
Mat model2object{};

Mat model2clip{};
Mat clip2model{};


PV4 translation_vec{0.0, 0.0, 0.0, 0.0};

constexpr Mat id{true};


std::vector<GLuint> flat_indices{};

PV4 pointmodel2clip(const PV4& point)
{
    return proj2clip * (view2proj * (world2view * (rotated2world * (object2rotated * (model2object * point)))));
}

PV4 pointclip2model(const PV4& point)
{
    return object2model * (rotated2object * (world2rotated * (view2world * (proj2view * clip2proj * point))));
}

void updateM2C()
{
    model2clip = proj2clip * (view2proj * (world2view * (rotated2world * (object2rotated * (model2object )))));
    clip2model = object2model * (rotated2object * (world2rotated * (view2world * (proj2view * clip2proj))));
    assert(model2clip * clip2model == id && "Model2Clip * Clip2Model != identity matrix")
}

void orthographic_transform()
{




}



int main()
{

    assert((canvas2clip * clip2canvas )== id);
    flat_indices.reserve(penger_fs.size() * 3);
    for (const PV4& face : penger_fs) {
        flat_indices.push_back(static_cast<GLuint>(face.x));
        flat_indices.push_back(static_cast<GLuint>(face.y));
        flat_indices.push_back(static_cast<GLuint>(face.z));
    }

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
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "da window", NULL, NULL);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

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
    GLuint fragShdr = glad_glCreateShader( GL_FRAGMENT_SHADER );

    init_shader(program, vertShdr, fragShdr, "./vertex_shader.glsl", "./fragment_shader.glsl");

    glad_glUseProgram( program );

    GLuint vao; // vertex array object...
    glGenVertexArrays(1, &vao);
    glad_glBindVertexArray(vao);

//    GLuint tri_buffer_color;
//    glad_glGenBuffers(1, &tri_buffer_color);
//    glad_glBindBuffer(GL_ARRAY_BUFFER, tri_buffer_color);
//    glad_glBufferData(GL_ARRAY_BUFFER, sizeof(PV4) * tri_colors.size(), std::data(tri_colors), GL_STATIC_DRAW);

    // setup the vertex buffer
    GLuint penger_verts_buff;
    glad_glGenBuffers(1, &penger_verts_buff);
    glad_glBindBuffer( GL_ARRAY_BUFFER, penger_verts_buff );
    glad_glBufferData(GL_ARRAY_BUFFER, sizeof(PV4) * penger_verts.size() , std::data(penger_verts), GL_STATIC_DRAW);

    GLuint vPosition = glad_glGetAttribLocation(program, "vPosition");
    glad_glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE , STRIDE,(void*) 0 );
    glad_glEnableVertexAttribArray(vPosition);


    // setup faces buffer
    GLuint penger_fs_buff;
    glad_glGenBuffers(1, &penger_fs_buff);
    glad_glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, penger_fs_buff );

glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * flat_indices.size(), flat_indices.data(), GL_STATIC_DRAW);
//    glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(PV4) * penger_fs.size() , std::data(penger_fs),GL_STATIC_DRAW);

    glad_glBindVertexArray(0);

    // uniforms
    GLuint translationLoc = glad_glGetAttribLocation(program, "translation");
    GLuint dummyLoc = glad_glGetUniformLocation(program, "dummy");
    GLuint thetaLoc = glad_glGetUniformLocation(program, "theta");

    // Main Render Loop
    while (!glfwWindowShouldClose(window)) {
        // Clear screen with a color (Dark Teal)
        //        glClearColor(0.1f, 0.4f, 0.4f, 1.0f);
        //


        glad_glClear(GL_COLOR_BUFFER_BIT);
        glad_glUniform1f(dummyLoc, dummy);
        glad_glUniform1f(thetaLoc, theta);
        glad_glUniform4f(translationLoc, translation_vec.x, translation_vec.y, 0.0f, 0.0f);
        glad_glBindVertexArray(vao);

        glad_glDrawElements(GL_TRIANGLES, flat_indices.size(), GL_UNSIGNED_INT, 0);
        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();

        if (dummy)
            theta += 0.01;
        else
            theta -= 0.01;
    }


    glad_glDeleteVertexArrays(1, &vao);
    glfwTerminate();
    return 0;
}// end of main
