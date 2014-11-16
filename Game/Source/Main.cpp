#include "../Include/Game.hpp"
#include "../../GameComponentFactory/Include/GameComponentFactory.hpp"

#include "../../Logger/Include/Logger.hpp"

#include "../../Setup/Include/Setup.hpp"

#include "../../AssetManager/Include/AssetManager.hpp"
#include "../../AssetManager/Include/Model.hpp"
#include "../../ModelLoader/Include/ModelLoader.hpp"
#include "../../Utility/Include/MessageBox.hpp"

#include "../../LuaScripting/Include/LuaScripting.hpp"

#include "../../Configuration/Include/Configuration.hpp"
#include "../../Utility/Include/FileSystem.hpp"

#include <Windows.h>

using namespace Fnd::Logger;

int _stdcall
WinMain (	_In_ struct HINSTANCE__* hIinstance,
			_In_opt_ struct HINSTANCE__* hPrevInstance,
			_In_ char* lpszCmdLine,
			_In_ int nCmdShow )
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	auto cmds = Fnd::Utility::FileSystem::ParseCommandLine( lpszCmdLine );
	
	if ( cmds.size() < 1 )
	{
		Fnd::Utility::BlockingMessageBox( "Failed to start", "Requires Application directory as first argument." );

		return 1;
	}

	std::string application_directory = Fnd::Utility::FileSystem::CanonicaliseDirectory(cmds[0]);

	/*
		Load the setup file.
	*/
	const std::string setup_dir = application_directory;
	const std::string setup_file = "ApplicationSettings.xml";
	Fnd::Setup::Setup setup;	
	if ( !setup.LoadSetupFile( setup_dir, setup_file ) )
	{
		Fnd::Utility::BlockingMessageBox( "Error", "Failed to load and parse \"" + setup_dir + setup_file + "\"." );
		return 2;
	}

	const std::string config_file = "EngineSettings.xml";
	Fnd::Configuration::Configuration config;
	if ( !config.LoadConfiguration(config_file) )
	{
		Fnd::Utility::BlockingMessageBox( "Error", "Failed to load and parse \"" + config_file + "\"." );
		return 2;
	}

	/*
		Create a logger and give it info about the game components.
	*/
	Logger::GetInstance().Initialise( setup.GetLoggerSetupData() );
	Logger::GetInstance().SetWindowSetupData( setup.GetWindowSetupData() );
	Logger::GetInstance().SetGraphicsSetupData( setup.GetGraphicsSetupData() );
	Logger::GetInstance().SetWorldSetupData( setup.GetWorldSetupData() );
	// TODO: log physics and scripting data

	/*
		Create the game components.
	*/
	Fnd::GameComponentFactory::GameComponentFactory component_factory;

	Fnd::GameComponentInterfaces::IWindow* window = component_factory.GetWindowComponent( setup.GetWindowSetupData(), config.GetConfigNonConst().window_config );
	Fnd::GameComponentInterfaces::IGraphics* graphics = component_factory.GetGraphicsComponent( setup.GetGraphicsSetupData(), config.GetConfigNonConst().graphics_config );
	Fnd::GameComponentInterfaces::IPhysics* physics = component_factory.GetPhysicsComponent( setup.GetPhysicsSetupData() );
	Fnd::GameComponentInterfaces::IWorld* world = component_factory.GetWorldComponent( setup.GetWorldSetupData() );
	Fnd::Scripting::ScriptManager* scripting = component_factory.GetScriptManager( setup.GetScriptingSetupData() );

	if ( !( window && graphics && physics && world && scripting ) )
	{
		Fnd::Utility::BlockingMessageBox( "Error", "Failed to create game components." );
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

	return 0;
}
