#pragma once

#ifndef _ENGINESETTINGS_ENGINECONFIG_HPP_
#define _ENGINESETTINGS_ENGINECONFIG_HPP_

#include <string>

namespace Fnd
{
namespace Settings
{

/**
	A helper class to get compatible component implementations for a configuration.
*/
class EngineConfig
{
	public:

		/**
			An enum to define the config.
			Used internally to get the flags for the requested configuration.
		*/
		enum Config
		{
			Invalid_config	= 0,
			Windows_config	= 1,
			Linux_config	= 2,
			Mac_config		= 3,

			Config_count	= 4
		};

		/**
			An enum to define Logger implementations compatible with a configuration.
		*/
		enum LoggerImplementation
		{
			InvalidLogger_implementation	= 0,
			ConsoleLogger_implementation	= 1 << 0,
			NetworkLogger_implementation	= 1 << 1
		};

		/**
			An enum to define Window implementations compatible with a configuration.
		*/
		enum WindowImplementation
		{
			InvalidWindow_implementation	= 0,
			Win32Window_implementation		= 1 << 0,
			XWindowsWindow_implementation	= 1 << 1
		};

		/**
			An enum to define Graphics implementations compatible with a configuration.
		*/
		enum GraphicsImplementation
		{
			InvalidGraphics_implementation		= 0,
			DirectX11Graphics_implementation	= 1 << 0,
			OpenGLGraphics_implementation		= 1 << 1
		};

		/**
			An enum to define Physics implementations compatible with a configuration.
		*/
		enum PhysicsImplementation
		{
			InvalidPhysics_implementation	= 0,
			BulletPhysics_implementation	= 1 << 0
		};

		/**
			An enum to define World implementations compatible with a configuration.
		*/
		enum WorldImplementation
		{
			InvalidWorld_implementation	= 0,
			LoadedWorld_implementation	= 1 << 0
		};

		/**
			An enum to define Scripting implementations compatible with a configuration.
		*/
		enum ScriptingImplementation
		{
			InvalidScripting_implementation	= 0,
			MockScripting_implementation	= 1 << 0,
			LuaScripting_implementation		= 1 << 1
		};

		/**
			Get the config from a string.
			@param config_str The configuration as a string. This should be equal to a _****_config_str value.
			@return Returns the matching Config enum, or Invalid_config if there are no matching configs.
		*/
		static Config GetConfig( const std::string& config_str );

		/**
			Get the Logger implementations compatible with a Config.
			@param config The defined configuration.
			@return Returns the Logger implementations compatible with config.
		*/
		static int GetCompatibleLoggers( Config config );

		/**
			Get the Window implementations compatible with a Config.
			@param config The defined configuration.
			@return Returns the Window implementations compatible with config.
		*/
		static int GetCompatibleWindows( Config config );

		/**
			Get the Graphics implementations compatible with a Config.
			@param config The defined configuration.
			@return Returns the Graphics implementations compatible with config.
		*/
		static int GetCompatibleGraphics( Config config );

		/**
			Get the Physics implementations compatible with a Config.
			@param config The defined configuration.
			@return Returns the Physics implementations compatible with config.
		*/
		static int GetCompatiblePhysics( Config config );

		/**
			Get the World implementations compatible with a Config.
			@param config The defined configuration.
			@return Returns the World implementations compatible with config.
		*/
		static int GetCompatibleWorlds( Config config );

		/**
			Get the Scripting implementations compatible with a Config.
			@param config The defined configuration.
			@return Returns the Scripting implementations compatible with config.
		*/
		static int GetCompatibleScripting( Config config );

		static LoggerImplementation GetLoggerImplementation( const std::string& str );
		static WindowImplementation GetWindowImplementation( const std::string& str );
		static GraphicsImplementation GetGraphicsImplementation( const std::string& str );
		static PhysicsImplementation GetPhysicsImplementation( const std::string& str );
		static WorldImplementation GetWorldImplementation( const std::string& str );
		static ScriptingImplementation GetScriptingImplementation( const std::string& str );

		static std::string GetLoggerImplementationString( LoggerImplementation impl );
		static std::string GetWindowImplementationString( WindowImplementation impl );
		static std::string GetGraphicsImplementationString( GraphicsImplementation impl );
		static std::string GetPhysicsImplementationString( PhysicsImplementation impl );
		static std::string GetWorldImplementationString( WorldImplementation impl );
		static std::string GetScriptingImplementationString( ScriptingImplementation impl );

	private:
		
		/**
			An offset into the _config_map. 
			Used to get the flags for the correct type.
		*/
		enum ImplementationTypeOffset
		{
			LoggerImplementations_offset	= 0,
			WindowImplementations_offset	= 1,
			GraphicsImplementations_offset	= 2,
			PhysicsImplementations_offset	= 3,
			WorldImplementations_offset		= 4,
			ScriptingImplementations_offset	= 5,

			ImplementationType_count		= 6
		};

		/**
			A map to define the flags.
			Uses 'Config' and 'CompatibleTypeOffset' as offsets into the arrays.
		*/
		static const int _compatibility_map[Config_count][ImplementationType_count];
};

}
}

#endif