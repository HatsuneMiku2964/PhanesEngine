#include "pnpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace PN
{
    OpenGLShader::OpenGLShader(const std::string& path)
        : filepath(path)
    {
        std::string src_str = ReadFile(path);
        shader_container src = Partition(src_str);
        Compile(src);

        // extract name from the path
        size_t beg = path.find_last_of("/\\");
        beg = (beg == std::string::npos) ? 0 : beg + 1;

        size_t end = path.find_last_of('.');
        end = (end == std::string::npos) ? 0 : end;

        name = path.substr(beg, end - beg);
    }
    OpenGLShader::~OpenGLShader() { glDeleteProgram(shader_id); }

    void OpenGLShader::Bind() const { glUseProgram(shader_id); }
    void OpenGLShader::Unbind() const { glUseProgram(0); }

    int OpenGLShader::GetUniformLoc(const std::string& name) const
    {
        if (uniform_loc_cache.contains(name)) return uniform_loc_cache.at(name);

        int result = glGetUniformLocation(shader_id, name.c_str());
        if (result == -1) PN_CORE_LOG_ERROR("invalid uniform location of name \"{0}\"!!", name.c_str());
        uniform_loc_cache[name] = result;
        return result;
    }

    template <typename T>
    void OpenGLShader::SetUniform(const std::string& name, const T& value)
    {
        int location = GetUniformLoc(name);
        if (location == -1) return;

        if      constexpr (std::is_same_v<T, int>)          glUniform1i(location, value);
        else if constexpr (std::is_same_v<T, float>)        glUniform1f(location, value);
        else if constexpr (std::is_same_v<T, glm::vec2>)    glUniform2f(location, value.x, value.y);
        else if constexpr (std::is_same_v<T, glm::vec3>)    glUniform3f(location, value.x, value.y, value.z);
        else if constexpr (std::is_same_v<T, glm::vec4>)    glUniform4f(location, value.x, value.y, value.z, value.w);
        else if constexpr (std::is_same_v<T, glm::mat3>)    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
        else if constexpr (std::is_same_v<T, glm::mat4>)    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
        else                                                PN_CORE_ASSERT(false, "Unsupported Uniform Type!");
    }
    void OpenGLShader::SetUniform(const std::string& name, const UniformBox& value)
    {
        auto&& fn = [this, &name](auto&& arg) { this->SetUniform(name, arg); };
        std::visit(fn, value);
    }

    uint32_t OpenGLShader::StrToShaderType(const std::string& type) const
    {
        if (type == "vertex")   return GL_VERTEX_SHADER;
        if (type == "fragment") return GL_FRAGMENT_SHADER;

        PN_CORE_LOG_ERROR("invalid shader type of \"{0}\"", type);
        return 0;
    }
    std::string OpenGLShader::ReadFile(const std::string& path) const
    {
        std::ifstream in(path, std::ios::in | std::ios::binary | std::ios::ate);
        if (!in) { PN_CORE_ASSERT(false, "Invalid shader file path: {0}", path.c_str()); return {}; }

        std::string src;

        src.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(src.data(), src.size());
        in.close();

        return src;
    }
    std::unordered_map<uint32_t, std::string> OpenGLShader::Partition(const std::string& src) const
    {
        std::unordered_map<uint32_t, std::string> res;
        const char* token = "#shader";
        size_t token_len = strlen(token);
        size_t start_pos = src.find(token);

        while (start_pos != std::string::npos)
        {
            size_t eol = src.find_first_of("\r\n", start_pos);
            PN_CORE_ASSERT(eol != std::string::npos, "syntax error");

            size_t type_start = start_pos + token_len + 1;
            std::string type = src.substr(type_start, eol - type_start);
            PN_CORE_ASSERT(StrToShaderType(type), "syntax error: invalid shader type");

            size_t next = src.find_first_not_of("\r\n", eol);
            if (next == std::string::npos) break;
            start_pos = src.find(token, next);

            size_t end_pos = (start_pos == std::string::npos) ? src.size() : start_pos;
            res[StrToShaderType(type)] = src.substr(next, end_pos - next);
        }

        return res;
    }
    void OpenGLShader::Compile(const shader_container& src)
    {
        uint32_t program = glCreateProgram();

        static constexpr uint8_t max_shaders_amt_support = 2; // INFO: we only support 2 shaders now
        PN_CORE_ASSERT(src.size() <= max_shaders_amt_support, "we only support 2 shaders now!!");
        std::array<uint32_t, max_shaders_amt_support> shaders;

        int shader_cnt = 0;
        for (const auto& [type, str] : src)
        {
            uint32_t shader = glCreateShader(type);
            const char* src = str.c_str();
            glShaderSource(shader, 1, &src, nullptr);
            glCompileShader(shader);
            {
                int compiled;
                glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
                if (!compiled) {
                    int len;
                    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
                    std::vector<char> message(len);
                    glGetShaderInfoLog(shader, len, &len, message.data());
                    PN_CORE_ASSERT(false, "{0}", message.data());
                    break;
                }
            }
            glAttachShader(program, shader);
            shaders[shader_cnt++] = shader;
        }

        glLinkProgram(program);
        {
            int linked;
            glGetProgramiv(program, GL_LINK_STATUS, &linked);
            if (!linked) {
                int len;
                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
                std::vector<char> message(len);
                glGetProgramInfoLog(program, len, &len, message.data());
                PN_CORE_ASSERT(false, "{0}", message.data());

                glDeleteProgram(program);
                for (uint32_t shader : shaders) glDeleteShader(shader);
                return;
            }
        }
        glValidateProgram(program);

        for (uint32_t shader : shaders) {
            glDetachShader(program, shader);
            glDeleteShader(shader);
        }

        shader_id = program;
    }
}

namespace PN
{
    template void OpenGLShader::SetUniform<int>(const std::string&, const int&);
    template void OpenGLShader::SetUniform<float>(const std::string&, const float&);
    template void OpenGLShader::SetUniform<glm::vec2>(const std::string&, const glm::vec2&);
    template void OpenGLShader::SetUniform<glm::vec3>(const std::string&, const glm::vec3&);
    template void OpenGLShader::SetUniform<glm::vec4>(const std::string&, const glm::vec4&);
    template void OpenGLShader::SetUniform<glm::mat3>(const std::string&, const glm::mat3&);
    template void OpenGLShader::SetUniform<glm::mat4>(const std::string&, const glm::mat4&);
}