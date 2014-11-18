#include "../Include/ConsoleLogger.hpp"

#include "../../Setup/Include/GameComponentData.hpp"

using namespace Fnd::Logger;

#include <sstream>

#include <Windows.h>

ConsoleLogger::ConsoleLogger()
{
}

bool ConsoleLogger::Initialise( const Fnd::Setup::LoggerSetupData& logger_data )
{
	return true;
}

void ConsoleLogger::SetWindowSetupData( const Fnd::Setup::WindowSetupData& window_data )
{
	std::stringstream ss;

	ss	<< "Window Data:\n"
		<< "\tImplementation: " << window_data.window << "\n"
		<< "\tTitle: " << window_data.window_title << "\n"
		<< "\tSize: " << window_data.initial_width << "x" << window_data.initial_height << "\n"
		<< "\tResizable: " << ( window_data.is_resizable ? "true" : "false" ) << "\n"
		<< "\tFullscreen: " << ( window_data.is_fullscreen ? "true" : "false" ) << "\n";

	OutputDebugString( ss.str().c_str() );
}

void ConsoleLogger::SetGraphicsSetupData( const Fnd::Setup::GraphicsSetupData& graphics_data )
{
	std::stringstream ss;

	ss	<< "Graphics Data:\n"
		<< "\tImplementation: " << graphics_data.graphics << "\n";

	OutputDebugString( ss.str().c_str() );
}

void ConsoleLogger::SetWorldSetupData( const Fnd::Setup::WorldSetupData& world_data )
{
	std::stringstream ss;

	ss	<< "World Data:\n"
		<< "\tImplementation: " << world_data.world << "\n"
		<< "\tWorld files: " << "can't be arsed to get this from the map" << "\n";

	OutputDebugString( ss.str().c_str() );
}

void ConsoleLogger::Log( const LogMessage& log_message )
{
	OutputDebugString( ( log_message.message + '\n' ).c_str() );
}

void ConsoleLogger::Log( const LogError& log_error )
{
	OutputDebugString( ( "Error: " + log_error.message + '\n' ).c_str() );
}

void ConsoleLogger::Log( const LogWarning& log_warning )
{
	OutputDebugString( ( "Warning: " + log_warning.message + '\n' ).c_str() );
}

void ConsoleLogger::Shutdown()
{
}

ConsoleLogger::~ConsoleLogger()
{
}