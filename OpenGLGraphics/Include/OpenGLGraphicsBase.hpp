#pragma once

#ifndef _OPENGLGRAPHICS_OPENGLGRAPHICSBASE_HPP_
#define _OPENGLGRAPHICS_OPENGLGRAPHICSBASE_HPP_

#include "../../GraphicsResources/Include/GraphicsImplementation.hpp"

namespace Fnd
{
namespace OpenGLGraphics
{

/**
	Base class for OpenGL graphics implementations.
*/
class OpenGLGraphicsBase:
	public Fnd::GraphicsResources::GraphicsImplementation
{
	public:

		/**
			Default constructor.
		*/
		OpenGLGraphicsBase();

		/**
			Set the a pointer to the game.
			@param game A pointer to the IGraphicsMessageListener inferface of the Game component.
		*/
		void SetGraphicsMessageListener( Fnd::GameComponentInterfaces::IGraphicsMessageListener* game );

		void SetGraphicsSettings( const Fnd::Settings::EngineSettings::GraphicsSettings& config );

		void SetEntitySystem( Fnd::EntitySystem::EntitySystem* entity_system );

		bool VRIsSupported();

		void EnableVR( bool enable );

		bool VRIsEnabled() const;

		/**
			Initialise OpenGLGraphics.
			@note Calls OnInitialise() to initialise derived classes.
			@return Returns true if successful.
		*/
		bool Initialise();

		/**
			Present the backbuffer to the screen.
		*/
		void Present();

		/**
			Resize the graphics resources.
			@note Calls OnResize() to initialise derived classes.
			@param width The new width of the window.
			@param height The new height of the window.
		*/
		void Resize( unsigned int width, unsigned int height );

		/**
			Release the graphics resources.
			@note Calls OnRelease() to release resources in derived classes.
		*/
		void Release();

		std::vector<std::shared_ptr<Fnd::EntitySystem::System>> GetSystems();

		Fnd::AssetManager::Texture2D* GetNewTexture2D();
		Fnd::AssetManager::Model* GetNewModel();

		void SetActiveCamera( unsigned int i, unsigned int j );

		Fnd::GameComponentInterfaces::IGraphics::OculusDataD3D11 GetOculusDataD3D11();
		Fnd::GameComponentInterfaces::IGraphics::OculusDataOpenGL GetOculusDataOpenGL();

		void UpdateVRCameraOffsets( const CameraOffsets& camera_offsets );

		bool AddScreenBufferResources( unsigned int id, unsigned int width, unsigned int height );

	public:	

		/**
			Initialise the derived class.
		*/
		virtual bool OnInitialise() = 0;

		/**
			Resize the graphics resources for the derived class.
			@param width The new width of the window.
			@param height The new height of the window.
		*/
		virtual void OnResize( unsigned int width, unsigned int height ) = 0;

		/**
			Release resources in the derived class.
		*/
		virtual void OnRelease() = 0;

	protected:

		void OnSetOculusData( const Fnd::GameComponentInterfaces::IGraphics::OculusData& oculus_data );

		Fnd::GameComponentInterfaces::IGraphicsMessageListener* _game;
		void* _hglrc;
};

}
}

#endif