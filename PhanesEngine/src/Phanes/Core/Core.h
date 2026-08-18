#pragma once

// Platform
#ifdef _WIN32
    #ifdef _WIN64
        #define PN_PLATFORMS_WINDOWS
    #else
        #error "Phanes Engine do not support Win32 yet!!!"
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>

    #if TARGET_IPHONE_SIMULATOR == 1
        #error "iPhone simulator is not supported yet!!"
    #elif TARGET_OS_IPHONE == 1
        #define PN_PLATFORMS_IOS
        #error "IOS is not supported yet!!"
    #elif TARGET_OS_MAC == 1
        #define PN_PLATFORMS_MACOS
        #error "macOS is not supported yet!!"
    #else
        #error "Unknown Apple platform!!"
    #endif
#elif defined(__ANDROID__)
    #define PN_PLATFORMS_ANDROID
    #error "Android is not supported yet!!"
#elif defined(__linux__)
    #define PN_PLATFORMS_LINUX
    #error "linux is not supported yet!!"
#endif

// DLL build
#ifdef PN_PLATFORMS_WINDOWS
    #if PN_DY_LKN
        #ifdef PN_BUILD_DLL
            #define PN_API __declspec(dllexport)
        #else
            #define PN_API __declspec(dllimport)
        #endif
    #else
        #define PN_API
    #endif
#endif

// Asserts
#ifdef PN_ENABLE_ASSERTS
    #define PN_ASSERT(x, ...) { if(!(x)) { PN_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define PN_CORE_ASSERT(x, ...) { if(!(x)) { PN_CORE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define PN_ASSERT(x, ...)
    #define PN_CORE_ASSERT(x, ...)
#endif


// Inlining
#ifdef _MSC_VER
    #define pn_forceinline __forceinline
#elif defined(__GNUC__) || defined(__clang__)
    #define pn_forceinline __attribute__((always_inline)) inline
#else
    #define pn_forceinline inline
#endif

// Macro
#define PN_TOKEN_CONCAT_IMPL(a, b) a##b
#define PN_TOKEN_CONCAT(a, b) PN_TOKEN_CONCAT_IMPL(a, b)

// Event binding
#define BIND_EVENT_FN(fn) ::PN::BindEventFn(&std::remove_reference_t<decltype(*this)>::fn, this)

// Memory
#include <memory>
namespace PN
{
    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename... Args>
    constexpr Scope<T> CreateScope(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename... Args>
    constexpr Ref<T> CreateRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}
