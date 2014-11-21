#pragma once

#ifndef _LOGGER_LOGGER_HPP_
#define _LOGGER_LOGGER_HPP_

#include "LogRecords.hpp"
#include "ILogger.hpp"

#include <memory>
#include <vector>
#include <sstream>

namespace Fnd
{
namespace Logger
{

class Logger:
	public Fnd::Logger::ILogger
{
	public:

		static Logger& GetInstance();

		bool Initialise( const Fnd::Settings::LoggerSettings& logger_data );
		void SetWindowSetupData( const Fnd::Settings::WindowSettings& window_data );
		void SetGraphicsSetupData( const Fnd::Settings::GraphicsSettings& graphics_data );
		void SetWorldSetupData( const Fnd::Settings::WorldSettings& world_data );
		void Log( const LogMessage& log_message );
		void Log( const LogError& log_error );
		void Log( const LogWarning& log_warning );
		
		void Shutdown();

		~Logger();

	private:

		Logger();

		std::vector<std::unique_ptr<ILogger>> _impl;
};

}
}

#endif