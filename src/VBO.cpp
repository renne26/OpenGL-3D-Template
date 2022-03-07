#include "Header/VBO.h"

// Function to initialise the VBO
VBO::VBO(GLfloat* vertices, GLsizeiptr size){
    // Generates the buffers for VBO
    glGenBuffers(1, &ID);
    // Binds the VBO
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    // Loads the data into the buffer
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind(){
    // Binds the VBO
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind(){
    // Binds the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete(){
    // Deletes the buffers for VBO
    glDeleteBuffers(1, &ID);
}