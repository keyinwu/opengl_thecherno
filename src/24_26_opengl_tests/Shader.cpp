#include "Shader.h"
#include "Renderer.h"

Shader::Shader(const string& filepath)
    : m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
    GLCALL(glDeleteProgram(m_RendererID));
}

ShaderProgramSource Shader::ParseShader(const string& filepath) 
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

unsigned int Shader::CompileShader(unsigned int type, const string& source)
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

unsigned int Shader::CreateShader(const string& vertexShader, const string& fragmentShader) 
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

void Shader::Bind() const
{
    GLCALL(glUseProgram(m_RendererID));
}
void Shader::Unbind() const
{
    GLCALL(glUseProgram(0));
}

void Shader::SetUniform1i(const string& name, int value)
{
    GLCALL(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const string& name, float value)
{
    GLCALL(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform2f(const string& name, const glm::vec2& value)
{
    GLCALL(glUniform2f(GetUniformLocation(name), value.x, value.y));
}

void Shader::SetUniform3f(const string& name, const glm::vec3& value)
{
    GLCALL(glUniform3f(GetUniformLocation(name), value.x, value.y, value.z));
}

void Shader::SetUniform4f(const string& name, const glm::vec4& value)
{
    GLCALL(glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w));
}

void Shader::SetUniformMat3f(const string& name, const glm::mat3& matrix)
{   
    GLCALL(glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SetUniformMat4f(const string& name, const glm::mat4& matrix)
{
    GLCALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const string& name) const
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    
    GLCALL(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        cout << "Warning: uniform '" << name << "' doesn't exist!" << endl;
    else
        m_UniformLocationCache[name] = location;
    return location;  
}