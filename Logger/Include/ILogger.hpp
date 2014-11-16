#pragma once

#ifndef _ILOGGER_HPP_
#define _ILOGGER_HPP_

#include "LogRecords.hpp"

namespace Fnd
{
namespace Setup
{
struct LoggerSetupData;
struct WindowSetupData;
struct GraphicsSetupData;
struct WorldSetupData;
}
}

namespace Fnd
{
namespace Logger
{

class ILogger
{
	public:

		virtual bool Initialise( const Fnd::Setup::LoggerSetupData& logger_data ) = 0;
		virtual void SetWindowSetupData( const Fnd::Setup::WindowSetupData& window_data ) = 0;
		virtual void SetGraphicsSetupData( const Fnd::Setup::GraphicsSetupData& graphics_data ) = 0;
		virtual void SetWorldSetupData( const Fnd::Setup::WorldSetupData& world_data ) = 0;
		virtual void Log( const LogMessage& log_message ) = 0;
		virtual void Log( const LogError& log_error ) = 0;
		virtual void Log( const LogWarning& log_warning ) = 0;

		virtual ~ILogger() {};
};

}
}

#endif