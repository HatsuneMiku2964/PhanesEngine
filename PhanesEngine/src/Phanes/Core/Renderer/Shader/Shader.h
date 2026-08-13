#pragma once

#include <glm/glm.hpp>

#include "Phanes/Core/Debugging/Log/Log.h"

namespace PN
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual int GetUniformLoc(const std::string& name) const = 0;
        template<typename T>
        pn_forceinline void SetUniform(const std::string& name, const T& value)
        {
            int location = GetUniformLoc(name);
            if (location == -1) return;

            if      constexpr (std::is_same_v<T, int>)          SetUniform_int(name, value);
            else if constexpr (std::is_same_v<T, float>)        SetUniform_float(name, value);
            else if constexpr (std::is_same_v<T, glm::vec2>)    SetUniform_vec2(name, value);
            else if constexpr (std::is_same_v<T, glm::vec3>)    SetUniform_vec3(name, value);
            else if constexpr (std::is_same_v<T, glm::vec4>)    SetUniform_vec4(name, value);
            else if constexpr (std::is_same_v<T, glm::mat3>)    SetUniform_mat3(name, value);
            else if constexpr (std::is_same_v<T, glm::mat4>)    SetUniform_mat4(name, value);
            else                                                PN_CORE_ASSERT(false, "Unsupported Uniform Type!");
        }


        virtual const std::string& GetName() const = 0;
        virtual const std::string& GetPath() const = 0;

        static Ref<Shader> Create(const std::string& path);

    protected:
        virtual void SetUniform_int(const std::string& name, int val) = 0;
        virtual void SetUniform_float(const std::string& name, float val) = 0;
        virtual void SetUniform_vec2(const std::string& name, glm::vec2 val) = 0;
        virtual void SetUniform_vec3(const std::string& name, glm::vec3 val) = 0;
        virtual void SetUniform_vec4(const std::string& name, glm::vec4 val) = 0;
        virtual void SetUniform_mat3(const std::string& name, glm::mat3 val) = 0;
        virtual void SetUniform_mat4(const std::string& name, glm::mat4 val) = 0;
    };

    class ShaderManager
    {
    public:
        void Add(const Ref<Shader>& shader);
        void Add(const std::string& name, const Ref<Shader>& shader);

        Ref<Shader> Load(const std::string& filepath);
        Ref<Shader> Load(const std::string& name, const std::string& filepath);

        Ref<Shader> Get(const std::string& name);
        pn_forceinline bool Exists(const std::string& name) const { return shaders.contains(name); }

    private:
        std::unordered_map<std::string, Ref<Shader>> shaders;
    };

}
