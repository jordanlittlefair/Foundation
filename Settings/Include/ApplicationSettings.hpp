#pragma once

#ifndef _SETTINGS_APPLICATIONSETTINGS_HPP_
#define _SETTINGS_APPLICATIONSETTINGS_HPP_

#include "GameComponentSettings.hpp"

namespace Fnd
{
namespace Settings
{

class ApplicationSettings
{
	public:
		
		bool LoadSetupFile( const std::string& directory, const std::string& filename, EngineConfig::Config config );

		const LoggerSettings& GetLoggerSettings() const;
		const WindowSettings& GetWindowSettings() const;
		const GraphicsSettings& GetGraphicsSettings() const;
		const PhysicsSettings& GetPhysicsSettings() const;
		const WorldSettings& GetWorldSettings() const;
		const ScriptingSettings& GetScriptingSettings() const;

	private:

		bool CheckCompatibility();
		
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