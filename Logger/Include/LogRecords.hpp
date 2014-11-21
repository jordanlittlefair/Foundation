#pragma once

#ifndef _LOGGER_LOGRECORDS_HPP_
#define _LOGGER_LOGRECORDS_HPP_

#include <string>

#include "../../Settings/Include/GameComponentSettings.hpp"

namespace Fnd
{
namespace Logger
{
	
struct SystemDetails
{
	std::string window;
	std::string graphics;
	std::string world;
};

struct LogMessage
{
	LogMessage(const std::string& message_):message(message_){}
	std::string message;
};

struct LogError
{
	LogError(const std::string& error_message):message(error_message){}
	std::string message;
};

struct LogWarning
{
	LogWarning(const std::string& warning_message):message(warning_message){}
	std::string message;
};

/*
	Methods for reading/writing json
*/
std::string ParseLogSessionIdJson( const std::string& json );
std::string WriteWindowSetupDataJson( const Fnd::Settings::WindowSettings& window_data );
std::string WriteGraphicsSetupDataJson( const Fnd::Settings::GraphicsSettings& graphics_data );
std::string WriteWorldSetupDataJson( const Fnd::Settings::WorldSettings& world_data );
std::string WriteLogMessageJson( const LogMessage& log_message, unsigned int time );
std::string WriteLogErrorJson( const LogError& log_error, unsigned int time );
std::string WriteLogWarningJson( const LogWarning& log_warning, unsigned int time );

}
}

#endif