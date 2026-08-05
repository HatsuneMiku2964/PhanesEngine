#pragma once

namespace PN
{
    class Shader
    {
    public:
        
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual int GetUniformLoc(const std::string& name) const = 0;

        static Shader* Create(const std::string& path);
    };

}
