#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Phanes
{
    class PN_API Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger_; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger_; }

    private:
        static std::shared_ptr<spdlog::logger> coreLogger_;
        static std::shared_ptr<spdlog::logger> clientLogger_;
    };
}

// Core log macros
#define PN_CORE_LOG_TRACE(...)          ::Phanes::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PN_CORE_LOG_INFO(...)           ::Phanes::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PN_CORE_LOG_WARN(...)           ::Phanes::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PN_CORE_LOG_ERROR(...)          ::Phanes::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PN_CORE_LOG_CRITICAL(...)       ::Phanes::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define PN_CLIENT_LOG_TRACE(...)        ::Phanes::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PN_CLIENT_LOG_INFO(...)         ::Phanes::Log::GetClientLogger()->info(__VA_ARGS__)
#define PN_CLIENT_LOG_WARN(...)         ::Phanes::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PN_CLIENT_LOG_ERROR(...)        ::Phanes::Log::GetClientLogger()->error(__VA_ARGS__)
#define PN_CLIENT_LOG_CRITICAL(...)     ::Phanes::Log::GetClientLogger()->critical(__VA_ARGS__)
