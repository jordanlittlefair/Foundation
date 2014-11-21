#pragma once

#ifndef _LOGGER_NETWORKLOGGER_HPP_
#define _LOGGER_NETWORKLOGGER_HPP_

#include "ILogger.hpp"

#include <queue>

#include <thread>
#include <mutex>
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

		bool Initialise( const Fnd::Settings::ApplicationSettings::LoggerSettings& logger_data );
		void SetWindowSetupData( const Fnd::Settings::ApplicationSettings::WindowSettings& window_data );
		void SetGraphicsSetupData( const Fnd::Settings::ApplicationSettings::GraphicsSettings& graphics_data );
		void SetWorldSetupData( const Fnd::Settings::ApplicationSettings::WorldSettings& world_data );
		void Log( const LogMessage& log_message );
		void Log( const LogError& log_error );
		void Log( const LogWarning& log_warning );

		void Shutdown();

		~NetworkLogger();

	private:
	
		void ThreadFunc();

		bool GetId();

	private:

		std::string _id;

		Fnd::HTTPClient::HTTPClient _http_client;

		std::mutex _mutex;

		std::queue<std::string> _log_queue;

		std::thread _thread;
		bool _is_running;
};

}
}

#endif