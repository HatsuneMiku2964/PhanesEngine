#include "pnpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Phanes
{
    OpenGLShader::OpenGLShader(const std::string& path)
    {
        ShaderSrc src = ParseShader(path);

        shader_id = glCreateProgram();
        uint32_t program = shader_id;

        uint32_t vs = glCreateShader(GL_VERTEX_SHADER);
        uint32_t fs = glCreateShader(GL_FRAGMENT_SHADER);

        const char* vs_src = src.vtxsrc.c_str();
        glShaderSource(vs, 1, &vs_src, nullptr);
        glCompileShader(vs);

        const char* fs_src = src.frgmsrc.c_str();
        glShaderSource(fs, 1, &fs_src, nullptr);
        glCompileShader(fs);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        glDetachShader(program, vs);
        glDetachShader(program, fs);
    }

    OpenGLShader::~OpenGLShader() { glDeleteProgram(shader_id); }

    void OpenGLShader::Bind() const { glUseProgram(shader_id); }
    void OpenGLShader::Unbind() const { glUseProgram(0); }

    int OpenGLShader::GetUniformLoc(const std::string& name) const
    {
        if (uniform_loc_cache.contains(name)) return uniform_loc_cache.at(name);

        int result = glGetUniformLocation(shader_id, name.c_str());
        if (result == -1) PN_CORE_LOG_ERROR("invalid uniform location!!");
        uniform_loc_cache[name] = result;
        return result;
    }

    template <typename T>
    void OpenGLShader::SetUniform(const std::string& name, const T& value)
    {
        int location = GetUniformLoc(name);
        if (location == -1) return;

        if constexpr (std::is_same_v<T, int>)               glUniform1i(location, value);
        else if constexpr (std::is_same_v<T, float>)        glUniform1f(location, value);
        else if constexpr (std::is_same_v<T, glm::vec2>)    glUniform2f(location, value.x, value.y);
        else if constexpr (std::is_same_v<T, glm::vec3>)    glUniform3f(location, value.x, value.y, value.z);
        else if constexpr (std::is_same_v<T, glm::vec4>)    glUniform4f(location, value.x, value.y, value.z, value.w);
        else if constexpr (std::is_same_v<T, glm::mat3>)    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
        else if constexpr (std::is_same_v<T, glm::mat4>)    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
        else static_assert(!sizeof(T*), "Unsupported Uniform Type!");
    }

    template void OpenGLShader::SetUniform<int>(const std::string&, const int&);
    template void OpenGLShader::SetUniform<float>(const std::string&, const float&);
    template void OpenGLShader::SetUniform<glm::vec2>(const std::string&, const glm::vec2&);
    template void OpenGLShader::SetUniform<glm::vec3>(const std::string&, const glm::vec3&);
    template void OpenGLShader::SetUniform<glm::vec4>(const std::string&, const glm::vec4&);
    template void OpenGLShader::SetUniform<glm::mat3>(const std::string&, const glm::mat3&);
    template void OpenGLShader::SetUniform<glm::mat4>(const std::string&, const glm::mat4&);

    void OpenGLShader::SetUniform(const std::string& name, const UniformBox& value)
    {
        auto&& fn = [this, &name](auto&& arg) { this->SetUniform(name, arg); };
        std::visit(fn, value);
    }

    ShaderSrc OpenGLShader::ParseShader(const std::string& path)
    {
        std::ifstream stream(path);
        if (!stream.is_open()) {
            PN_CORE_ASSERT(false, "Invalid shader file path: {0}", path.c_str());
            return ShaderSrc();
        }

        enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;

        while (getline(stream, line)) {
            if (line.find("#shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos)           type = ShaderType::VERTEX;
                else if (line.find("fragment") != std::string::npos)    type = ShaderType::FRAGMENT;
                else {
                    PN_CORE_ASSERT(false, "Invalid shader type: "
                                   "should be either \"#shader vertex\" or \"#shader fragment\".\n"
                                   "                   see file {0}", path.c_str());
                    return ShaderSrc();
                }
            } else {
                ss[(int) type] << line << "\n";
            }
        }
        ShaderSrc src;
        src.vtxsrc = ss[0].str();
        src.frgmsrc = ss[1].str();
        return src;
    }
}
