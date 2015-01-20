#include "../Include/ConsoleLogger.hpp"

#include "../../Settings/Include/ApplicationSettings.hpp"

using namespace Fnd::Logger;

#include <sstream>

void OutputToConsole( const std::string& str );

#ifdef _WIN32
#include <Windows.h>
void OutputToConsole( const std::string& str )
{
    OutputDebugString( str.c_str() );
}
#else
#include <iostream>
void OutputToConsole( const std::string& str )
{
    std::cout << str << std::endl;
}
#endif

ConsoleLogger::ConsoleLogger()
{
}

bool ConsoleLogger::Initialise( const Fnd::Settings::ApplicationSettings::LoggerSettings& logger_data )
{
	return true;
}

void ConsoleLogger::SetWindowSetupData( const Fnd::Settings::ApplicationSettings::WindowSettings& window_data )
{
	std::stringstream ss;

	ss	<< "Window Data:\n"
		<< "\tImplementation: " << window_data.implementation << "\n"
		<< "\tTitle: " << window_data.window_title << "\n"
		<< "\tSize: " << window_data.initial_width << "x" << window_data.initial_height << "\n"
		<< "\tResizable: " << ( window_data.is_resizable ? "true" : "false" ) << "\n"
		<< "\tFullscreen: " << ( window_data.is_fullscreen ? "true" : "false" ) << "\n";

	OutputToConsole( ss.str() );
}

void ConsoleLogger::SetGraphicsSetupData( const Fnd::Settings::ApplicationSettings::GraphicsSettings& graphics_data )
{
	std::stringstream ss;

	ss	<< "Graphics Data:\n"
		<< "\tImplementation: " << graphics_data.implementation << "\n";

	OutputToConsole( ss.str() );
}

void ConsoleLogger::SetWorldSetupData( const Fnd::Settings::ApplicationSettings::WorldSettings& world_data )
{
	std::stringstream ss;

	ss	<< "World Data:\n"
		<< "\tImplementation: " << world_data.implementation << "\n"
		<< "\tWorld files: " << "can't be arsed to get this from the map" << "\n";

	OutputToConsole( ss.str() );
}

void ConsoleLogger::Log( const LogMessage& log_message )
{
	OutputToConsole( log_message.message + '\n' );
}

void ConsoleLogger::Log( const LogError& log_error )
{
	OutputToConsole( "Error: " + log_error.message + '\n' );
}

void ConsoleLogger::Log( const LogWarning& log_warning )
{
	OutputToConsole( "Warning: " + log_warning.message + '\n' );
}

void ConsoleLogger::Shutdown()
{
}

ConsoleLogger::~ConsoleLogger()
{
}