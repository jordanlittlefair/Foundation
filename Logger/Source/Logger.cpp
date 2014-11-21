#include "../Include/Logger.hpp"

#include "../../HTTPClient/Include/HTTPClient.hpp"
#include "../../Settings/Include/ApplicationSettings.hpp"
#include "../../Settings/Include/EngineConfig.hpp"

#include "../Include/ILogger.hpp"
#include "../Include/NetworkLogger.hpp"
#include "../Include/ConsoleLogger.hpp"

#include <queue>

using namespace Fnd::Logger;

Logger::Logger()
{
}

Logger& Logger::GetInstance()
{
	static Logger logger;
	return logger;
}

bool Logger::Initialise( const Fnd::Settings::ApplicationSettings::LoggerSettings& logger_data )
{
	if ( logger_data.implementations | Settings::EngineConfig::NetworkLogger_implementation )
	{
		_impl.push_back(std::move(std::unique_ptr<NetworkLogger>(new NetworkLogger())));
	}

	if ( logger_data.implementations | Settings::EngineConfig::ConsoleLogger_implementation )
	{
		_impl.push_back(std::move(std::unique_ptr<ConsoleLogger>(new ConsoleLogger())));
	}

	for ( unsigned int i = 0; i < _impl.size(); ++i )
	{
		if ( !_impl[i]->Initialise( logger_data ) )
		{
			_impl[i].reset(nullptr);
		}
	}

	_impl.erase( std::remove_if( _impl.begin(), _impl.end(), 
		[] (const std::unique_ptr<ILogger>& logger) -> bool
		{
			return !logger.get(); 
		}
		),
		_impl.end());

	return true;
}

void Logger::SetWindowSetupData( const Fnd::Settings::ApplicationSettings::WindowSettings& window_data )
{
	for ( unsigned int i = 0; i < _impl.size(); ++i )
	{
		_impl[i]->SetWindowSetupData( window_data );
	}
}

void Logger::SetGraphicsSetupData( const Fnd::Settings::ApplicationSettings::GraphicsSettings& graphics_data )
{
	for ( unsigned int i = 0; i < _impl.size(); ++i )
	{
		_impl[i]->SetGraphicsSetupData( graphics_data );
	}
}

void Logger::SetWorldSetupData( const Fnd::Settings::ApplicationSettings::WorldSettings& world_data )
{
	for ( unsigned int i = 0; i < _impl.size(); ++i )
	{
		_impl[i]->SetWorldSetupData( world_data );
	}
}

void Logger::Log( const LogMessage& log_message )
{	
	for ( unsigned int i = 0; i < _impl.size(); ++i )
	{
		_impl[i]->Log( log_message );
	}
}

void Logger::Log( const LogError& log_error )
{	
	for ( unsigned int i = 0; i < _impl.size(); ++i )
	{
		_impl[i]->Log( log_error );
	}
}

void Logger::Log( const LogWarning& log_warning )
{	
	for ( unsigned int i = 0; i < _impl.size(); ++i )
	{
		_impl[i]->Log( log_warning );
	}
}

void Logger::Shutdown()
{
	for ( unsigned int i = 0; i < _impl.size(); ++i )
	{
		_impl[i]->Shutdown();
	}
}

Logger::~Logger()
{
}