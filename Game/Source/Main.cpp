#include "../Include/Game.hpp"
#include "../../GameComponentFactory/Include/GameComponentFactory.hpp"

#include "../../Logger/Include/Logger.hpp"

#include "../../Settings/Include/ApplicationSettings.hpp"

#include "../../AssetManager/Include/AssetManager.hpp"
#include "../../AssetManager/Include/Model.hpp"
#include "../../ModelLoader/Include/ModelLoader.hpp"
#include "../../Utility/Include/MessageBox.hpp"

#include "../../LuaScripting/Include/LuaScripting.hpp"

#include "../../Settings/Include/EngineSettings.hpp"
#include "../../Utility/Include/FileSystem.hpp"

#include "../../Settings/Include/ApplicationSettings.hpp"

using namespace Fnd::Logger;
using namespace Fnd::Settings;

#ifdef _WIN32
int _stdcall
WinMain (	_In_ struct HINSTANCE__* hIinstance,
			_In_opt_ struct HINSTANCE__* hPrevInstance,
			_In_ char* lpszCmdLine,
			_In_ int nCmdShow )
#else
int main( int argc, char* argv[] )
#endif
{

#ifdef _WIN32
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

#ifdef _WIN32
	auto cmds = Fnd::Utility::FileSystem::ParseCommandLine( lpszCmdLine );
#else
    std::vector<std::string> cmds;
    for ( int i = 0; i < argc; ++i )
    {
        cmds.push_back( argv[i] );
    }
#endif
	
	if ( cmds.size() < 2 )
	{
		Fnd::Utility::BlockingMessageBox( "Failed to start", "Game.exe [ApplicationDirectory] [ConfigStr]" );

		return 1;
	}

	std::string application_directory = Fnd::Utility::FileSystem::CanonicaliseDirectory(cmds[0]);
	std::string config_str = cmds[1];

	const std::string engine_settings_filename = Fnd::Utility::FileSystem::CanonicaliseFile( Fnd::Utility::FileSystem::GetWorkingDirectory() + "/EngineSettings.xml" );
	const std::string application_settings_filename = Fnd::Utility::FileSystem::CanonicaliseFile( application_directory + "/ApplicationSettings.xml" );

	ApplicationSettings application_settings;
	if ( !application_settings.Load( application_settings_filename, EngineConfig::GetConfig(config_str) ) )
	{
		Fnd::Utility::BlockingMessageBox( "Error", "Failed to load and parse \"" + application_settings_filename + "\"." );
		return 2;
	}

	Fnd::Settings::EngineSettings engine_settings;
	if ( !engine_settings.Load( engine_settings_filename, application_settings ) )
	{
		Fnd::Utility::BlockingMessageBox( "Error", "Failed to load and parse \"" + engine_settings_filename + "\"." );
		return 2;
	}

	/*
		Create a logger and give it info about the game components.
	*/
	Logger::GetInstance().Initialise( application_settings.GetLoggerSettings() );
	Logger::GetInstance().SetWindowSetupData( application_settings.GetWindowSettings() );
	Logger::GetInstance().SetGraphicsSetupData( application_settings.GetGraphicsSettings() );
	Logger::GetInstance().SetWorldSetupData( application_settings.GetWorldSettings() );
	// TODO: log physics and scripting data

	/*
		Create the game components.
	*/
	Fnd::GameComponentFactory::GameComponentFactory component_factory;

	Fnd::GameComponentInterfaces::IWindow* window = component_factory.GetWindowComponent( application_settings.GetWindowSettings(), engine_settings.GetWindowSettings() );
	Fnd::GameComponentInterfaces::IGraphics* graphics = component_factory.GetGraphicsComponent( application_settings.GetGraphicsSettings(), engine_settings.GetGraphicsSettings() );
	Fnd::GameComponentInterfaces::IPhysics* physics = component_factory.GetPhysicsComponent( application_settings.GetPhysicsSettings() );
	Fnd::GameComponentInterfaces::IWorld* world = component_factory.GetWorldComponent( application_settings.GetWorldSettings() );
	Fnd::Scripting::ScriptManager* scripting = component_factory.GetScriptManager( application_settings.GetScriptingSettings() );

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
	Fnd::Game::Game game( engine_settings );
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
