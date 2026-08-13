#pragma once

#include "Phanes/Core/Core.h"
#include "spdlog/spdlog.h"

namespace PN
{
    class Log
    {
    public:
        static void Init();

        pn_forceinline static Ref<spdlog::logger>& GetCoreLogger() { return coreLogger_; }
        pn_forceinline static Ref<spdlog::logger>& GetClientLogger() { return clientLogger_; }

    private:
        static Ref<spdlog::logger> coreLogger_;
        static Ref<spdlog::logger> clientLogger_;
    };
}

// Core log macros
#define PN_CORE_LOG_TRACE(...)          ::PN::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PN_CORE_LOG_INFO(...)           ::PN::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PN_CORE_LOG_WARN(...)           ::PN::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PN_CORE_LOG_ERROR(...)          ::PN::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PN_CORE_LOG_CRITICAL(...)       ::PN::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define PN_LOG_TRACE(...)               ::PN::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PN_LOG_INFO(...)                ::PN::Log::GetClientLogger()->info(__VA_ARGS__)
#define PN_LOG_WARN(...)                ::PN::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PN_LOG_ERROR(...)               ::PN::Log::GetClientLogger()->error(__VA_ARGS__)
#define PN_LOG_CRITICAL(...)            ::PN::Log::GetClientLogger()->critical(__VA_ARGS__)
