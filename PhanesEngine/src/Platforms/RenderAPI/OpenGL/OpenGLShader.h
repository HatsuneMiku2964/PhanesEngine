#pragma once

#include <variant>

#include "glm/gtc/type_ptr.hpp"
#include "Phanes/Renderer/Shader/Shader.h"

namespace Phanes
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

        static ShaderSrc ParseShader(const std::string& path);
    private:
        uint32_t shader_id = 0;
        const std::string filepath;

        // cache
        mutable std::unordered_map<std::string, int> uniform_loc_cache;
    };
}
