#include "../Include/Game.hpp"
#include "../../GameComponentFactory/Include/GameComponentFactory.hpp"

#include "../../Logger/Include/Logger.hpp"

#include "../../Settings/Include/GameComponentSettings.hpp"

#include "../../AssetManager/Include/AssetManager.hpp"
#include "../../AssetManager/Include/Model.hpp"
#include "../../ModelLoader/Include/ModelLoader.hpp"
#include "../../Utility/Include/MessageBox.hpp"

#include "../../LuaScripting/Include/LuaScripting.hpp"

#include "../../Settings/Include/EngineSettings.hpp"
#include "../../Utility/Include/FileSystem.hpp"

#include "../../Settings/Include/ApplicationSettings.hpp"

#include <Windows.h>

using namespace Fnd::Logger;
using namespace Fnd::Settings;

int _stdcall
WinMain (	_In_ struct HINSTANCE__* hIinstance,
			_In_opt_ struct HINSTANCE__* hPrevInstance,
			_In_ char* lpszCmdLine,
			_In_ int nCmdShow )
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	auto cmds = Fnd::Utility::FileSystem::ParseCommandLine( lpszCmdLine );
	
	if ( cmds.size() < 2 )
	{
		Fnd::Utility::BlockingMessageBox( "Failed to start", "Game.exe [ApplicationDirectory] [ConfigStr]" );

		return 1;
	}

	std::string application_directory = Fnd::Utility::FileSystem::CanonicaliseDirectory(cmds[0]);
	std::string config_str = cmds[1];

	const std::string engine_settings_filename = Fnd::Utility::FileSystem::CanonicaliseFile( Fnd::Utility::FileSystem::GetWorkingDirectory() + "/EngineSettings.xml" );
	const std::string application_settings_filename = Fnd::Utility::FileSystem::CanonicaliseFile( application_directory + "/ApplicationSettings.xml" );


	ApplicationSettings appsettings;
	std::string a;
	std::string b;
	Fnd::Utility::FileSystem::GetPathAndName( application_settings_filename, a, b );
	if ( !appsettings.LoadSetupFile( a, b, EngineConfig::GetConfig(config_str) ) )
	{
		Fnd::Utility::BlockingMessageBox( "Error", "Failed to load and parse \"" + application_settings_filename + "\"." );
		return 2;
	}
	/*
		Load ApplicationSettings.
		Get config enum and check flags using EngineConfig. (put an IsValid method in ApplicationSettings?)
		Load EngineSettings- using ApplicationSettings->Implementations to load the correct implementation.
	*/

	const std::string config_file = "EngineSettings.xml";
	Fnd::Settings::EngineSettings config;
	if ( !config.LoadConfiguration(config_file) )
	{
		Fnd::Utility::BlockingMessageBox( "Error", "Failed to load and parse \"" + config_file + "\"." );
		return 2;
	}

	/*
		Create a logger and give it info about the game components.
	*/
	Logger::GetInstance().Initialise( appsettings.GetLoggerSettings() );
	Logger::GetInstance().SetWindowSetupData( appsettings.GetWindowSettings() );
	Logger::GetInstance().SetGraphicsSetupData( appsettings.GetGraphicsSettings() );
	Logger::GetInstance().SetWorldSetupData( appsettings.GetWorldSettings() );
	// TODO: log physics and scripting data

	/*
		Create the game components.
	*/
	Fnd::GameComponentFactory::GameComponentFactory component_factory;

	Fnd::GameComponentInterfaces::IWindow* window = component_factory.GetWindowComponent( appsettings.GetWindowSettings(), config.GetConfigNonConst().window_config );
	Fnd::GameComponentInterfaces::IGraphics* graphics = component_factory.GetGraphicsComponent( appsettings.GetGraphicsSettings(), config.GetConfigNonConst().graphics_config );
	Fnd::GameComponentInterfaces::IPhysics* physics = component_factory.GetPhysicsComponent( appsettings.GetPhysicsSettings() );
	Fnd::GameComponentInterfaces::IWorld* world = component_factory.GetWorldComponent( appsettings.GetWorldSettings() );
	Fnd::Scripting::ScriptManager* scripting = component_factory.GetScriptManager( appsettings.GetScriptingSettings() );

	if ( !( window && graphics && physics && world && scripting ) )
	{
		Fnd::Utility::BlockingMessageBox( "Error", "Failed to create game components." );
		/*
			Release the game components.
		*/
		component_factory.Release(world);
		component_factory.Release(physics);
		component_factory.Release(graphics);
		component_factory.Release(window);
		component_factory.Release(scripting);
		return 2;
	}

	/*
		Create the Game with the game components.
	*/
	Fnd::Game::Game game( config.GetConfig() );
	game.SetWindow( window );
	game.SetGraphics( graphics );
	game.SetPhysics( physics );
	game.SetWorld( world );
	game.SetScriptManager( scripting );

	if ( !game.Initialise() )
	{
		return 2;
	}

	/*
		Enter the main Game loop.
	*/
	game.Play();

	/*
		Release the game components.
	*/
	component_factory.Release(world);
	component_factory.Release(physics);
	component_factory.Release(graphics);
	component_factory.Release(window);
	component_factory.Release(scripting);

	Logger::GetInstance().Shutdown();

	return 0;
}
