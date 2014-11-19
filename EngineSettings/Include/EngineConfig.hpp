#pragma once

#ifndef _ENGINESETTINGS_ENGINECONFIG_HPP_
#define _ENGINESETTINGS_ENGINECONFIG_HPP_

#include <string>

namespace Fnd
{
namespace EngineSettings
{

/**
	A helper class to get compatible components for a configuration.
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
			An enum to define Window implementations compatible with a configuration.
		*/
		enum CompatibleWindows
		{
			Win32Window_compatible		= 1 << 0,
			XWindowsWindow_compatible	= 1 << 1
		};

		/**
			An enum to define Graphics implementations compatible with a configuration.
		*/
		enum CompatibleGraphics
		{
			DirectX11Graphics_compatible	= 1 << 0,
			OpenGLGraphics_compatible		= 1 << 1
		};

		/**
			An enum to define Physics implementations compatible with a configuration.
		*/
		enum CompatiblePhysics
		{
			BulletPhysics_compatible		= 1 << 0
		};

		/**
			An enum to define Scripting implementations compatible with a configuration.
		*/
		enum CompatibleScripting
		{
			MockScripting_compatible		= 1 << 0,
			LuaScripting_compatible			= 1 << 1
		};

		/**
			Get the config from a string.
			@param config_str The configuration as a string. This should be equal to a _****_config_str value.
			@return Returns the matching Config enum, or Invalid_config if there are no matching configs.
		*/
		static Config GetConfig( const std::string& config_str );

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
			Get the Scripting implementations compatible with a Config.
			@param config The defined configuration.
			@return Returns the Scripting implementations compatible with config.
		*/
		static int GetCompatibleScripting( Config config );

	private:

		static const std::string _windows_config_str;
		static const std::string _linux_config_str;
		static const std::string _mac_config_str;

		/**
			An offset into the _config_map. 
			Used to get the flags for the correct type.
		*/
		enum CompatibleTypeOffset
		{
			CompatibleWindows_offset	= 0,
			CompatibleGraphics_offset	= 1,
			CompatiblePhysics_offset	= 2,
			CompatibleScripting_offset	= 3,

			CompatibleType_count		= 4
		};

		/**
			A map to define the flags.
			Uses 'Config' and 'CompatibleTypeOffset' as offsets into the arrays.
		*/
		static const int _config_map[Config_count][CompatibleType_count];
};

}
}

#endif