#include "../Include/ApplicationSettings.hpp"

#include "../../Utility/Include/XmlManager.hpp"
#include "../../Utility/Include/MessageBox.hpp"

using namespace Fnd::Settings;
using namespace Fnd::Utility;

namespace ApplicationSettingsHelper
{

LoggerSettings ReadLoggerSettings( const std::string& directory, rapidxml::xml_node<char>* logger_node, EngineConfig::Config config )
{
	LoggerSettings ret;
	ret.implementations = 0;
	ret.server = "";
	ret.port = "";

	{
		auto loggers_iter = logger_node->first_node();

		while ( loggers_iter )
		{
			EngineConfig::LoggerImplementation impl = EngineConfig::GetLoggerImplementation( loggers_iter->name() );
			
			if ( impl | EngineConfig::GetCompatibleLoggers( config ) )
			{
				ret.implementations |= impl;
			}

			loggers_iter = loggers_iter->next_sibling();
		}
	}
	{
		auto attrib = logger_node->first_attribute("server");
		if ( attrib )
		{
			ret.server = attrib->value();
		}
	}
	{
		auto attrib = logger_node->first_attribute("port");
		if ( attrib )
		{
			ret.port = attrib->value();
		}
	}

	return ret;
} 

WindowSettings ReadWindowSettings( const std::string& directory, rapidxml::xml_node<char>* window_node, EngineConfig::Config config )
{
	WindowSettings ret;
	ret.implementation = EngineConfig::InvalidWindow_implementation;
	ret.window_title = "Unknown";
	ret.initial_width = 0;
	ret.initial_height = 0;
	ret.is_resizable = false;
	ret.is_fullscreen = false;

	{
		auto attrib = window_node->first_attribute("window");
		if ( attrib )
		{
			ret.implementation = (EngineConfig::WindowImplementation)( EngineConfig::GetWindowImplementation( attrib->value() ) | EngineConfig::GetCompatibleWindows( config ) );
		}
	}
	{
		auto attrib = window_node->first_attribute("window_title");
		if ( attrib )
		{
			ret.window_title = attrib->value();
		}
	}
	{
		auto attrib = window_node->first_attribute("initial_width");
		if ( attrib )
		{
			ret.initial_width = atol(attrib->value());
		}
	}
	{
		auto attrib = window_node->first_attribute("initial_height");
		if ( attrib )
		{
			ret.initial_height = atol(attrib->value());
		}
	}
	{
		auto attrib = window_node->first_attribute("is_resizable");
		if ( attrib )
		{
			ret.is_resizable = std::string(attrib->value()) == "true";
		}
	}
	{
		auto attrib = window_node->first_attribute("is_fullscreen");
		if ( attrib )
		{
			ret.is_fullscreen = std::string(attrib->value()) == "true";
		}
	}

	return ret;
}

GraphicsSettings ReadGraphicsSetupData( const std::string& directory, rapidxml::xml_node<char>* graphics_node, EngineConfig::Config config )
{
	GraphicsSettings ret;

	{
		auto attrib = graphics_node->first_attribute("graphics");
		if ( attrib )
		{
			ret.implementation = (EngineConfig::GraphicsImplementation)( EngineConfig::GetGraphicsImplementation( attrib->value() ) | EngineConfig::GetCompatibleGraphics( config ) );
		}
	}

	{
		auto attrib = graphics_node->first_attribute("enable_vr");
		if ( attrib )
		{
			ret.enable_vr = std::string(attrib->value()) == "true";
		}
	}

	return ret;
}

PhysicsSettings ReadPhysicsSetupData( const std::string& directory, rapidxml::xml_node<char>* physics_node, EngineConfig::Config config )
{
	PhysicsSettings ret;

	{
		auto attrib = physics_node->first_attribute("physics");
		if ( attrib )
		{
			ret.implementation = (EngineConfig::PhysicsImplementation)( EngineConfig::GetPhysicsImplementation( attrib->value() ) | EngineConfig::GetCompatiblePhysics( config ) );
		}
	}

	return ret;
}

WorldSettings ReadWorldSetupData( const std::string& directory, rapidxml::xml_node<char>* world_node, EngineConfig::Config config )
{
	WorldSettings ret;

	{
		auto attrib = world_node->first_attribute("world");
		if ( attrib )
		{
			ret.implementation = (EngineConfig::WorldImplementation)( EngineConfig::GetWindowImplementation( attrib->value() ) | EngineConfig::GetCompatibleWorlds( config ) );
		}
	}

	auto world_files_iter = world_node->first_node();

	while ( world_files_iter )
	{
		auto index_attrib = world_files_iter->first_attribute("index");
		auto file_attrib = world_files_iter->first_attribute("filename");

		if ( index_attrib && file_attrib )
		{
			WorldSettings::WorldFile world_file;
			world_file.world_filename = directory + file_attrib->value();

			auto assets = world_files_iter->first_node("Assets");

			if ( assets )
			{
				auto asset_files_iter = assets->first_node("AssetFile");

				while ( asset_files_iter )
				{
					auto asset_filename_attrib = asset_files_iter->first_attribute("filename");

					if( asset_filename_attrib )
					{
						world_file.asset_files.push_back( directory + asset_filename_attrib->value() );
					}

					asset_files_iter = asset_files_iter->next_sibling("AssetFile");
				}
			}

			ret.world_files[atoi(index_attrib->value())] = world_file;
		}

		world_files_iter = world_files_iter->next_sibling();
	}

	return ret;
}

ScriptingSettings ReadScriptingSetupData( const std::string& directory, rapidxml::xml_node<char>* scripting_node, EngineConfig::Config config )
{
	ScriptingSettings ret;
	{
		auto attrib = scripting_node->first_attribute("scripting");
		if ( attrib )
		{
			ret.implementation = (EngineConfig::ScriptingImplementation)( EngineConfig::GetScriptingImplementation( attrib->value() ) | EngineConfig::GetCompatibleScripting( config ) );
		}
	}

	return ret;
}

}

