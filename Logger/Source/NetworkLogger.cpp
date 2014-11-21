#include "../Include/NetworkLogger.hpp"

#include "../../Settings/Include/GameComponentSettings.hpp"

#include <chrono>
#include <cassert>

using namespace Fnd::Logger;

NetworkLogger::NetworkLogger():
	_is_running(false)
{
}

void NetworkLogger::ThreadFunc()
{
	while ( _is_running || !_log_queue.empty() )
	{
		_mutex.lock();

		if ( !_log_queue.empty() )
		{
			HTTPClient::Request request;
			request.method = "POST";
			request.url = "/fndLogServer/createLogRecord";
			request.queries["logSessionId"] = _id;
			request.body = _log_queue.front();
			request.headers["Content-Type"] = "application/json";

			_log_queue.pop();	// TODO: could retry if Send failed?

			HTTPClient::Response response;

			_http_client.Send( request, response );

			_mutex.unlock();
		}
		else
		{
			_mutex.unlock();
			std::this_thread::sleep_for( std::chrono::seconds(2) );
		}
	}
}
			
NetworkLogger::~NetworkLogger()
{
	// The thread MUST be stopped/joined in Shutdown.
	// Calling join() here (global object destructor, after main) will cause the app to hang.
	assert( !_is_running );

	// Also, there is a known issue in VS2012- it will always leak 44 bytes when using std::thread.
	// This is fixed in VS2013.
	// https://connect.microsoft.com/VisualStudio/feedback/details/757212/vs-2012-rc-std-thread-reports-memory-leak-even-on-stack
}

bool NetworkLogger::Initialise( const Fnd::Settings::LoggerSettings& logger_data )
{
	_http_client.SetServer( logger_data.server );
	_http_client.SetPort( logger_data.port );

	if ( !GetId() )
	{
		return false;
	}

	_is_running = true;
	_thread = std::thread( &NetworkLogger::ThreadFunc, this );

	return true;
}

void NetworkLogger::SetWindowSetupData( const Fnd::Settings::WindowSettings& window_data )
{
	std::lock_guard<std::mutex> lock(_mutex);
	
	std::string json = WriteWindowSetupDataJson( window_data );

	HTTPClient::Request request;
	request.method = "POST";
	request.url = "/fndLogServer/setSessionDetails";
	request.queries["logSessionId"] = _id;
	request.body = json;
	request.headers["Content-Type"] = "application/json";

	HTTPClient::Response response;
	_http_client.Send( request, response );
}

void NetworkLogger::SetGraphicsSetupData( const Fnd::Settings::GraphicsSettings& graphics_data )
{
	std::lock_guard<std::mutex> lock(_mutex);
	
	std::string json = WriteGraphicsSetupDataJson( graphics_data );

	HTTPClient::Request request;
	request.method = "POST";
	request.url = "/fndLogServer/setSessionDetails";
	request.queries["logSessionId"] = _id;
	request.body = json;
	request.headers["Content-Type"] = "application/json";

	HTTPClient::Response response;
	_http_client.Send( request, response );
}

void NetworkLogger::SetWorldSetupData( const Fnd::Settings::WorldSettings& world_data )
{
	std::lock_guard<std::mutex> lock(_mutex);
	
	std::string json = WriteWorldSetupDataJson( world_data );

	HTTPClient::Request request;
	request.method = "POST";
	request.url = "/fndLogServer/setSessionDetails";
	request.queries["logSessionId"] = _id;
	request.body = json;
	request.headers["Content-Type"] = "application/json";

	HTTPClient::Response response;
	_http_client.Send( request, response );
}

void NetworkLogger::Log( const LogMessage& log_message )
{
	std::lock_guard<std::mutex> lock(_mutex);

	unsigned int t = (unsigned int)time(nullptr);

	std::string json = WriteLogMessageJson( log_message, t );

	_log_queue.push( json );
}

void NetworkLogger::Log( const LogError& log_error )
{
	std::lock_guard<std::mutex> lock(_mutex);

	unsigned int t = (unsigned int)time(nullptr);
	
	std::string json = WriteLogErrorJson( log_error, t );

	_log_queue.push( json );
}

void NetworkLogger::Log( const LogWarning& log_warning )
{
	std::lock_guard<std::mutex> lock(_mutex);

	unsigned int t = (unsigned int)time(nullptr);
	
	std::string json = WriteLogWarningJson( log_warning, t );

	_log_queue.push( json );
}

void NetworkLogger::Shutdown()
{
	if ( _is_running )
	{
		_is_running = false;
		_thread.join();
	}
}

bool NetworkLogger::GetId()
{
	std::lock_guard<std::mutex> lock(_mutex);
	
	HTTPClient::Request request;
	request.method = "POST";
	request.url = "/fndLogServer/createLogSession";

	HTTPClient::Response response;

	if ( !_http_client.Send( request, response ) )
	{
		return false;
	}
	if ( response.return_code != 201 )
	{
		return false;
	}

	_id = ParseLogSessionIdJson(response.body);

	return true;
}