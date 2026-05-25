#pragma once

#ifdef PN_PLATFORMS_WINDOWS
         #ifdef PN_BUILD_DLL
                #define PN_API __declspec(dllexport)
         #else
                #define PN_API __declspec(dllimport)
        #endif
#else
        #error Phanes Engine only supports Windows!
#endif
