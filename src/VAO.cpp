#include "Header/VAO.h"

// Function to initialise the VAO
VAO::VAO(){
    // Generate the arrays for the VAO
    glGenVertexArrays(1, &ID);
}

// Function to link the VBO to VAO
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset){
    // Binds the VBO
    VBO.Bind();

    // Communicates the vertex shader from the outside
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    // Sets the location which is 0
    glEnableVertexAttribArray(layout);

    // Unbinds the VBO
    VBO.Unbind();
}

void VAO::Bind(){
    // Binds the VAO
    glBindVertexArray(ID);
}

void VAO::Unbind(){
    // Unbinds the VAO
    glBindVertexArray(0);
}

void VAO::Delete(){
    // Deletes the VAO
    glDeleteVertexArrays(1, &ID);
}