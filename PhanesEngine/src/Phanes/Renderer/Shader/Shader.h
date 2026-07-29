#pragma once

#include <glm/glm.hpp>

namespace Phanes
{
    struct ShaderSrc
    {
        std::string vtxsrc;
        std::string frgmsrc;
    };
    class Shader
    {
    public:
        Shader(const std::string &path);
        ~Shader();

        virtual void Bind() const;
        virtual void Unbind() const;

        void SetUniformMat4(const std::string& name, const glm::mat4& value);

        static ShaderSrc ParseShader(const std::string &path);
    private:
        uint32_t shader_id = 0;
        const std::string filepath;
    };

}
