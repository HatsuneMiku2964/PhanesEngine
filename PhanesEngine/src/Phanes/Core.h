#pragma once

// API
#ifdef PN_PLATFORMS_WINDOWS
         #ifdef PN_BUILD_DLL
                #define PN_API __declspec(dllexport)
        #else
                #define PN_API __declspec(dllimport)
        #endif
#else
        #error Phanes Engine only supports Windows!
#endif

// Asserts
#ifdef PN_ENABLE_ASSERTS
        #define PN_ASSERT(x, ...) { if(!x) {PN_CLIENT_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
        #define PN_CORE_ASSERT(x, ...) { if(!x) { PN_CORE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
        #define PN_ASSERT(x, ...) 
        #define PN_CORE_ASSERT(x, ...)
#endif

// Bitwise
#define BIT_PUSH(x) (1 << x)