#pragma once

#include <glm/glm.hpp>

#include "Phanes/Core/Debugging/Log/Log.h"
#include "Phanes/Core/Debugging/Benchmark/Instrumentation.h"

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
        pn_forceinline void SetUniform(const std::string& name, const T& val, uint32_t cnt = 0)
        {
            int loc = GetUniformLoc(name);
            if (loc == -1) return;

            if      constexpr (std::is_same_v<T, int>)          SetUniform_int(loc, val);
            else if constexpr (std::is_same_v<T, int*>)         SetUniform_int_arr(loc, val, cnt);
            else if constexpr (std::is_same_v<T, float>)        SetUniform_float(loc, val);
            else if constexpr (std::is_same_v<T, glm::vec2>)    SetUniform_vec2(loc, val);
            else if constexpr (std::is_same_v<T, glm::vec3>)    SetUniform_vec3(loc, val);
            else if constexpr (std::is_same_v<T, glm::vec4>)    SetUniform_vec4(loc, val);
            else if constexpr (std::is_same_v<T, glm::mat3>)    SetUniform_mat3(loc, val);
            else if constexpr (std::is_same_v<T, glm::mat4>)    SetUniform_mat4(loc, val);
            else                                                PN_CORE_ASSERT(false, "Unsupported Uniform Type!");
        }


        virtual const std::string& GetName() const = 0;
        virtual const std::string& GetPath() const = 0;

        static Ref<Shader> Create(const std::string& path);

    protected:
        virtual void SetUniform_int(int loc, int val) = 0;
        virtual void SetUniform_int_arr(int loc, int* val, uint32_t cnt) = 0;
        virtual void SetUniform_float(int loc, float val) = 0;
        virtual void SetUniform_vec2(int loc, glm::vec2 val) = 0;
        virtual void SetUniform_vec3(int loc, glm::vec3 val) = 0;
        virtual void SetUniform_vec4(int loc, glm::vec4 val) = 0;
        virtual void SetUniform_mat3(int loc, glm::mat3 val) = 0;
        virtual void SetUniform_mat4(int loc, glm::mat4 val) = 0;
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
