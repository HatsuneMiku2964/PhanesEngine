#pragma once

namespace Phanes
{
    class Shader
    {
    public:
        Shader(const std::string& vtxsrc, const std::string& frgmsrc);
        ~Shader();

        virtual void Bind() const;
        virtual void Unbind() const;
    private:
        unsigned int shader_id = 0;
    };

}
