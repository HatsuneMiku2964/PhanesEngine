#include "pnpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace PN
{
    Ref<spdlog::logger> Log::core_logger;
    Ref<spdlog::logger> Log::client_logger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        core_logger = spdlog::stdout_color_mt("PHANES");
        core_logger->set_level(spdlog::level::trace);

        client_logger = spdlog::stdout_color_mt("APP");
        client_logger->set_level(spdlog::level::trace);

        PN_CORE_LOG_INFO("Log initialized successfully");
    }
}