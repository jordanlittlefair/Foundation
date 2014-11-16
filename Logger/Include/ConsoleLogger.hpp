#pragma once

#ifndef _CONSOLELOGGER_HPP_
#define _CONSOLELOGGER_HPP_

#include "ILogger.hpp"

#include <queue>

#include <boost/thread.hpp>
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

		bool Initialise( const Fnd::Setup::LoggerSetupData& logger_data );
		void SetWindowSetupData( const Fnd::Setup::WindowSetupData& window_data );
		void SetGraphicsSetupData( const Fnd::Setup::GraphicsSetupData& graphics_data );
		void SetWorldSetupData( const Fnd::Setup::WorldSetupData& world_data );
		void Log( const LogMessage& log_message );
		void Log( const LogError& log_error );
		void Log( const LogWarning& log_warning );

		~ConsoleLogger();
};

}
}

#endif