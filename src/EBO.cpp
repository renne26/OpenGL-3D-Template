#include "Header/EBO.h"

// Function to initialise the EBO
EBO::EBO(GLuint* indices, GLsizeiptr size){
    // Generate the buffers for EBO
    glGenBuffers(1, &ID);
    // Binds the VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    // Loads the data into the buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind(){
    // Binds the VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind(){
    // Binds the VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete(){
    // Deletes the buffers for EBO
    glDeleteBuffers(1, &ID);
}