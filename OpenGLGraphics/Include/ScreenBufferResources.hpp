#pragma once

#ifndef _OPENGLGRAPHICS_SCREENBUFFERRESOURCES_HPP_
#define _OPENGLGRAPHICS_SCREENBUFFERRESOURCES_HPP_

#include "../../Math/Include/Math.hpp"

#include "../../GraphicsResources/Include/ScreenBufferResourcesBase.hpp"

#ifdef _WIN32
#include "../../glew/Include/glew.hpp"
#else
#include <OpenGL/gl3.h>
#endif

namespace Fnd
{
namespace OpenGLGraphics
{
class OpenGLGraphics;

class ScreenBufferResources:
	public Fnd::GraphicsResources::ScreenBufferResourcesBase
{
	public:

		ScreenBufferResources( OpenGLGraphics* graphics );
				
		/*
			Gbuffer
		*/
		GLuint GetGBuffer0_tex();
		GLuint GetGBuffer1_tex();
		GLuint GetGBuffer2_tex();
		GLuint GetGBuffer3_tex();

		GLuint GetGBuffer_dsrb();	// depth stencil renderbuffer

		GLuint GetGBuffer_framebuffer();

		/*
			LBuffer
		*/
		GLuint GetLBuffer_tex();
		GLuint GetLBuffer_fb();

		// No ambient occlusion resources in OpenGL yet

		GLuint GetPositionReconstructionBuffer();
		
		~ScreenBufferResources();

	protected:

		void OnUpdatePositionReconstructionData( const ScreenBufferResources::PositionReconstruction_cbuffer& data );

		void ReleaseResources();
		bool CreateResources();

	private:

		OpenGLGraphics* _graphics;

		GLuint _GBuffer0_tex;
		GLuint _GBuffer1_tex;
		GLuint _GBuffer2_tex;
		GLuint _GBuffer3_tex;

		GLuint _GBuffer_dsrb;

		GLuint _GBuffer_framebuffer;

		GLuint _LBuffer_tex;
		GLuint _LBuffer_fb;

		GLuint _position_reconstruction_cbuffer;
};

}
}

#endif