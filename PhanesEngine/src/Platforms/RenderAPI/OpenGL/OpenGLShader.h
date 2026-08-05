#pragma once

#include <variant>

#include "glm/gtc/type_ptr.hpp"
#include "Phanes/Core/Renderer/Shader/Shader.h"

namespace PN
{
    class OpenGLShader : public Shader
    {
    public:
        using UniformBox = std::variant<
            int,
            float, glm::vec2, glm::vec3, glm::vec4,
            glm::mat3, glm::mat4
        >;

        OpenGLShader(const std::string& path);
        ~OpenGLShader() override;

        void Bind() const override;
        void Unbind() const override;

        int GetUniformLoc(const std::string& name) const override;

        template<typename T>
        void SetUniform(const std::string& name, const T& value);
        void SetUniform(const std::string& name, const UniformBox& value); //support std::variant

    private:
        using shader_container = std::unordered_map<uint32_t, std::string>;

        std::string ReadFile(const std::string& path);
        uint32_t StrToShaderType(const std::string & type);
        shader_container Partition(const std::string& src);
        void Compile(const std::string &path);

    private:
        uint32_t shader_id = 0;
        const std::string filepath;

        // cache
        mutable std::unordered_map<std::string, int> uniform_loc_cache;
    };
}
