// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// Math

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>


#include <iostream>
#include <string>
#include "shader/Shader.h"

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
    fprintf( stderr,
            "GL CALLBACK: %s source = 0x%x, type = 0x%x, severity = 0x%x, message = %s\n",
             ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
             source, type, severity, message );
}

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 1600, HEIGHT = 1200;


float b_scale = 1e-3;
float scale = 1e-3;
int zoom = 0;
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    zoom += int(yoffset);
    scale = b_scale * powf(1.1f, (float)zoom);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
//    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
//        popup_menu();
}

auto mouse_pos = glm::vec4();
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    mouse_pos.x = xpos;
    mouse_pos.y = ypos;
}


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

    Program p("res/shaders/mandelbrot.glsl");
//    Program p("res/shaders/basic.glsl");
    p.Compile();
    //
    // IMGUI
    //
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glsl_version = "#version 330 core";
    ImGui_ImplOpenGL3_Init(glsl_version);
    //
    //
    ///

//    glGetString(GL_VERSION)
    int maj, min;
    glGetIntegerv(GL_MAJOR_VERSION, &maj);
    glGetIntegerv(GL_MINOR_VERSION, &min);

    std::cout << "Loaded version: " <<  maj << "." << min << std::endl;

    glEnable              ( GL_DEBUG_OUTPUT );
    glDebugMessageControl(
            GL_DEBUG_SOURCE_SHADER_COMPILER,
            GL_DEBUG_TYPE_OTHER,
            GL_DEBUG_SEVERITY_NOTIFICATION,
            0, nullptr,
            GL_FALSE);
    glDebugMessageCallback( MessageCallback, nullptr);

    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);


//    return 0;

    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);




//    float vertices[] = {
//            -0.5f, -0.5f,
//            +0.5f, -0.5f,
//             0.0f, +0.5f,
//    };
    float vertices[] = {
            -1., -1.,
            -1., +1.,
            +1., +1.,

            -1., -1.,
            +1., -1.,
            +1., +1.,
    };

    uint32_t VAO;
//    glGenBuffers(1, &VAO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAO);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    uint32_t index_buf;
    glGenBuffers(1, &index_buf);
    glBindBuffer(GL_ARRAY_BUFFER, index_buf);
    glBufferData(GL_ARRAY_BUFFER, 12 * 2 * sizeof(float), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void *)0);


    auto proj = glm::ortho(-800.f, +800.f, -600.f, +600.f);
    auto proj_inv = glm::inverse(proj);


//    auto model = glm::scale(glm::vec3(1.f, 1.f, 1.f) * 2.f);


//    auto MVP = model * proj;
//    std::cout<<glm::to_string(MVP)<<std::endl;

    p.Bind();
//    p.setUniform4x4("MVP", glm::mat4(1.f));
//    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    // Game loop
    char title[500];
    double prev = glfwGetTime(), now, diff;
    bool show_another_window = false;
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        p.setUniform1f("scale", scale);


        // Render
        // Clear the colorbuffer
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the screen buffers
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        glfwSwapBuffers(window);

        auto true_mouse_pos = proj * mouse_pos;


        now = glfwGetTime();
        diff = now - prev;
        if (diff > .001f) {
            snprintf(title, 500, "OpenGL Test FPS: %6.2f x: %6.2f y: %6.2f", 1 / diff, true_mouse_pos.x, true_mouse_pos.y);
            glfwSetWindowTitle(window, title);
        }
        prev = now;
    }

    ImGui::DestroyContext();

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