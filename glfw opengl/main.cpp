#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
//#include "vertex.glsl"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}


char  *vertexShaderSource = "#version 330 core layout(location=0) in vec3 aPos;void main(){gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0);}";
char  *fragmentShaderSource = "#version 330 core out vec4 FragColor; void main() { FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); }";



void render(){
    //background
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    float vertices[] = {
        -0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.0f,0.5f,0.0f
    };
    

    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    
    unsigned int VBO;
    glGenBuffers(1, &VBO); //get buffer id
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //bind VBO buffer to target
    
    
    //start drawing
    //we initialized the vertex data in a buffer using a vertex buffer object,
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //set vertex attribute pointers
    //vertex array object ( VAO )
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    
    //set up vert shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    //check if compile successfully
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    //set up frag shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    //check if frag is compiled successfully
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glad_glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    //link shaders to shaderprogram
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //check if linking is successful
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        cout << "ERROR::SHADER::LINKING::COMPILATION_FAILED\n" << infoLog << endl;
    }
    
    

    
    glUseProgram(shaderProgram);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    

    
    
    
}

int main(){
    glfwInit();
    //minimum glfw version: 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //only use the core profile setting of glfw
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "hello OPENGL", nullptr, nullptr);
    if(window == nullptr){
        cout << "failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout << "failed to initilize GLAD" << endl;
        return -1;
    }
    
    glViewport(0,0,800,600);
    //add call back
    
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        //render
        render();
        //
        
        glfwSwapBuffers(window);//output all computed results to screen
        glfwPollEvents();//hold all received event and execute corresponding functions
    }
    
    glfwTerminate();
    
    return 0;
}
