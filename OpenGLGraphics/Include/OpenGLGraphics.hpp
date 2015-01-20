#pragma once

#ifndef _OPENGLGRAPHICS_OPENGLGRAPHICS_HPP_
#define _OPENGLGRAPHICS_OPENGLGRAPHICS_HPP_

#include "../../GraphicsResources/Include/GraphicsImplementation.hpp"
#include "ScreenBufferResources.hpp"

namespace Fnd
{
namespace OpenGLGraphics
{

/**
	Base class for OpenGL graphics implementations.
*/
class OpenGLGraphics:
	public Fnd::GraphicsResources::GraphicsImplementation
{
	public:

		/**
			Default constructor.
		*/
		OpenGLGraphics();
		
		bool VRIsSupported();

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

		void BeginRender();

		/**
			Release the graphics resources.
			@note Calls OnRelease() to release resources in derived classes.
		*/
		void Release();

		std::vector<std::shared_ptr<Fnd::EntitySystem::System>> GetSystems();

		Fnd::AssetManager::Texture2D* GetNewTexture2D();
		Fnd::AssetManager::Model* GetNewModel();
		
		Fnd::GameComponentInterfaces::IGraphics::OculusDataOpenGL GetOculusDataOpenGL();

		bool AddScreenBufferResources( unsigned int id, unsigned int width, unsigned int height );

		ScreenBufferResources* GetScreenBufferResources( unsigned int id );

	protected:
		
		void OnSetOculusData( const Fnd::GameComponentInterfaces::IGraphics::OculusData& oculus_data );

		void* _hglrc;
};

}
}

#endif