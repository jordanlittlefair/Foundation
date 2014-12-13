#pragma once

#ifndef _GAME_GAME_HPP_
#define _GAME_GAME_HPP_

#include "../../GameComponentInterfaces/Include/IWindowMessageListener.hpp"
#include "../../GameComponentInterfaces/Include/IGraphicsMessageListener.hpp"
#include "../../GameComponentInterfaces/Include/IPhysicsMessageListener.hpp"
#include "../../GameComponentInterfaces/Include/IWorldMessageListener.hpp"
#include "../../GameComponentInterfaces/Include/IAssetManagerMessageListener.hpp"

#include "../../Settings/Include/EngineSettings.hpp"

#include <memory>
#include <vector>

namespace Fnd
{
namespace GameComponentInterfaces
{
class IWindow;
class IGraphics;
class IPhysics;
class IWorld;
}
namespace EntitySystem
{
class EntitySystem;
class System;
}
namespace AssetManager
{
class AssetManager;
}
namespace Scripting
{
class ScriptManager;
}
namespace Input
{
class InputHandler;
}
namespace OculusRift
{
class OculusRift;
}
}

namespace Fnd
{
namespace Game
{

/**
	Game component which manages the actual game.
	Interacts with the window, graphics, and world implementations through their interfaces.
*/
class Game:
	public Fnd::GameComponentInterfaces::IWindowMessageListener,
	public Fnd::GameComponentInterfaces::IGraphicsMessageListener,
	public Fnd::GameComponentInterfaces::IPhysicsMessageListener,
	public Fnd::GameComponentInterfaces::IWorldMessageListener,
	public Fnd::GameComponentInterfaces::IAssetManagerMessageListener
{
	public:

		/**
			Default Constructor.
		*/
		Game( const Fnd::Settings::EngineSettings& engine_settings );

		// Set the Window.
		void SetWindow( Fnd::GameComponentInterfaces::IWindow* window );

		// Set the Window.
		void SetGraphics( Fnd::GameComponentInterfaces::IGraphics* graphics );

		// Set the Physics.
		void SetPhysics( Fnd::GameComponentInterfaces::IPhysics* physics );
		
		// Set the World.
		void SetWorld( Fnd::GameComponentInterfaces::IWorld* world );

		void SetScriptManager( Fnd::Scripting::ScriptManager* script_manager );

		// Initialise the game and its components.
		// Returns true if successful.
		bool Initialise();

		// Play the game.
		// This method contains the main game loop.
		void Play();


		/*
			Methods inherited from IWindowMessageListener.
		*/

		// Handle Game events when the Window is closed.
		void OnWindowClose();

		// Handle Game events when the Window is resized.
		void OnWindowResize( unsigned int width, unsigned int height );

		// Called when the Window is activated.
		void OnWindowActivate();

		// Called when the Window is deactivated.
		void OnWindowDeactivate();

		bool VRIsEnabled() const;

		/*
			Methods inherited from IGraphicsMessageListener.
		*/

		/**
			Get a pointer to the HWND window handle.
			@note Only implemented for Win32.\n
			All other implementations return null.
			@return Returns the window handle.
		*/
		void* GetHWND() const;

		/**
			Get a pointer to the HCD device context handle.
			@note Only implemented for Win32.\n
			All other implementations return null.
			@return Returns the device context handle.
		*/
		void* GetHDC() const;

		bool GetVRTextureDimensions( unsigned int& width, unsigned int& height );

		/*
			Methods inherited from IWorldMessageListener.
		*/
		Fnd::EntitySystem::EntitySystem& GetEntitySystem();

		Fnd::AssetManager::AssetManager& GetAssetManager();

		Fnd::Scripting::ScriptManager& GetScriptManager();

		/*
			Methods inherited from IContentManagerMessageListener.
		*/
		Fnd::GameComponentInterfaces::IGraphics* GetGraphics();

		// Destructor.
		~Game();

	private:
		
		bool _is_initialised;

		Fnd::GameComponentInterfaces::IWindow* _window;
		Fnd::GameComponentInterfaces::IGraphics* _graphics;
		Fnd::GameComponentInterfaces::IPhysics* _physics;
		Fnd::GameComponentInterfaces::IWorld* _world;
		Fnd::Scripting::ScriptManager* _script_manager;

#ifdef _WIN32
		std::unique_ptr<Fnd::OculusRift::OculusRift> _oculus;
#endif

		std::unique_ptr<Fnd::EntitySystem::EntitySystem> _entity_system;
		std::unique_ptr<Fnd::AssetManager::AssetManager> _asset_manager;
		std::unique_ptr<Fnd::Input::InputHandler> _input_handler;

		std::vector<std::shared_ptr<Fnd::EntitySystem::System>> _systems;

		Fnd::Settings::EngineSettings _engine_settings;
};

}
}

#endif