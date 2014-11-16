#pragma once

#ifndef _OPENGLGRAPHICS_HPP_
#define _OPENGLGRAPHICS_HPP_

#include "..//Include/OpenGLGraphicsBase.hpp"

namespace Fnd
{
namespace OpenGLGraphics
{

/**
	OpenGL graphics implementation.
*/
class OpenGLGraphics:
	public Fnd::OpenGLGraphics::OpenGLGraphicsBase
{
	public:

		void Render();

	public:	

		/**
			Initialise the derived class.
		*/
		bool OnInitialise();

		/**
			Resize the graphics resources for the derived class.
			@param width The new width of the window.
			@param height The new height of the window.
		*/
		void OnResize( unsigned int width, unsigned int height );

		/**
			Release the graphics resources.
		*/
		void OnRelease();
};

}
}

#endif