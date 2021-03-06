#include "../Include/GameComponentFactory.hpp"

#include "../../Settings/Include/ApplicationSettings.hpp"
#include "../../Utility/Include/MessageBox.hpp"

#include "../../Logger/Include/Logger.hpp"

using namespace Fnd::GameComponentFactory;
using namespace Fnd::GameComponentInterfaces;
using namespace Fnd::Settings;
using namespace Fnd::Logger;

#define OPENGLGRAPHICS

#ifdef _WIN32
    #define USE_DIRECTX
#endif

#ifdef _WIN32
	#define WIN32WINDOW
#else
#ifdef __APPLE__
    #define MACWINDOW
    #define XWINDOWSWINDOW
#else
	#define XWINDOWSWINDOW
#endif
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
#ifdef MACWINDOW
    #include "../../MacWindow/Include/MacWindow.hpp"
#endif

IWindow* GameComponentFactory::GetWindowComponent( const Fnd::Settings::ApplicationSettings::WindowSettings& window_data, const Fnd::Settings::EngineSettings::WindowSettings& window_settings )
{
	std::stringstream ss; ss << window_data.implementation;

	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Creating Window [" + ss.str() + "].") );
	IWindow* window = nullptr;

	/*
		Check the 'implementation' against all existing implementations.
	*/
	switch (window_data.implementation)
	{
	case Fnd::Settings::EngineConfig::Win32Window_implementation:
#ifdef WIN32WINDOW
		window = new Fnd::Win32Window::Win32Window();
#endif
		break;
	case Fnd::Settings::EngineConfig::XWindowsWindow_implementation:
#ifdef XWINDOWSWINDOW
		window = new Fnd::XWindowsWindow::XWindowsWindow();
#endif
		break;
    case Fnd::Settings::EngineConfig::MacWindow_implementation:
#ifdef MACWINDOW
        window = new Fnd::MacWindow::MacWindow();
#endif
        break;
    case Fnd::Settings::EngineConfig::InvalidWindow_implementation:
    default:
            window = nullptr;
	}

	if ( !window )
	{
		const auto err = "Failed to create Window [" + Settings::EngineConfig::GetWindowImplementationString(window_data.implementation) + "].";
		Fnd::Logger::Logger::GetInstance().Log( LogError(err) );
		Fnd::Utility::BlockingMessageBox( "Error", err );
		return nullptr;
	}
	
#ifdef _WIN32
	window->SetWindowTitle( window_data.window_title );
	window->SetWindowSize( window_data.initial_width, window_data.initial_height );
	window->SetWindowResizable( window_data.is_resizable );
	window->SetWindowFullscreen( window_data.is_fullscreen );
#endif
	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Created Window [" + Settings::EngineConfig::GetWindowImplementationString(window_data.implementation) + "].") );
	return window;
}

#ifdef OPENGLGRAPHICS
	#include "../../OpenGLGraphics/Include/OpenGLGraphics.hpp"
#endif
#ifdef DIRECTX11GRAPHICS
	#include "../../DirectX11Graphics/Include/DirectX11Graphics.hpp"
#endif

IGraphics* GameComponentFactory::GetGraphicsComponent( const Fnd::Settings::ApplicationSettings::GraphicsSettings& graphics_data, const Fnd::Settings::EngineSettings::GraphicsSettings& graphics_config )
{
	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Creating Graphics [" + Settings::EngineConfig::GetGraphicsImplementationString(graphics_data.implementation) + "].") );
	IGraphics* graphics = nullptr;

	/*
		Check the 'implementation' against all existing implementations.
	*/
	switch (graphics_data.implementation)
	{
	case Fnd::Settings::EngineConfig::DirectX11Graphics_implementation:
#ifdef DIRECTX11GRAPHICS
		graphics = new Fnd::DirectX11Graphics::DirectX11Graphics();
#endif
		break;
	case Fnd::Settings::EngineConfig::OpenGLGraphics_implementation:
#ifdef OPENGLGRAPHICS
		graphics = new Fnd::OpenGLGraphics::OpenGLGraphics();
#endif
        break;
    case Fnd::Settings::EngineConfig::InvalidGraphics_implementation:
    default:
		graphics = nullptr;
	}


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

Fnd::GameComponentInterfaces::IPhysics* GameComponentFactory::GetPhysicsComponent( const Fnd::Settings::ApplicationSettings::PhysicsSettings& physics_data )
{
	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Creating Physics [" + Settings::EngineConfig::GetPhysicsImplementationString(physics_data.implementation) + "].") );
	IPhysics* physics = nullptr;

	/*
		Check the 'implementation' against all existing implementations.
	*/
	switch (physics_data.implementation)
	{
	case Fnd::Settings::EngineConfig::BulletPhysics_implementation:
		physics = new Fnd::BulletPhysics::BulletPhysics();
		break;
    case Fnd::Settings::EngineConfig::InvalidPhysics_implementation:
    default:
        physics = nullptr;
	}

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

Fnd::GameComponentInterfaces::IWorld* GameComponentFactory::GetWorldComponent( const Fnd::Settings::ApplicationSettings::WorldSettings& world_data )
{
	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Creating World [" + Settings::EngineConfig::GetWorldImplementationString(world_data.implementation) + "]") );
	IWorld* world = nullptr;

	/*
		Check the 'implementation' against all existing implementations.
	*/
	switch (world_data.implementation)
	{
	case Fnd::Settings::EngineConfig::LoadedWorld_implementation:
		world = new Fnd::LoadedWorld::LoadedWorld();
		break;
    case Fnd::Settings::EngineConfig::InvalidWorld_implementation:
    default:
        world = nullptr;
	}

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

Fnd::Scripting::ScriptManager* GameComponentFactory::GetScriptManager( const Fnd::Settings::ApplicationSettings::ScriptingSettings& scripting_data )
{
	Fnd::Logger::Logger::GetInstance().Log( LogMessage("Creating Scripting [" + Settings::EngineConfig::GetScriptingImplementationString(scripting_data.implementation) + "]") );
	Fnd::Scripting::ScriptManager* scripting = nullptr;

	/*
		Check the 'implementation' against all existing implementations.
	*/
	switch (scripting_data.implementation)
	{
	case Fnd::Settings::EngineConfig::MockScripting_implementation:
		scripting = new Fnd::MockScripting::MockScriptManager();
		break;
	case Fnd::Settings::EngineConfig::LuaScripting_implementation:
		scripting = nullptr;
		break;
    case Fnd::Settings::EngineConfig::InvalidScripting_implementation:
    default:
        scripting = nullptr;
	}

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