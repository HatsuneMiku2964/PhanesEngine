#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Phanes {
	class PN_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return CoreLogger__; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return ClientLogger__; }

	private:
		static std::shared_ptr<spdlog::logger> CoreLogger__;
		static std::shared_ptr<spdlog::logger> ClientLogger__;
	};
}

// Core log macros
#define PN_CORE_TRACE(...)		::Phanes::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PN_CORE_INFO(...)		::Phanes::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PN_CORE_WARN(...)		::Phanes::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PN_CORE_ERROR(...)		::Phanes::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PN_CORE_CRITICAL(...)		::Phanes::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define PN_CLIENT_TRACE(...)		::Phanes::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PN_CLIENT_INFO(...)		::Phanes::Log::GetClientLogger()->info(__VA_ARGS__)
#define PN_CLIENT_WARN(...)		::Phanes::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PN_CLIENT_ERROR(...)		::Phanes::Log::GetClientLogger()->error(__VA_ARGS__)
#define PN_CLIENT_CRITICAL(...)	::Phanes::Log::GetClientLogger()->critical(__VA_ARGS__)