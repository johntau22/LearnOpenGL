#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SRC_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "\n"
    "out vec3 customColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "    customColor = aColor;\n"
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "\n"
    "in vec3 customColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(customColor, 1.0f);\n"
    "}\0";

const char* fragmentShaderSourceYellow = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\0";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ----------------
    // shader program
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShaderYellow;
    fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, NULL);
    glCompileShader(fragmentShaderYellow);

    glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderYellow, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT_YELLOW::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgramYellow;
    shaderProgramYellow = glCreateProgram();
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);

    //glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShaderYellow);

    // data
    float vertices[] =
    {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    float vert_ex2_1[] =
    {
        -1.0f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.0f, -0.5f, 0.0f
    };

    float vert_ex2_2[] =
    {
        0.0f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        1.0f, -0.5f, 0.0f
    };

    float vertices2[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    unsigned int indices[] =
    {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int VBO_EX2_1, VBO_EX2_2, VAO_EX2_1, VAO_EX2_2;
    glGenBuffers(1, &VBO_EX2_1);
    glGenBuffers(1, &VBO_EX2_2);
    glGenVertexArrays(1, &VAO_EX2_1);
    glGenVertexArrays(1, &VAO_EX2_2);

    glBindVertexArray(VAO_EX2_1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_EX2_1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert_ex2_1), vert_ex2_1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindVertexArray(VAO_EX2_2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_EX2_2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert_ex2_2), vert_ex2_2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // draw as wireframes
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // ----------------

    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw
        glUseProgram(shaderProgram);

        // update uniform
        //float timeValue = glfwGetTime();
        //float redValue = sin(timeValue) / 2.0f + 0.5f;
        //int vertexColorLocation = glGetUniformLocation(shaderProgram, "customColor");
        //glUniform4f(vertexColorLocation, redValue, 0.0f, 0.0f, 1.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //glBindVertexArray(VAO_EX2_1);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        //glBindVertexArray(0);

        //glUseProgram(shaderProgramYellow);
        //glBindVertexArray(VAO_EX2_2);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        //glBindVertexArray(0);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // finalize
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    //glDeleteBuffers(1, &VBO);
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &EBO);

    glDeleteBuffers(1, &VBO_EX2_1);
    glDeleteBuffers(1, &VBO_EX2_2);
    glDeleteVertexArrays(1, &VAO_EX2_1);
    glDeleteVertexArrays(1, &VAO_EX2_2);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}