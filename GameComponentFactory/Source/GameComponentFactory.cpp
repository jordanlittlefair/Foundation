#include "../Include/GameComponentFactory.hpp"

#include "../../Settings/Include/GameComponentSettings.hpp"
#include "../../Utility/Include/MessageBox.hpp"

#include "../../Logger/Include/Logger.hpp"

using namespace Fnd::GameComponentFactory;
using namespace Fnd::GameComponentInterfaces;
using namespace Fnd::Settings;
using namespace Fnd::Logger;

#define OPENGLGRAPHICS
#define USE_DIRECTX

#ifdef _WIN32
	#define WIN32WINDOW
#else
	#define XWINDOWSWINDOW
#endif

#ifdef USE_DIRECTX
	#define DIRECTX11GRAPHICS
#endif

#include <iostream>

#ifdef WIN32WINDOW
	#include "../../Win32Window/Include/Win32Window.hpp"
#endif
#ifdef XWINDOWSWINDOW
	#include "../../XWindowsWindow/Include/XWindowsWindow.hpp"
#endif

IWindow* GameComponentFactory::GetWindowComponent( const Fnd::Settings::WindowSettings& window_data, Fnd::Configuration::WindowConfig& window_config )
{
	window_config.implementation = window_data.implementation;

	std::stringstream ss; ss << window_data.implementation;

	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Creating Window [" + ss.str() + "].") );
	IWindow* window = nullptr;

	if ( window_config.implementations.find(Settings::EngineConfig::GetWindowImplementationString(window_data.implementation)) == window_config.implementations.end() )
	{
		const auto err = "Window [" + Settings::EngineConfig::GetWindowImplementationString(window_data.implementation) + "] is not supported.";
		Fnd::Logger::Logger::GetInstance().Log( LogError(err) );
	}

	/*
		Check the 'implementation' against all existing implementations.
	*/
	if ( Settings::EngineConfig::GetWindowImplementationString(window_data.implementation) == "Win32Window" )
	{
#ifdef WIN32WINDOW
		window = new Fnd::Win32Window::Win32Window();
#endif
	}
	if ( Settings::EngineConfig::GetWindowImplementationString(window_data.implementation) == "XWindowsWindow" )
	{
#ifdef XWINDOWSWINDOW
		window = new Fnd::XWindowsWindow::XWindowsWindow();
#endif
	}
	// TODO: Check other implementations.

	if ( !window )
	{
		const auto err = "Failed to create Window [" + Settings::EngineConfig::GetWindowImplementationString(window_data.implementation) + "].";
		Fnd::Logger::Logger::GetInstance().Log( LogError(err) );
		Fnd::Utility::BlockingMessageBox( "Error", err );
		return nullptr;
	}
	
	window->SetWindowTitle( window_data.window_title );
	window->SetWindowSize( window_data.initial_width, window_data.initial_height );
	window->SetWindowResizable( window_data.is_resizable );
	window->SetWindowFullscreen( window_data.is_fullscreen );

	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Created Window [" + Settings::EngineConfig::GetWindowImplementationString(window_data.implementation) + "].") );
	return window;
}

#ifdef OPENGLGRAPHICS
	#include "../../OpenGLGraphics/Include/OpenGLGraphics.hpp"
#endif
#ifdef DIRECTX11GRAPHICS
	#include "../../DirectX11Graphics/Include/DirectX11Graphics.hpp"
#endif

IGraphics* GameComponentFactory::GetGraphicsComponent( const Fnd::Settings::GraphicsSettings& graphics_data, Fnd::Configuration::GraphicsConfig& graphics_config )
{
	graphics_config.implementation = Settings::EngineConfig::GetGraphicsImplementationString(graphics_data.implementation);

	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Creating Graphics [" + Settings::EngineConfig::GetGraphicsImplementationString(graphics_data.implementation) + "].") );
	IGraphics* graphics = nullptr;

	if ( graphics_config.implementations.find(Settings::EngineConfig::GetGraphicsImplementationString(graphics_data.implementation)) == graphics_config.implementations.end() )
	{
		const auto err = "Graphics [" + Settings::EngineConfig::GetGraphicsImplementationString(graphics_data.implementation) + "] is not supported.";
		Fnd::Logger::Logger::GetInstance().Log( LogError(err) );
	}

	/*
		Check the 'implementation' against all existing implementations.
	*/
	if ( Settings::EngineConfig::GetGraphicsImplementationString(graphics_data.implementation) == "OpenGLGraphics" )
	{
#ifdef OPENGLGRAPHICS
		graphics = new Fnd::OpenGLGraphics::OpenGLGraphics();
#endif
	}
	else
	if ( Settings::EngineConfig::GetGraphicsImplementationString(graphics_data.implementation) == "DirectX11Graphics" )
	{
#ifdef DIRECTX11GRAPHICS
		graphics = new Fnd::DirectX11Graphics::DirectX11Graphics();
#endif
	}
	// TODO: Check other implementations.

	if ( !graphics )
	{
		const auto err = "Failed to create Graphics [" + Settings::EngineConfig::GetGraphicsImplementationString(graphics_data.implementation) + "].";
		Fnd::Logger::Logger::GetInstance().Log( LogError(err) );
		Fnd::Utility::BlockingMessageBox( "Error", err );
		return nullptr;
	}

	graphics->EnableVR( graphics_data.enable_vr );

	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Created Graphics [" + Settings::EngineConfig::GetGraphicsImplementationString(graphics_data.implementation) + "]") );
	return graphics;
}

