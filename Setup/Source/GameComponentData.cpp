#include "../Include/GameComponentData.hpp"

#include "../../Utility/Include/String.hpp"

#include "../../Utility/Include/rapidxml/rapidxml.hpp"

#include <iostream>

Fnd::Setup::LoggerSetupData Fnd::Setup::CreateLoggerSetupData( const std::string& directory, rapidxml::xml_node<char>* logger_node )
{
	LoggerSetupData ret;
	ret.server = "";
	ret.port = "";

	{
		auto loggers_iter = logger_node->first_node();

		while ( loggers_iter )
		{
			ret.loggers.push_back( loggers_iter->name() );

			loggers_iter = loggers_iter->next_sibling();
		}
	}
	{
		auto attrib = logger_node->first_attribute("server");
		if ( attrib )
		{
			ret.server = attrib->value();
		}
		else
		{
			std::cout << "Cannot find \"server\" attribute.\n";
		}
	}
	{
		auto attrib = logger_node->first_attribute("port");
		if ( attrib )
		{
			ret.port = attrib->value();
		}
		else
		{
			std::cout << "Cannot find \"port\" attribute.\n";
		}
	}

	return ret;
}

Fnd::Setup::WindowSetupData Fnd::Setup::CreateWindowSetupData( const std::string& directory, rapidxml::xml_node<char>* window_node )
{
	WindowSetupData ret;
	ret.window_title = "Unknown";
	ret.initial_width = 0;
	ret.initial_height = 0;
	ret.is_resizable = false;
	ret.is_fullscreen = false;

	{
		auto attrib = window_node->first_attribute("window");
		if ( attrib )
		{
			ret.window = attrib->value();
		}
		else
		{
			std::cout << "Cannot find \"window\" attribute.\n";
		}
	}
	{
		auto attrib = window_node->first_attribute("window_title");
		if ( attrib )
		{
			ret.window_title = attrib->value();
		}
		else
		{
			std::cout << "Cannot find \"window_title\" attribute.\n";
		}
	}
	{
		auto attrib = window_node->first_attribute("initial_width");
		if ( attrib )
		{
			ret.initial_width = atol(attrib->value());
		}
		else
		{
			std::cout << "Cannot find \"initial_width\" attribute.\n";
		}
	}
	{
		auto attrib = window_node->first_attribute("initial_height");
		if ( attrib )
		{
			ret.initial_height = atol(attrib->value());
		}
		else
		{
			std::cout << "Cannot find \"initial_height\" attribute.\n";
		}
	}
	{
		auto attrib = window_node->first_attribute("is_resizable");
		if ( attrib )
		{
			ret.is_resizable = std::string(attrib->value()) == "true";
		}
		else
		{
			std::cout << "Cannot find \"is_resizable\" attribute.\n";
		}
	}
	{
		auto attrib = window_node->first_attribute("is_fullscreen");
		if ( attrib )
		{
			ret.is_fullscreen = std::string(attrib->value()) == "true";
		}
		else
		{
			std::cout << "Cannot find \"is_fullscreen\" attribute.\n";
		}
	}

	return ret;
}

Fnd::Setup::GraphicsSetupData Fnd::Setup::CreateGraphicsSetupData( const std::string& directory, rapidxml::xml_node<char>* graphics_node )
{
	GraphicsSetupData ret;

	{
		auto attrib = graphics_node->first_attribute("graphics");
		if ( attrib )
		{
			ret.graphics = attrib->value();
		}
		else
		{
			std::cout << "Cannot find \"graphics\" attribute.\n";
		}
	}

	{
		auto attrib = graphics_node->first_attribute("enable_vr");
		if ( attrib )
		{
			ret.enable_vr = std::string(attrib->value()) == "true";
		}
		else
		{
			std::cout << "Cannot find \"enable_vr\" attribute.\n";
		}
	}

	return ret;
}

Fnd::Setup::PhysicsSetupData Fnd::Setup::CreatePhysicsSetupData( const std::string& directory, rapidxml::xml_node<char>* physics_node )
{
	PhysicsSetupData ret;

	{
		auto attrib = physics_node->first_attribute("physics");
		if ( attrib )
		{
			ret.physics = attrib->value();
		}
		else
		{
			std::cout << "Cannot find \"physics\" attribute.\n";
		}
	}

	return ret;
}

Fnd::Setup::WorldSetupData Fnd::Setup::CreateWorldSetupData( const std::string& directory, rapidxml::xml_node<char>* world_node )
{
	WorldSetupData ret;

	{
		auto attrib = world_node->first_attribute("world");
		if ( attrib )
		{
			ret.world = attrib->value();
		}
		else
		{
			std::cout << "Cannot find \"world\" attribute.\n";
		}
	}

	auto world_files_iter = world_node->first_node();

	while ( world_files_iter )
	{
		auto index_attrib = world_files_iter->first_attribute("index");
		auto file_attrib = world_files_iter->first_attribute("filename");

		if ( index_attrib && file_attrib )
		{
			WorldSetupData::WorldFile world_file;
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

Fnd::Setup::ScriptingSetupData Fnd::Setup::CreateScriptingSetupData( const std::string& directory, rapidxml::xml_node<char>* scripting_node )
{
	ScriptingSetupData ret;
	{
		auto attrib = scripting_node->first_attribute("scripting");
		if ( attrib )
		{
			ret.scripting = attrib->value();
		}
		else
		{
			std::cout << "Cannot find \"scripting\" attribute.\n";
		}
	}

	return ret;
}