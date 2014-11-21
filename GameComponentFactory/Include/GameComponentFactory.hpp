#pragma once

#ifndef _GAMECOMPONENTFACTORY_GAMECOMPONENTFACTORY_HPP_
#define _GAMECOMPONENTFACTORY_GAMECOMPONENTFACTORY_HPP_

#include <string>

#include "../../Utility/Include/XmlManager.hpp"
#include "../../Settings/Include/EngineSettings.hpp"
#include "../../Settings/Include/ApplicationSettings.hpp"

namespace Fnd
{
namespace GameComponentInterfaces
{
	class IWindow;
	class IGraphics;
	class IPhysics;
	class IWorld;
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
		Fnd::GameComponentInterfaces::IWindow* GetWindowComponent( const Fnd::Settings::ApplicationSettings::WindowSettings& window_data, Fnd::Settings::EngineSettings::WindowSettings& window_config );

		/**
			Get the graphics implementation described by the setup file.
			Returns null if the creation of the graphics failed.
			@return Returns a pointer to the IGraphics interface of the graphics.
		*/
		Fnd::GameComponentInterfaces::IGraphics* GetGraphicsComponent( const Fnd::Settings::ApplicationSettings::GraphicsSettings& graphics_data, Fnd::Settings::EngineSettings::GraphicsSettings& graphics_config );

		Fnd::GameComponentInterfaces::IPhysics* GetPhysicsComponent( const Fnd::Settings::ApplicationSettings::PhysicsSettings& physics_data );

		Fnd::GameComponentInterfaces::IWorld* GetWorldComponent( const Fnd::Settings::ApplicationSettings::WorldSettings& world_data );

		Fnd::Scripting::ScriptManager* GetScriptManager( const Fnd::Settings::ApplicationSettings::ScriptingSettings& scripting_data );

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