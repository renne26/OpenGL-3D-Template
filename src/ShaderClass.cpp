#include "Header/ShaderClass.h"

// Function to get the contents of the file
std::string get_file_contents(const char* filename){
    std::ifstream in(filename, std::ios::binary);
    if(in){
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}

// Function to create the shader program
Shader::Shader(const char* vertexFile, const char* fragmentFile){
    // Reads the source code of the vertex shader and fragment shader files
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    // Converts them to a c string for interpretation
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Creates the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Links the vertex shader source code
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    // Compiles the vertex shader source code
    glCompileShader(vertexShader);
    compileErrors(vertexShader, "VERTEX");

    // Creates the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Links the fragment shader source code
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    // Compiles the fragment shader source code
    glCompileShader(fragmentShader);
    compileErrors(fragmentShader, "FRAGMENT");


    // Creates the shader program
    ID = glCreateProgram();

    // Attach both the fragment and vertex shader to the shader program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    compileErrors(fragmentShader, "PROGRAM");

    // Deletes the vertex and fragemnt shader as it is already linked to the shader program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// Function to activate the shader program
void Shader::Activate(){
    // Uses the shaderProgram
    glUseProgram(ID);
}

// Function to delete the shader program
void Shader::Delete(){
    glDeleteProgram(ID);
}

// Function for error checking
void Shader::compileErrors(unsigned int shader, const char* type){
    GLint hasCompiled;
    char infoLog[1024];

    if(type != "PROGRAM "){
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if(hasCompiled == GL_FALSE){
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << std::endl;
        }
    }
    else{
        glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if(hasCompiled == GL_FALSE){
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << std::endl;
        }
    }
}