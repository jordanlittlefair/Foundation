#pragma once

#ifndef _SETTINGS_APPLICATIONSETTINGS_HPP_
#define _SETTINGS_APPLICATIONSETTINGS_HPP_

#include "EngineConfig.hpp"

#include <vector>
#include <map>

namespace Fnd
{
namespace Settings
{

class ApplicationSettings
{
	public:
		
		/**
			A struct to store the data required to initialise a logger.
		*/
		struct LoggerSettings
		{
			int implementations;	// flags from EngineConfig
			std::string server;
			std::string port;
		};

		/**
			A struct to store the data required to initialise a window.
		*/
		struct WindowSettings
		{
			EngineConfig::WindowImplementation implementation;
			std::string window_title;
			unsigned int initial_width;
			unsigned int initial_height;
			bool is_resizable;
			bool is_fullscreen;
		};

		/**
			A struct to store the data required to initialise a graphics implementation.
		*/
		struct GraphicsSettings
		{
			EngineConfig::GraphicsImplementation implementation;

			bool enable_vr;
		};

		/**
			A struct to store the data required to initialise a physics implementation.
		*/
		struct PhysicsSettings
		{
			EngineConfig::PhysicsImplementation implementation;
		};

		/**
			A struct to store the data required to initialise a world implementation.
		*/
		struct WorldSettings
		{
			EngineConfig::WorldImplementation implementation;

			struct WorldFile
			{
				std::string world_filename;
				std::vector<std::string> asset_files;
			};

			std::map<int,WorldFile> world_files;
			std::vector<std::string> asset_file;
		};

		/**
			A struct to store the data required to initialise a scripting implementation.
		*/
		struct ScriptingSettings
		{
			EngineConfig::ScriptingImplementation implementation;
		};

		bool Load( const std::string& filename, EngineConfig::Config config );

		const LoggerSettings& GetLoggerSettings() const;
		const WindowSettings& GetWindowSettings() const;
		const GraphicsSettings& GetGraphicsSettings() const;
		const PhysicsSettings& GetPhysicsSettings() const;
		const WorldSettings& GetWorldSettings() const;
		const ScriptingSettings& GetScriptingSettings() const;

	private:

		bool CheckCompatibility( EngineConfig::Config config );
		
		LoggerSettings _logger_settings;
		WindowSettings _window_settings;
		GraphicsSettings _graphics_settings;
		PhysicsSettings _physics_settings;
		WorldSettings _world_settings;
		ScriptingSettings _scripting_settings;
};
}
}

#endif