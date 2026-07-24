#pragma once

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

        static ShaderSrc ParseShader(const std::string &path);
    private:
        unsigned int shader_id = 0;
        const std::string filepath;
    };

}
