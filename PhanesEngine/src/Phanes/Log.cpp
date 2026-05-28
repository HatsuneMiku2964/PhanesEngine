#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Phanes {
	std::shared_ptr<spdlog::logger> Log::CoreLogger__;
	std::shared_ptr<spdlog::logger> Log::ClientLogger__;

	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		CoreLogger__ = spdlog::stdout_color_mt("PHANES");
		CoreLogger__->set_level(spdlog::level::trace);

		ClientLogger__ = spdlog::stdout_color_mt("APP");
		ClientLogger__->set_level(spdlog::level::trace);
	}
}