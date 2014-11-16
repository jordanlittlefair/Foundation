#include "../Include/NetworkLogger.hpp"

#include "../../Setup/Include/GameComponentData.hpp"

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
			boost::posix_time::millisec t(1000);
			boost::this_thread::sleep(t); 
		}
	}
}
			
NetworkLogger::~NetworkLogger()
{
	if ( _is_running )
	{
		_is_running = false;
		_thread.join();
	}
}

bool NetworkLogger::Initialise( const Fnd::Setup::LoggerSetupData& logger_data )
{
	_http_client.SetServer( logger_data.server );
	_http_client.SetPort( logger_data.port );

	if ( !GetId() )
	{
		return false;
	}

	_is_running = true;
	_thread = boost::thread(&NetworkLogger::ThreadFunc, this);

	return true;
}

void NetworkLogger::SetWindowSetupData( const Fnd::Setup::WindowSetupData& window_data )
{
	boost::mutex::scoped_lock lock(_mutex);
	
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

void NetworkLogger::SetGraphicsSetupData( const Fnd::Setup::GraphicsSetupData& graphics_data )
{
	boost::mutex::scoped_lock lock(_mutex);
	
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

void NetworkLogger::SetWorldSetupData( const Fnd::Setup::WorldSetupData& world_data )
{
	boost::mutex::scoped_lock lock(_mutex);
	
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
	boost::mutex::scoped_lock lock(_mutex);

	unsigned int t = (unsigned int)time(nullptr);

	std::string json = WriteLogMessageJson( log_message, t );

	_log_queue.push( json );
}

void NetworkLogger::Log( const LogError& log_error )
{
	boost::mutex::scoped_lock lock(_mutex);

	unsigned int t = (unsigned int)time(nullptr);
	
	std::string json = WriteLogErrorJson( log_error, t );

	_log_queue.push( json );
}

void NetworkLogger::Log( const LogWarning& log_warning )
{
	boost::mutex::scoped_lock lock(_mutex);

	unsigned int t = (unsigned int)time(nullptr);
	
	std::string json = WriteLogWarningJson( log_warning, t );

	_log_queue.push( json );
}

bool NetworkLogger::GetId()
{
	boost::mutex::scoped_lock lock(_mutex);
	
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