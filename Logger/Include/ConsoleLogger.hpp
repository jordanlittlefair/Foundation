#pragma once

#ifndef _LOGGER_CONSOLELOGGER_HPP_
#define _LOGGER_CONSOLELOGGER_HPP_

#include "ILogger.hpp"

#include <queue>

#include "../../HTTPClient/Include/HTTPClient.hpp"

namespace Fnd
{
namespace Logger
{

class ConsoleLogger:
	public Fnd::Logger::ILogger
{
	public:

		ConsoleLogger();

		bool Initialise( const Fnd::Settings::ApplicationSettings::LoggerSettings& logger_data );
		void SetWindowSetupData( const Fnd::Settings::ApplicationSettings::WindowSettings& window_data );
		void SetGraphicsSetupData( const Fnd::Settings::ApplicationSettings::GraphicsSettings& graphics_data );
		void SetWorldSetupData( const Fnd::Settings::ApplicationSettings::WorldSettings& world_data );
		void Log( const LogMessage& log_message );
		void Log( const LogError& log_error );
		void Log( const LogWarning& log_warning );

		void Shutdown();

		~ConsoleLogger();
};

}
}

#endif