// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>


#include <iostream>
#include <string>

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
             ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
             type, severity, message );
}

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

void bindSimpleProgram() {
    std::string vertex_shader{
        "#version 330 core\n"
        "layout(location = 0) in vec4 a_pos;\n"
        "void main() {\n"
        "   gl_Position = a_pos;\n"
        "}"
    };
    std::string fragment_shader{
        "#version 330 core\n"
        "void main() {\n"
        "   gl_FragColor = vec4(0.2, 0.5, 0.7, 1.0);\n"
        "}"
    };
    int status;
    auto vertex = glCreateShader(GL_VERTEX_SHADER);
    auto p = vertex_shader.c_str();
    glShaderSource(vertex, 1, &p, nullptr);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        char buff [2048];
        int buffLen;
        glGetShaderInfoLog(vertex, 2048, &buffLen, buff);
        std::cout << "Errors during compilation: \n" << buff << std::endl;
    }

    auto fragment = glCreateShader(GL_FRAGMENT_SHADER);
    p = fragment_shader.c_str();
    glShaderSource(fragment, 1, &p, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        char buff [2048];
        int buffLen;
        glGetShaderInfoLog(fragment, 2048, &buffLen, buff);
        std::cout << "Errors during compilation: \n" << buff << std::endl;
    }
    auto program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    glUseProgram(program);

//    glDeleteShader(vertex);
//    glDeleteShader(fragment);
}

//void debug(GLenum source,
//           GLenum type,
//           GLuint id,
//           GLenum severity,
//           GLsizei length,
//           const GLchar* message,
//           const void* userParam) {
//    std::cerr <<  message << std::endl;
//
//}

// The MAIN function, from here we start the application and run the game loop
int main()
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Set all the required options for GLFW
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //CORE_PROFILE
//    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
//    glfwSwapInterval(0);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }


//    glGetString(GL_VERSION)
    int maj, min;
    glGetIntegerv(GL_MAJOR_VERSION, &maj);
    glGetIntegerv(GL_MINOR_VERSION, &min);

    std::cout << "Loaded version: " <<  maj << "." << min << std::endl;
    bindSimpleProgram();

    glEnable              ( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( MessageCallback, nullptr);


//    return 0;

    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);



    
    float vertices[] = {
            -0.5f, -0.5f,
            +0.5f, -0.5f,
             0.0f, +0.5f,
    };

    uint32_t VAO;
//    glGenBuffers(1, &VAO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAO);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    uint32_t index_buf;
    glGenBuffers(1, &index_buf);
    glBindBuffer(GL_ARRAY_BUFFER, index_buf);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void *)0);



    // Game loop
    char title[500];
    double prev = glfwGetTime(), now, diff;
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();


        // Render
        // Clear the colorbuffer
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the screen buffers
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);


        now = glfwGetTime();
        diff = now - prev;
        if (diff > .001f) {
            snprintf(title, 500, "OpenGL Test FPS: %6.2f", 1 / diff);
            glfwSetWindowTitle(window, title);
        }
        prev = now;
    }

    // Terminates GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
//    std::cout << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}