#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

/*
	DUE TO GLCore::Log::logger being a shared pointer, you can not call 
	getLogger inside of destructors because logger might already be deleted
*/

namespace GLCore {

	class Log {
	private:
		static std::shared_ptr<spdlog::logger> logger;
	public:
		static void init();
		static std::shared_ptr<spdlog::logger>& getLogger();
	};
}

// Client log macros
#ifdef DEBUG
	#define LOG_TRACE(...)         ::GLCore::Log::getLogger()->trace(__VA_ARGS__)
	#define LOG_INFO(...)          ::GLCore::Log::getLogger()->info(__VA_ARGS__)
	#define LOG_WARN(...)          ::GLCore::Log::getLogger()->warn(__VA_ARGS__)
	#define LOG_ERROR(...)         ::GLCore::Log::getLogger()->error(__VA_ARGS__)
	#define LOG_CRITICAL(...)      ::GLCore::Log::getLogger()->critical(__VA_ARGS__)
#else
	#define LOG_TRACE(...)         
	#define LOG_INFO(...)          
	#define LOG_WARN(...)          
	#define LOG_ERROR(...)        
	#define LOG_CRITICAL(...)    
#endif