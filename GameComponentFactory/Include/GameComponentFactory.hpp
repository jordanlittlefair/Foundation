#pragma once

#ifndef _GAMECOMPONENTFACTORY_GAMECOMPONENTFACTORY_HPP_
#define _GAMECOMPONENTFACTORY_GAMECOMPONENTFACTORY_HPP_

#include <string>

#include "../../Utility/Include/XmlManager.hpp"
#include "../../Configuration/Include/Configuration.hpp"

namespace Fnd
{
namespace GameComponentInterfaces
{
	class IWindow;
	class IGraphics;
	class IPhysics;
	class IWorld;
}
namespace Setup
{
	class Setup;
	struct WindowSetupData;
	struct GraphicsSetupData;
	struct PhysicsSetupData;
	struct WorldSetupData;
	struct ScriptingSetupData;
}
namespace Scripting
{
	class ScriptManager;
}
}

namespace Fnd
{
namespace GameComponentFactory
{

/**
	A factory class to create game components from a setup file.
*/
class GameComponentFactory
{
	public:

		/**
			Get the window implementation described by the setup file.
			Returns null if the creation of the window failed.
			@return Returns a pointer to the IWindow interface of the window.
		*/
		Fnd::GameComponentInterfaces::IWindow* GetWindowComponent( const Fnd::Setup::WindowSetupData& window_data, Fnd::Configuration::WindowConfig& window_config );

		/**
			Get the graphics implementation described by the setup file.
			Returns null if the creation of the graphics failed.
			@return Returns a pointer to the IGraphics interface of the graphics.
		*/
		Fnd::GameComponentInterfaces::IGraphics* GetGraphicsComponent( const Fnd::Setup::GraphicsSetupData& graphics_data, Fnd::Configuration::GraphicsConfig& graphics_config );

		Fnd::GameComponentInterfaces::IPhysics* GetPhysicsComponent( const Fnd::Setup::PhysicsSetupData& physics_data );

		Fnd::GameComponentInterfaces::IWorld* GetWorldComponent( const Fnd::Setup::WorldSetupData& world_data );

		Fnd::Scripting::ScriptManager* GetScriptManager( const Fnd::Setup::ScriptingSetupData& scripting_data );

		/**
			Release any resources and delete the window pointer.
			@note A pointer passed to this will be deleted, and\n
			must not be dereferenced after calling this method.
			@param window A pointer to the window to release.
		*/
		void Release( Fnd::GameComponentInterfaces::IWindow* window );

		/**
			Release any resources and delete the graphics pointer.
			@note A pointer passed to this will be deleted, and\n
			must not be dereferenced after calling this method.
			@param window A pointer to the graphics to release.
		*/
		void Release( Fnd::GameComponentInterfaces::IGraphics* graphics );

		void Release( Fnd::GameComponentInterfaces::IPhysics* physics );

		void Release( Fnd::GameComponentInterfaces::IWorld* world );

		void Release( Fnd::Scripting::ScriptManager* script_manager );
};

}
}

#endif