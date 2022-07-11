#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

/* MSVC
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCALL(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
*/

#define ASSERT(x) if (!(x)) assert(false)
#define GLCALL(x) GLClearError();\
    x;\
    ASSERT(GLCheckErro())

static void GLClearError();
static bool GLCheckErro();
// static bool GLLogCall(const char* function, const char* file, int line);

struct ShaderProgramSource {
    string VertexSource;
    string FragmentSource;
};

static ShaderProgramSource ParseShader(const string& filepath);
static unsigned int CompileShader(unsigned int type, const string& source);
static unsigned int CreateShader(const string& vertexShader, const string& fragmentShader);

// window settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main() 
{
    // glfw: initialize and configure
    // ------------------------------
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


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSwapInterval(1);


    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        glfwTerminate();
        return -1;
    }

    GLCALL(glClearColor(0.2f, 0.4f, 0.2f, 0.0f));   // background color


    // vertex buffers
    // --------------

    // necessary to add, and the order matters!
    unsigned int VertexArrayID;
	GLCALL(glGenVertexArrays(1, &VertexArrayID));
	GLCALL(glBindVertexArray(VertexArrayID));

    float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // buffer id
    unsigned int buffer;
    GLCALL(glGenBuffers(1, &buffer));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW));

    GLCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0)); 
    GLCALL(glEnableVertexAttribArray(0));

    // index buffer object
    unsigned int ibo;
    GLCALL(glGenBuffers(1, &ibo));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));


    // vertex & fragment shaders
    // -------------------------
    ShaderProgramSource source = ParseShader("res/shaders/uniforms.shader");
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    GLCALL(glUseProgram(shader));

    // using uniform
    GLCALL(int location = glGetUniformLocation(shader, "u_Color"));
    ASSERT(location != -1);
    GLCALL(glUniform4f(location, 0.8f, 0.2f, 0.3f, 1.0f));
        // 4f -- 4 floats in vec4

    float r = 0.0f;
    float increment = 0.05f;


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        GLCALL(glClear(GL_COLOR_BUFFER_BIT));

        GLCALL(glUniform4f(location, r, 0.2f, 0.3f, 1.0f));
        GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        if (r > 1.0f)
            increment = -0.05f;
        if (r < 0.0f)
            increment = 0.05f;
        
        r += increment;
        
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    GLCALL(glDeleteBuffers(1, &buffer));
	GLCALL(glDeleteVertexArrays(1, &VertexArrayID));

    GLCALL(glDeleteProgram(shader));

    glfwTerminate();
    return 0;
}

static ShaderProgramSource ParseShader(const string& filepath) 
{
    ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    string line;
    stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) 
    {
        if (line.find("#shader") != string::npos) 
        {
            if (line.find("vertex") != string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != string::npos) 
                type = ShaderType::FRAGMENT;
        } 
        else 
        {
            ss[(int)type] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};
}

static unsigned int CompileShader(unsigned int type, const string& source)
{
    GLCALL(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCALL(glShaderSource(id, 1, &src, nullptr));
    GLCALL(glCompileShader(id));

    // Error handling
    int result;
    GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) 
    {
        int length;
        GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*) alloca(length * sizeof(char));
        GLCALL(glGetShaderInfoLog(id, length, &length, message));
        cout << "Failed to compile shader!\n" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << endl;
        cout << message << endl;
        GLCALL(glDeleteShader(id));
        return 0;
    }
    
    return id;
}


static unsigned int CreateShader(const string& vertexShader, const string& fragmentShader) 
{
    GLCALL(unsigned int program = glCreateProgram());
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCALL(glAttachShader(program, vs));
    GLCALL(glAttachShader(program, fs));
    GLCALL(glLinkProgram(program));
    // glValidateProgram(program);

    int result;
    GLCALL(glGetProgramiv(program, GL_LINK_STATUS, &result));
    if (!result) 
    {
        int length;
        GLCALL(glGetShaderiv(program, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*) alloca(length * sizeof(char));
        GLCALL(glGetProgramInfoLog(program, length, &length, message));
        cout << "Failed to link shaders!\n" << message << endl;
    }

    GLCALL(glDeleteShader(vs));
    GLCALL(glDeleteShader(fs));

    return program;
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
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    GLCALL(glViewport(0, 0, width, height));
}

// opengl error handling
// ---------------------
static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static bool GLCheckErro() 
{
    while (GLenum error = glGetError())
    {
        cout << "[OpenGL Error] (" << error << "): ";
        switch(error) 
        {
            case GL_INVALID_ENUM :
                std::cout << "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE :
                std::cout << "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION :
                std::cout << "GL_INVALID_OPERATION";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION :
                std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
            case GL_OUT_OF_MEMORY :
                std::cout << "GL_OUT_OF_MEMORY";
                break;
            default :
                std::cout << "Unrecognized error" << error;
        }
        cout << endl;
        return false;
    }
    return true;
}

/*
static bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        cout << "[OpenGL Error] (" << error << "): " << function <<
            " " << file << ": " << line << endl;
        return false;
    }
    return true;
}
*/