#pragma once

#ifndef _NETWORKLOGGER_HPP_
#define _NETWORKLOGGER_HPP_

#include "ILogger.hpp"

#include <queue>

#include <boost/thread.hpp>
#include "../../HTTPClient/Include/HTTPClient.hpp"

namespace Fnd
{
namespace Logger
{

class NetworkLogger:
	public Fnd::Logger::ILogger
{
	public:

		NetworkLogger();

		bool Initialise( const Fnd::Setup::LoggerSetupData& logger_data );
		void SetWindowSetupData( const Fnd::Setup::WindowSetupData& window_data );
		void SetGraphicsSetupData( const Fnd::Setup::GraphicsSetupData& graphics_data );
		void SetWorldSetupData( const Fnd::Setup::WorldSetupData& world_data );
		void Log( const LogMessage& log_message );
		void Log( const LogError& log_error );
		void Log( const LogWarning& log_warning );

		~NetworkLogger();

	private:
	
		void ThreadFunc();

		bool GetId();

	private:

		std::string _id;

		Fnd::HTTPClient::HTTPClient _http_client;

		boost::mutex _mutex;

		std::queue<std::string> _log_queue;

		boost::thread _thread;
		bool _is_running;
};

}
}

#endif