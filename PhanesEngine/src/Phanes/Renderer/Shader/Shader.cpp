#include "pnpch.h"
#include "Shader.h"

#include <glad/glad.h>

namespace Phanes
{
    Shader::Shader(const std::string& path)
    {
        ShaderSrc src = ParseShader(path);

        shader_id = glCreateProgram();
        unsigned int program = shader_id;

        unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
        unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);

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
    Shader::~Shader() { glDeleteProgram(shader_id); }

    void Shader::Bind() const { glUseProgram(shader_id); }
    void Shader::Unbind() const { glUseProgram(0); }

    ShaderSrc Shader::ParseShader(const std::string &path)
    {
        std::ifstream stream(path);
        if (!stream.is_open()) {
            PN_CORE_LOG_ERROR("Invalid shader file path: {0}", path.c_str());
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
                    PN_CORE_LOG_ERROR("Invalid shader type: "
                                      "should be either \"#shader vertex\" or \"#shader fragment\".\n"
                                      "                   see file {0}", path.c_str());
                    return ShaderSrc();
                }
            } else {
                ss[(int) type] << line << "\n";
            }
        }
        ShaderSrc src;
        src.vtxsrc =    ss[0].str();
        src.frgmsrc =   ss[1].str();
        return src;
    }
}
