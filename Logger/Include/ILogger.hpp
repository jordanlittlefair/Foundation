#pragma once

#ifndef _LOGGER_ILOGGER_HPP_
#define _LOGGER_ILOGGER_HPP_

#include "LogRecords.hpp"

#include "../../Settings/Include/ApplicationSettings.hpp"

namespace Fnd
{
namespace Logger
{

class ILogger
{
	public:

		virtual bool Initialise( const Fnd::Settings::ApplicationSettings::LoggerSettings& logger_data ) = 0;
		virtual void SetWindowSetupData( const Fnd::Settings::ApplicationSettings::WindowSettings& window_data ) = 0;
		virtual void SetGraphicsSetupData( const Fnd::Settings::ApplicationSettings::GraphicsSettings& graphics_data ) = 0;
		virtual void SetWorldSetupData( const Fnd::Settings::ApplicationSettings::WorldSettings& world_data ) = 0;
		virtual void Log( const LogMessage& log_message ) = 0;
		virtual void Log( const LogError& log_error ) = 0;
		virtual void Log( const LogWarning& log_warning ) = 0;

		// This must be called to stop any threads.
		// Destroying the Logger (a static object) happens after main() exits.
		// Any threads running will cause join() to hang if called in the destructor.
		virtual void Shutdown() = 0;

		virtual ~ILogger() {};
};

}
}

#endif