#include "../../BulletPhysics/Include/BulletPhysics.hpp"

Fnd::GameComponentInterfaces::IPhysics* GameComponentFactory::GetPhysicsComponent( const Fnd::Settings::PhysicsSettings& physics_data )
{
	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Creating Physics [" + Settings::EngineConfig::GetPhysicsImplementationString(physics_data.implementation) + "].") );
	IPhysics* physics = nullptr;

	/*
		Check the 'implementation' against all existing implementations.
	*/
	if ( Settings::EngineConfig::GetPhysicsImplementationString(physics_data.implementation) == "Bullet" )
	{
		physics = new Fnd::BulletPhysics::BulletPhysics();
	}
	// TODO: Check other implementations.

	if ( !physics )
	{
		const auto err = "Failed to create Physics [" + Settings::EngineConfig::GetPhysicsImplementationString(physics_data.implementation) + "].";
		Fnd::Logger::Logger::GetInstance().Log( LogError(err) );
		Fnd::Utility::BlockingMessageBox( "Error", err );
		return nullptr;
	}

	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Created Physics [" + Settings::EngineConfig::GetPhysicsImplementationString(physics_data.implementation) + "]") );
	return physics;
}

#include "../../LoadedWorld/Include/LoadedWorld.hpp"

Fnd::GameComponentInterfaces::IWorld* GameComponentFactory::GetWorldComponent( const Fnd::Settings::WorldSettings& world_data )
{
	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Creating World [" + Settings::EngineConfig::GetWorldImplementationString(world_data.implementation) + "]") );
	IWorld* world = nullptr;

	/*
		Check the 'implementation' against all existing implementations.
	*/
	if ( Settings::EngineConfig::GetWorldImplementationString(world_data.implementation) == "LoadedWorld" )
	{
		world = new Fnd::LoadedWorld::LoadedWorld();
	}
	// TODO: Check other implementations.

	if ( !world )
	{
		const auto err = "Failed to create World [" + Settings::EngineConfig::GetWorldImplementationString(world_data.implementation) + "].";
		Fnd::Logger::Logger::GetInstance().Log( LogError(err) );
		Fnd::Utility::BlockingMessageBox( "Error", err );
		return nullptr;
	}
	
	world->SetWorldSetupData(world_data);

	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Created World [" + Settings::EngineConfig::GetWorldImplementationString(world_data.implementation) + "]") );
	return world;
}

#include "../../MockScripting/Include/MockScriptManager.hpp"

Fnd::Scripting::ScriptManager* GameComponentFactory::GetScriptManager( const Fnd::Settings::ScriptingSettings& scripting_data )
{
	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Creating Scripting [" + Settings::EngineConfig::GetScriptingImplementationString(scripting_data.implementation) + "]") );
	Fnd::Scripting::ScriptManager* scripting = nullptr;

	/*
		Check the 'implementation' against all existing implementations.
	*/
	if ( Settings::EngineConfig::GetScriptingImplementationString(scripting_data.implementation) == "Mock" )
	{
		scripting = new Fnd::MockScripting::MockScriptManager();
	}
	// TODO: Check other implementations.

	if ( !scripting )
	{
		const auto err = "Failed to create Scripting [" + Settings::EngineConfig::GetScriptingImplementationString(scripting_data.implementation) + "].";
		Fnd::Logger::Logger::GetInstance().Log( LogError(err) );
		Fnd::Utility::BlockingMessageBox( "Error", err );
		return nullptr;
	}
	
	//scripting->SetScriptingSetupData(scripting);

	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Created Scripting [" + Settings::EngineConfig::GetScriptingImplementationString(scripting_data.implementation) + "]") );
	return scripting;
}

void GameComponentFactory::Release( IWindow* window )
{
	if ( window )
	{
		// TODO: window->Release();
		delete window;
	}
}

void GameComponentFactory::Release( IGraphics* graphics )
{
	if ( graphics )
	{
		graphics->Release();

		delete graphics;
	}
}

void GameComponentFactory::Release( Fnd::GameComponentInterfaces::IPhysics* physics )
{
	if ( physics )
	{
		delete physics;
	}
}

void GameComponentFactory::Release( IWorld* world )
{
	if ( world )
	{
		//world->Release();
	
		delete world;
	}
}

void GameComponentFactory::Release( Fnd::Scripting::ScriptManager* script_manager )
{
	if ( script_manager )
	{
		delete script_manager;
	}
}