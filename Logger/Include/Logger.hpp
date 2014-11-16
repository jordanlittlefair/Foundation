#pragma once

#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include "LogRecords.hpp"
#include "ILogger.hpp"

#include <memory>
#include <vector>
#include <sstream>

namespace Fnd
{
namespace Setup
{
struct LoggerSetupData;
}
}

namespace Fnd
{
namespace Logger
{

class Logger:
	public Fnd::Logger::ILogger
{
	public:

		static Logger& GetInstance();

		bool Initialise( const Fnd::Setup::LoggerSetupData& logger_data );
		void SetWindowSetupData( const Fnd::Setup::WindowSetupData& window_data );
		void SetGraphicsSetupData( const Fnd::Setup::GraphicsSetupData& graphics_data );
		void SetWorldSetupData( const Fnd::Setup::WorldSetupData& world_data );
		void Log( const LogMessage& log_message );
		void Log( const LogError& log_error );
		void Log( const LogWarning& log_warning );
		
		~Logger();

	private:

		Logger();

		std::vector<std::unique_ptr<ILogger>> _impl;
};

}
}

#endif