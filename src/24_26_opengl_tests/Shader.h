#ifndef SHADER_H__
#define SHADER_H__

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "glm/glm.hpp"


using namespace std;

struct ShaderProgramSource {
    string VertexSource;
    string FragmentSource;
};

class Shader
{
private:
    string m_FilePath;
    unsigned int m_RendererID;
    mutable unordered_map<string, int> m_UniformLocationCache;
public:
    Shader(const string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // Set uniforms
    void SetUniform1i(const string& name, int value);
    void SetUniform1f(const string& name, float value);
    void SetUniform2f(const string& name, const glm::vec2& value);
    void SetUniform3f(const string& name, const glm::vec3& value);
    void SetUniform4f(const string& name, const glm::vec4& value);
    void SetUniformMat3f(const string& name, const glm::mat3& matrix);
    void SetUniformMat4f(const string& name, const glm::mat4& matrix);
private:
    ShaderProgramSource ParseShader(const string& filepath);
    unsigned int CompileShader(unsigned int type, const string& source);
    unsigned int CreateShader(const string& vertexShader, const string& fragmentShader);

    int GetUniformLocation(const string& name) const;
};

#endif