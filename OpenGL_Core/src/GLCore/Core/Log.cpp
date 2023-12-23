#include "pch.hpp"
#include "Log.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace GLCore {

	std::shared_ptr<spdlog::logger> Log::logger;

	void Log::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		logger = spdlog::stdout_color_mt("GLCORE");
		logger->set_level(spdlog::level::trace);
	}

	std::shared_ptr<spdlog::logger>& GLCore::Log::getLogger()
	{
		if (logger == nullptr) {
			init();
		}
		return logger;
	}
}