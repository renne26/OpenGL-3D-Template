#include "Header/Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType){
    type = texType;

    int widthImg, heightImg, numColCh;
    // Flips the image because of how stb renders images
    stbi_set_flip_vertically_on_load(true);
    // Loads the image data into variable
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    // Generate the textures
    glGenTextures(1, &ID);
    // Sets the active slot in the tex unit
    glActiveTexture(slot);
    // Binds the texture
    glBindTexture(texType, ID);

    // Sets the texture to be nearest interpolation
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Sets the texture to repeat
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Sets the texture to the object
    glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
    // Generates a mipmap
    glGenerateMipmap(texType);

    // Deletes the unneeded textures and unbinds it
    stbi_image_free(bytes);
    glBindTexture(texType, 0);
}

// Sets the texture to be rendered into the shaders
void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit){
    GLuint tex0Uni = glGetUniformLocation(shader.ID, uniform);
    shader.Activate();
    glUniform1i(tex0Uni, unit);
}

// Binds the textures
void Texture::Bind(){
    glBindTexture(type, ID);
}

// Unbinds the textures
void Texture::Unbind(){
    glBindTexture(type, 0);
}

// Delete the textures
void Texture::Delete(){
    glDeleteTextures(1, &ID);
}