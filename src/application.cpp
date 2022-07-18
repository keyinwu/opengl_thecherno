#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"

using namespace std;

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main() 
{
    if( !glfwInit())
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSwapInterval(1);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        glfwTerminate();
        return -1;
    }

        GLCALL(glEnable(GL_BLEND));
        GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        Renderer renderer;
        renderer.BgColor(0.2f, 0.4f, 0.2f, 1.0f);

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        test::Test* currentTest = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        testMenu->RegisterTest<test::TestTexture2D>("2D Texture");

        while (!glfwWindowShouldClose(window))
        {
            processInput(window);
            renderer.BgColor(0.0f, 0.0f, 0.0f, 1.0f);
            renderer.Clear();

            ImGui_ImplGlfwGL3_NewFrame();
            if (currentTest)
            {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                ImGui::Begin("Test");
                if (currentTest != testMenu && ImGui::Button("<-"))
                {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest->OnImGuiRender();
                ImGui::End();
            }
            
            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        
            
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        delete currentTest;
        if (currentTest != testMenu)
            delete testMenu;

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}


// process whether relevant keys are pressed/released
// --------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// executes whenever the window size changed
// -----------------------------------------
// void framebuffer_size_callback(GLFWwindow* window, int width, int height)
// {
//     GLCALL(glViewport(0, 0, width, height));
// }