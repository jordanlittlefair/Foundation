#include "../Include/EngineConfig.hpp"

using namespace Fnd::EngineSettings;

const std::string EngineConfig::_windows_config_str = "Windows";
const std::string EngineConfig::_linux_config_str = "Linux";
const std::string EngineConfig::_mac_config_str = "Mac";

const int EngineConfig::_config_map[Config_count][CompatibleType_count] =
{
	{	// Invalid
		0,
		0,
		0,
		0
	},
	{	// Windows
		Win32Window_compatible,
		DirectX11Graphics_compatible | OpenGLGraphics_compatible,
		BulletPhysics_compatible,
		MockScripting_compatible | LuaScripting_compatible
	},
	{	// Linux
		XWindowsWindow_compatible,
		OpenGLGraphics_compatible,
		BulletPhysics_compatible,
		MockScripting_compatible | LuaScripting_compatible
	},
	{	// Mac
		XWindowsWindow_compatible,
		OpenGLGraphics_compatible,
		BulletPhysics_compatible,
		MockScripting_compatible | LuaScripting_compatible
	}
};

EngineConfig::Config EngineConfig::GetConfig( const std::string& config_str )
{
	if ( config_str == _windows_config_str )
	{
		return Windows_config;
	}
	else if ( config_str == _linux_config_str )
	{
		return Linux_config;
	}
	else if ( config_str == _mac_config_str )
	{
		return Mac_config;
	}
	else
	{
		return Invalid_config;
	}
}

int EngineConfig::GetCompatibleWindows( EngineConfig::Config config )
{
	return _config_map[CompatibleWindows_offset][config];
}

int EngineConfig::GetCompatibleGraphics( EngineConfig::Config config )
{
	return _config_map[CompatibleGraphics_offset][config];
}

int EngineConfig::GetCompatiblePhysics( EngineConfig::Config config )
{
	return _config_map[CompatiblePhysics_offset][config];
}

int EngineConfig::GetCompatibleScripting( EngineConfig::Config config )
{
	return _config_map[CompatibleScripting_offset][config];
}