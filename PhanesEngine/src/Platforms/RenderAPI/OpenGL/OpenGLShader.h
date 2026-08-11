#pragma once

#include <variant>

#include "glm/gtc/type_ptr.hpp"
#include "Phanes/Core/Renderer/Shader/Shader.h"

namespace PN
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& path);
        ~OpenGLShader() override;

        void Bind() const override;
        void Unbind() const override;

        int GetUniformLoc(const std::string& name) const override;
        pn_forceinline const std::string& GetName() const override { return name; }
        pn_forceinline const std::string& GetPath() const override { return filepath; }

    protected:
        void SetUniform_int(const std::string& name, int val) override;
        void SetUniform_float(const std::string& name, float val) override;
        void SetUniform_vec2(const std::string& name, glm::vec2 val) override;
        void SetUniform_vec3(const std::string& name, glm::vec3 val) override;
        void SetUniform_vec4(const std::string& name, glm::vec4 val) override;
        void SetUniform_mat3(const std::string& name, glm::mat3 val) override;
        void SetUniform_mat4(const std::string& name, glm::mat4 val) override;

    private:
        using shader_container = std::unordered_map<uint32_t, std::string>;
        uint32_t            StrToShaderType(const std::string& type) const;

        std::string         ReadFile(const std::string& path) const;
        shader_container    Partition(const std::string& src) const;
        void                Compile(const shader_container& src);

    private:
        uint32_t shader_id = 0;
        const std::string filepath;
        std::string name;

        // cache
        mutable std::unordered_map<std::string, int> uniform_loc_cache;
    };
}