bool ApplicationSettings::LoadSetupFile( const std::string& directory, const std::string& filename, EngineConfig::Config config )
{
	bool ret = true;

	std::string setup_file = directory + filename;

	do
	{
		XmlManager setup_xml;
		if ( !setup_xml.CreateFromFile( setup_file ) )
		{
			ret = false;
			break;
		}

		auto root_node = setup_xml.Xml().first_node("GameSetup");

		if ( !root_node )
		{
			ret = false;
			break;
		}

		{
			auto logger_node = root_node->first_node("Logger");

			if ( logger_node )
			{
				_logger_settings = ApplicationSettingsHelper::ReadLoggerSettings( directory, logger_node, config );
			}
			else
			{
				ret = false;
				break;
			}
		}

		{
			auto window_node = root_node->first_node("Window");

			if ( window_node )
			{
				_window_settings = ApplicationSettingsHelper::ReadWindowSettings( directory, window_node, config );
			}
			else
			{
				ret = false;
				break;
			}
		}

		{
			auto graphics_node = root_node->first_node("Graphics");

			if ( graphics_node )
			{
				_graphics_settings = ApplicationSettingsHelper::ReadGraphicsSetupData( directory, graphics_node, config );
			}
			else
			{
				ret = false;
				break;
			}
		}

		{
			auto physics_node = root_node->first_node("Physics");

			if ( physics_node )
			{
				_physics_settings = ApplicationSettingsHelper::ReadPhysicsSetupData( directory, physics_node, config );
			}
			else
			{
				ret = false;
				break;
			}
		}

		{
			auto world_node = root_node->first_node("World");

			if ( world_node )
			{
				_world_settings = ApplicationSettingsHelper::ReadWorldSetupData( directory, world_node, config );
			}
			else
			{
				ret = false;
				break;
			}
		}

		{
			auto scripting_node = root_node->first_node("Scripting");

			if ( scripting_node )
			{
				_scripting_settings = ApplicationSettingsHelper::ReadScriptingSetupData( directory, scripting_node, config );
			}
			else
			{
				ret = false;
				break;
			}
		}
	}
	while(false);

	if ( !ret )
	{
		BlockingMessageBox( "Setup Error", "Failed to read 'Setup.xml'.\nApplication will exit." );
	}

	return ret && CheckCompatibility();
}

const LoggerSettings& ApplicationSettings::GetLoggerSettings() const
{
	return _logger_settings;
}

const WindowSettings& ApplicationSettings::GetWindowSettings() const
{
	return _window_settings;
}

const GraphicsSettings& ApplicationSettings::GetGraphicsSettings() const
{
	return _graphics_settings;
}

const PhysicsSettings& ApplicationSettings::GetPhysicsSettings() const
{
	return _physics_settings;
}

const WorldSettings& ApplicationSettings::GetWorldSettings() const
{
	return _world_settings;
}

const ScriptingSettings& ApplicationSettings::GetScriptingSettings() const
{
	return _scripting_settings;
}

bool ApplicationSettings::CheckCompatibility()
{

	return false;
}