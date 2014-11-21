#include "../Include/EngineConfig.hpp"

using namespace Fnd::Settings;

const int EngineConfig::_compatibility_map[Config_count][ImplementationType_count] =
{
	{	// Invalid
		0,
		0,
		0,
		0,
		0,
		0
	},
	{	// Windows
		ConsoleLogger_implementation | NetworkLogger_implementation,
		Win32Window_implementation,
		DirectX11Graphics_implementation | OpenGLGraphics_implementation,
		BulletPhysics_implementation,
		LoadedWorld_implementation,
		MockScripting_implementation
	},
	{	// Linux
		ConsoleLogger_implementation | NetworkLogger_implementation,
		XWindowsWindow_implementation,
		OpenGLGraphics_implementation,
		BulletPhysics_implementation,
		LoadedWorld_implementation,
		MockScripting_implementation
	},
	{	// Mac
		ConsoleLogger_implementation | NetworkLogger_implementation,
		XWindowsWindow_implementation,
		OpenGLGraphics_implementation,
		BulletPhysics_implementation,
		LoadedWorld_implementation,
		MockScripting_implementation
	}
};

EngineConfig::Config EngineConfig::GetConfig( const std::string& config_str )
{
	if ( config_str == "Windows" )
	{
		return Windows_config;
	}
	else if ( config_str == "Linux" )
	{
		return Linux_config;
	}
	else if ( config_str == "Mac" )
	{
		return Mac_config;
	}
	else
	{
		return Invalid_config;
	}
}

int EngineConfig::GetCompatibleLoggers( EngineConfig::Config config )
{
	return _compatibility_map[config][LoggerImplementations_offset];
}

int EngineConfig::GetCompatibleWindows( EngineConfig::Config config )
{
	return _compatibility_map[config][LoggerImplementations_offset];
}

int EngineConfig::GetCompatibleGraphics( EngineConfig::Config config )
{
	return _compatibility_map[config][LoggerImplementations_offset];
}

int EngineConfig::GetCompatiblePhysics( EngineConfig::Config config )
{
	return _compatibility_map[config][LoggerImplementations_offset];
}

int EngineConfig::GetCompatibleWorlds( EngineConfig::Config config )
{
	return _compatibility_map[config][LoggerImplementations_offset];
}

int EngineConfig::GetCompatibleScripting( EngineConfig::Config config )
{
	return _compatibility_map[config][LoggerImplementations_offset];
}

EngineConfig::LoggerImplementation EngineConfig::GetLoggerImplementation( const std::string& str )
{
	if ( str == "NetworkLogger" )
		return NetworkLogger_implementation;
	else if ( str == "ConsoleLogger" )
		return ConsoleLogger_implementation;
	else
		return InvalidLogger_implementation;
}

EngineConfig::WindowImplementation EngineConfig::GetWindowImplementation( const std::string& str )
{
	if ( str == "Win32Window" )
		return Win32Window_implementation;
	else if ( str == "XWindowsWindow" )
		return XWindowsWindow_implementation;
	else
		return InvalidWindow_implementation;
}

EngineConfig::GraphicsImplementation EngineConfig::GetGraphicsImplementation( const std::string& str )
{
	if ( str == "DirectX11Graphics" )
		return DirectX11Graphics_implementation;
	else if ( str == "OpenGLGraphics" )
		return OpenGLGraphics_implementation;
	else
		return InvalidGraphics_implementation;
}

EngineConfig::PhysicsImplementation EngineConfig::GetPhysicsImplementation( const std::string& str )
{
	if ( str == "BulletPhysics" )
		return BulletPhysics_implementation;
	else
		return InvalidPhysics_implementation;
}

EngineConfig::WorldImplementation EngineConfig::GetWorldImplementation( const std::string& str )
{
	if ( str == "LoadedWorld" )
		return LoadedWorld_implementation;
	else
		return InvalidWorld_implementation;
}

EngineConfig::ScriptingImplementation EngineConfig::GetScriptingImplementation( const std::string& str )
{
	if ( str == "MockScripting" )
		return MockScripting_implementation;
	else if ( str == "LuaScripting" )
		return LuaScripting_implementation;
	else
		return InvalidScripting_implementation;
}

std::string EngineConfig::GetLoggerImplementationString( EngineConfig::LoggerImplementation impl )
{
	switch (impl)
	{
	case Fnd::Settings::EngineConfig::ConsoleLogger_implementation:
		return "ConsoleLogger";
	case Fnd::Settings::EngineConfig::NetworkLogger_implementation:
		return "NetworkLogger";
	default:
		return "";
	}
}

std::string EngineConfig::GetWindowImplementationString( EngineConfig::WindowImplementation impl )
{
	switch (impl)
	{
	case Fnd::Settings::EngineConfig::Win32Window_implementation:
		return "Win32Window";
	case Fnd::Settings::EngineConfig::XWindowsWindow_implementation:
		return "XWindowsWindow";
	default:
		return "";
	}
}

std::string EngineConfig::GetGraphicsImplementationString( EngineConfig::GraphicsImplementation impl )
{
	switch (impl)
	{
	case Fnd::Settings::EngineConfig::DirectX11Graphics_implementation:
		return "DirectX11Graphics";
	case Fnd::Settings::EngineConfig::OpenGLGraphics_implementation:
		return "OpenGLGraphics";
	default:
		return "";
	}
}

std::string EngineConfig::GetPhysicsImplementationString( EngineConfig::PhysicsImplementation impl )
{
	switch (impl)
	{
	case Fnd::Settings::EngineConfig::BulletPhysics_implementation:
		return "BulletPhysics";
	default:
		return "";
	}
}

std::string EngineConfig::GetWorldImplementationString( EngineConfig::WorldImplementation impl )
{
	switch (impl)
	{
	case Fnd::Settings::EngineConfig::LoadedWorld_implementation:
		return "LoadedWorld";
	default:
		return "";
	}
}

std::string EngineConfig::GetScriptingImplementationString( EngineConfig::ScriptingImplementation impl )
{
	switch (impl)
	{
	case Fnd::Settings::EngineConfig::MockScripting_implementation:
		return "MockScripting";
	case Fnd::Settings::EngineConfig::LuaScripting_implementation:
		return "LuaScripting";
	default:
		return "";
	}
}
