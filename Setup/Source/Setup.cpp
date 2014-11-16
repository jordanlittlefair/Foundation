#include "../Include/Setup.hpp"

#include "../../Utility/Include/XmlManager.hpp"
#include "../../Utility/Include/MessageBox.hpp"

using namespace Fnd::Setup;
using namespace Fnd::Utility;

Setup::Setup()
{
}

bool Setup::LoadSetupFile( const std::string& directory, const std::string& filename )
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
				_logger_data = CreateLoggerSetupData( directory, logger_node );
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
				_window_data = CreateWindowSetupData( directory, window_node );
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
				_graphics_data = CreateGraphicsSetupData( directory, graphics_node );
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
				_physics_data = CreatePhysicsSetupData( directory, physics_node );
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
				_world_data = CreateWorldSetupData( directory, world_node );
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
				_scripting_data = CreateScriptingSetupData( directory, scripting_node );
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

	return ret;
}

const LoggerSetupData& Setup::GetLoggerSetupData() const
{
	return _logger_data;
}

const WindowSetupData& Setup::GetWindowSetupData() const
{
	return _window_data;
}

const GraphicsSetupData& Setup::GetGraphicsSetupData() const
{
	return _graphics_data;
}

const PhysicsSetupData& Setup::GetPhysicsSetupData() const
{
	return _physics_data;
}

const WorldSetupData& Setup::GetWorldSetupData() const
{
	return _world_data;
}

const ScriptingSetupData& Setup::GetScriptingSetupData() const
{
	return _scripting_data;
}