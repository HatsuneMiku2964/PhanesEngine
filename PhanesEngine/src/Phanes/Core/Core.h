#pragma once

// API
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
#else
    #error Phanes Engine only supports Windows!
#endif

// Asserts
#ifdef PN_ENABLE_ASSERTS
    #define PN_ASSERT(x, ...) { if(!(x)) { PN_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define PN_CORE_ASSERT(x, ...) { if(!(x)) { PN_CORE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define PN_ASSERT(x, ...)
    #define PN_CORE_ASSERT(x, ...)
#endif

// Bitwise
#define BIT_PUSH(x) (1 << x)

// Event binding
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

// Inlining
#ifdef _MSC_VER
    #define pn_forceinline __forceinline
#elif defined(__GNUC__) || defined(__clang__)
    #define pn_forceinline __attribute__((always_inline)) inline
#else
    #define pn_forceinline inline
#endif

// Memory
#include <memory>
namespace PN {
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;
}