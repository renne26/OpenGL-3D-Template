#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Header/ShaderClass.h"
#include "Header/VAO.h"
#include "Header/VBO.h"
#include "Header/EBO.h"
#include "Header/Texture.h"

// Vertices of the object
GLfloat vertices[] =
{
    //    COORDINATES   //     COLOURS    //
    -0.5f, 0.0f,  0.5f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,   0.0f, 1.0f, 0.0f,  5.0f, 0.0f,
     0.5f, 0.0f, -0.5f,   0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
     0.5f, 0.0f,  0.5f,   1.0f, 1.0f, 1.0f,  5.0f, 0.0f,
     0.0f, 0.8f,  0.0f,   1.0f, 1.0f, 1.0f,  2.5f, 5.0f
};

// How to draw the object using indices
GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};

const unsigned int width = 800;
const unsigned int height = 800;

// Main function
int main(){
    // Initialises glfw
    glfwInit();

    // Tells OpenGL what is the version of OpenGL is used
    // Sets the current OpenGL profile to be the core version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Sets the window to be 800 by 800 pixels, can be substituted by a variable if wanted
    GLFWwindow* window = glfwCreateWindow(width, height, "Renne's Template Engine", NULL, NULL);
    // Checks if the window is not created
    // If true, it will terminate the program and return -1 as code
    if(window == NULL){
        std::cout << "failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Sets the current 'context' to the created window
    glfwMakeContextCurrent(window);

    // Loads in glad
    gladLoadGL();

    // Sets the viewport to be size of the created window starting at origin to size of window
    glViewport(0, 0, width, height);

    // Tells shaderProgram where the shaders files are located
    Shader shaderProgram("Resource/Shaders/default.vert", "Resource/Shaders/default.frag");

    // Creates and binds the VAO
    VAO VAO1;
    VAO1.Bind();

    // Creates the VBO and EBO
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    // Links the VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    // Unbinds VAO, VBO and EBO after finishing
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Gets the ID of the uniform called scale
    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    // Finds and sets the image with the correct data
    Texture penguin("Resource/Textures/Penguin.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    // Set it to the 0th texture unit
    penguin.texUnit(shaderProgram, "tex0", 0);

    float rotation = 0.0f;
    double prevTime = glfwGetTime();
    
    glEnable(GL_DEPTH_TEST);

    // While the window is not closed, keep it open
    while(!glfwWindowShouldClose(window)){
        // Sets the color for the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clears the color buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activates the shader program
        shaderProgram.Activate();

        double crnttime = glfwGetTime();
        if(crnttime - prevTime >= 1 / 60){
            rotation += 0.5f;
            prevTime = crnttime;
        }

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);

        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        proj = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);

        int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

        // Sets scale to be 0.5f
        glUniform1f(uniID, 0.5f);
        // Binds the image
        penguin.Bind();
        
        // Binds the vertex array, more useful if have more items
        VAO1.Bind();
        // Draws the arrays using triangles
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

        // Swaps the buffers so that the background is displayed
        glfwSwapBuffers(window);

        // Handles all the events of the window
        glfwPollEvents();
    }

    // After window is closed, i.e termination

    // Deletes all the vertes buffers and arrays and also the shaderProgram
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    penguin.Delete();
    shaderProgram.Delete();

    // Destroy all instance of the context then return 0 for successful termination
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}