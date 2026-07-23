#include "pnpch.h"
#include "Shader.h"

#include <glad/glad.h>

namespace Phanes
{
    Shader::Shader(const std::string& vtxsrc, const std::string& frgmsrc) {
        shader_id = glCreateProgram();
        unsigned int program = shader_id;

        unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
        unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);

        const char* vs_src = vtxsrc.c_str();
        glShaderSource(vs, 1, &vs_src, nullptr);
        glCompileShader(vs);

        const char* fs_src = frgmsrc.c_str();
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
}
