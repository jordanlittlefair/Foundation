#include "../Include/GameComponentFactory.hpp"

#include "../../Setup/Include/GameComponentData.hpp"
#include "../../Utility/Include/MessageBox.hpp"

#include "../../Logger/Include/Logger.hpp"

using namespace Fnd::GameComponentFactory;
using namespace Fnd::GameComponentInterfaces;
using namespace Fnd::Setup;
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

IWindow* GameComponentFactory::GetWindowComponent( const Fnd::Setup::WindowSetupData& window_data, Fnd::Configuration::WindowConfig& window_config )
{
	window_config.implementation = window_data.window;

	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Creating Window [" + window_data.window + "].") );
	IWindow* window = nullptr;

	if ( window_config.implementations.find(window_data.window) == window_config.implementations.end() )
	{
		const auto err = "Window [" + window_data.window + "] is not supported.";
		Fnd::Logger::Logger::GetInstance().Log( LogError(err) );
	}

	/*
		Check the 'implementation' against all existing implementations.
	*/
	if ( window_data.window == "Win32Window" )
	{
#ifdef WIN32WINDOW
		window = new Fnd::Win32Window::Win32Window();
#endif
	}
	if ( window_data.window == "XWindowsWindow" )
	{
#ifdef XWINDOWSWINDOW
		window = new Fnd::XWindowsWindow::XWindowsWindow();
#endif
	}
	// TODO: Check other implementations.

	if ( !window )
	{
		const auto err = "Failed to create Window [" + window_data.window + "].";
		Fnd::Logger::Logger::GetInstance().Log( LogError(err) );
		Fnd::Utility::BlockingMessageBox( "Error", err );
		return nullptr;
	}
	
	window->SetWindowTitle( window_data.window_title );
	window->SetWindowSize( window_data.initial_width, window_data.initial_height );
	window->SetWindowResizable( window_data.is_resizable );
	window->SetWindowFullscreen( window_data.is_fullscreen );

	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Created Window [" + window_data.window + "].") );
	return window;
}

#ifdef OPENGLGRAPHICS
	#include "../../OpenGLGraphics/Include/OpenGLGraphics.hpp"
#endif
#ifdef DIRECTX11GRAPHICS
	#include "../../DirectX11Graphics/Include/DirectX11Graphics.hpp"
#endif

IGraphics* GameComponentFactory::GetGraphicsComponent( const Fnd::Setup::GraphicsSetupData& graphics_data, Fnd::Configuration::GraphicsConfig& graphics_config )
{
	graphics_config.implementation = graphics_data.graphics;

	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Creating Graphics [" + graphics_data.graphics + "].") );
	IGraphics* graphics = nullptr;

	if ( graphics_config.implementations.find(graphics_data.graphics) == graphics_config.implementations.end() )
	{
		const auto err = "Graphics [" + graphics_data.graphics + "] is not supported.";
		Fnd::Logger::Logger::GetInstance().Log( LogError(err) );
	}

	/*
		Check the 'implementation' against all existing implementations.
	*/
	if ( graphics_data.graphics == "OpenGLGraphics" )
	{
#ifdef OPENGLGRAPHICS
		graphics = new Fnd::OpenGLGraphics::OpenGLGraphics();
#endif
	}
	else
	if ( graphics_data.graphics == "DirectX11Graphics" )
	{
#ifdef DIRECTX11GRAPHICS
		graphics = new Fnd::DirectX11Graphics::DirectX11Graphics();
#endif
	}
	// TODO: Check other implementations.

	if ( !graphics )
	{
		const auto err = "Failed to create Graphics [" + graphics_data.graphics + "].";
		Fnd::Logger::Logger::GetInstance().Log( LogError(err) );
		Fnd::Utility::BlockingMessageBox( "Error", err );
		return nullptr;
	}

	graphics->EnableVR( graphics_data.enable_vr );

	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Created Graphics [" + graphics_data.graphics + "]") );
	return graphics;
}

#include "../../BulletPhysics/Include/BulletPhysics.hpp"

Fnd::GameComponentInterfaces::IPhysics* GameComponentFactory::GetPhysicsComponent( const Fnd::Setup::PhysicsSetupData& physics_data )
{
	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Creating Physics [" + physics_data.physics + "].") );
	IPhysics* physics = nullptr;

	/*
		Check the 'implementation' against all existing implementations.
	*/
	if ( physics_data.physics == "Bullet" )
	{
		physics = new Fnd::BulletPhysics::BulletPhysics();
	}
	// TODO: Check other implementations.

	if ( !physics )
	{
		const auto err = "Failed to create Physics [" + physics_data.physics + "].";
		Fnd::Logger::Logger::GetInstance().Log( LogError(err) );
		Fnd::Utility::BlockingMessageBox( "Error", err );
		return nullptr;
	}

	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Created Physics [" + physics_data.physics + "]") );
	return physics;
}

#include "../../LoadedWorld/Include/LoadedWorld.hpp"

Fnd::GameComponentInterfaces::IWorld* GameComponentFactory::GetWorldComponent( const Fnd::Setup::WorldSetupData& world_data )
{
	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Creating World [" + world_data.world + "]") );
	IWorld* world = nullptr;

	/*
		Check the 'implementation' against all existing implementations.
	*/
	if ( world_data.world == "LoadedWorld" )
	{
		world = new Fnd::LoadedWorld::LoadedWorld();
	}
	// TODO: Check other implementations.

	if ( !world )
	{
		const auto err = "Failed to create World [" + world_data.world + "].";
		Fnd::Logger::Logger::GetInstance().Log( LogError(err) );
		Fnd::Utility::BlockingMessageBox( "Error", err );
		return nullptr;
	}
	
	world->SetWorldSetupData(world_data);

	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Created World [" + world_data.world + "]") );
	return world;
}

#include "../../MockScripting/Include/MockScriptManager.hpp"

Fnd::Scripting::ScriptManager* GameComponentFactory::GetScriptManager( const Fnd::Setup::ScriptingSetupData& scripting_data )
{
	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Creating Scripting [" + scripting_data.scripting + "]") );
	Fnd::Scripting::ScriptManager* scripting = nullptr;

	/*
		Check the 'implementation' against all existing implementations.
	*/
	if ( scripting_data.scripting == "Mock" )
	{
		scripting = new Fnd::MockScripting::MockScriptManager();
	}
	// TODO: Check other implementations.

	if ( !scripting )
	{
		const auto err = "Failed to create Scripting [" + scripting_data.scripting + "].";
		Fnd::Logger::Logger::GetInstance().Log( LogError(err) );
		Fnd::Utility::BlockingMessageBox( "Error", err );
		return nullptr;
	}
	
	//scripting->SetScriptingSetupData(scripting);

	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Created Scripting [" + scripting_data.scripting + "]") );
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