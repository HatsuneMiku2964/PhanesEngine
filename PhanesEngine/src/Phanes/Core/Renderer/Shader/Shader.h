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
        virtual const std::string& GetName() const = 0;
        virtual const std::string& GetPath() const = 0;

        static Ref<Shader> Create(const std::string& path);
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
