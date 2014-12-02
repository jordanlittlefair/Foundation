#include "../Include/ScreenBufferResources.hpp"

using namespace Fnd::OpenGLGraphics;

ScreenBufferResources::ScreenBufferResources( OpenGLGraphics* graphics ):
	_graphics(graphics),
	_GBuffer0_tex(0),
	_GBuffer1_tex(0),
	_GBuffer2_tex(0),
	_GBuffer3_tex(0),
	_GBuffer_dsrb(0),
	_GBuffer_framebuffer(0),
	_LBuffer_tex(0),
	_LBuffer_fb(0),
	_position_reconstruction_cbuffer(0)
{
}

GLuint ScreenBufferResources::GetGBuffer0_tex()
{
	return _GBuffer0_tex;
}

GLuint ScreenBufferResources::GetGBuffer1_tex()
{
	return _GBuffer1_tex;
}

GLuint ScreenBufferResources::GetGBuffer2_tex()
{
	return _GBuffer2_tex;
}

GLuint ScreenBufferResources::GetGBuffer3_tex()
{
	return _GBuffer3_tex;
}

GLuint ScreenBufferResources::GetGBuffer_dsrb()
{
	return _GBuffer_dsrb;
}

GLuint ScreenBufferResources::GetGBuffer_framebuffer()
{
	return _GBuffer_framebuffer;
}

GLuint ScreenBufferResources::GetLBuffer_tex()
{
	return _LBuffer_tex;
}

GLuint ScreenBufferResources::GetLBuffer_fb()
{
	return _LBuffer_fb;
}



GLuint ScreenBufferResources::GetPositionReconstructionBuffer()
{
	return _position_reconstruction_cbuffer;
}

		
ScreenBufferResources::~ScreenBufferResources()
{
}

void ScreenBufferResources::OnUpdatePositionReconstructionData( const ScreenBufferResources::PositionReconstruction_cbuffer& data )
{
}

void ScreenBufferResources::ReleaseResources()
{
	auto DeleteTex = [](GLuint& tex)
	{
		if ( tex )
		{
			glDeleteTextures(1,&tex);
			tex = 0;
		}
	};
	auto DeleteRB = [](GLuint& rb)
	{
		if ( rb )
		{
			glDeleteRenderbuffers(1,&rb);
			rb = 0;
		}
	};
	auto DeleteFB = [](GLuint& fb)
	{
		if ( fb )
		{
			glDeleteFramebuffers(1,&fb);
			fb = 0;
		}
	};


	DeleteTex( _GBuffer0_tex );
	DeleteTex( _GBuffer1_tex );
	DeleteTex( _GBuffer2_tex );
	DeleteTex( _GBuffer3_tex );

	DeleteRB( _GBuffer_dsrb );

	DeleteFB( _GBuffer_framebuffer );

	DeleteTex( _LBuffer_tex );
	DeleteFB( _LBuffer_fb );

	// Delete: _position_reconstruction_cbuffer;
	// too, but need to decide how it's stored first.
}

bool ScreenBufferResources::CreateResources()
{
	// Create gbuffer's framebuffer
	GLenum framebuffer_status = 0;
	glGenFramebuffers( 1, &_GBuffer_framebuffer );
	glBindFramebuffer( GL_FRAMEBUFFER, _GBuffer_framebuffer );

	// Create textures, and depth stencil renderbuffer
	glGenTextures( 1, &_GBuffer0_tex );
	glGenTextures( 1, &_GBuffer1_tex );
	glGenTextures( 1, &_GBuffer2_tex );
	glGenTextures( 1, &_GBuffer3_tex );
	glGenRenderbuffers( 1, &_GBuffer_dsrb );

	// Bind tex0 (geometry)
	glBindTexture( GL_TEXTURE_RECTANGLE, _GBuffer0_tex );
	glTexImage2D( GL_TEXTURE_RECTANGLE, 0, GL_RGB16F, GetWidth(), GetHeight(), 0, GL_RGBA, GL_FLOAT, 0 );
	glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_RECTANGLE, _GBuffer0_tex, 0 );

	// Bind tex1 (diffuse)
	glBindTexture( GL_TEXTURE_RECTANGLE, _GBuffer1_tex );
	glTexImage2D( GL_TEXTURE_RECTANGLE, 0, GL_RGBA, GetWidth(), GetHeight(), 0, GL_RGBA, GL_FLOAT, 0 );
	glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_RECTANGLE, _GBuffer1_tex, 0 );
	
	// Bind tex1 (specular)
	glBindTexture( GL_TEXTURE_RECTANGLE, _GBuffer2_tex );
	glTexImage2D( GL_TEXTURE_RECTANGLE, 0, GL_RGBA, GetWidth(), GetHeight(), 0, GL_RGBA, GL_FLOAT, 0 );
	glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_RECTANGLE, _GBuffer2_tex, 0 );
	
	// Bind tex1 (motion-currnetly unused)
	glBindTexture( GL_TEXTURE_RECTANGLE, _GBuffer3_tex );
	glTexImage2D( GL_TEXTURE_RECTANGLE, 0, GL_RG16F, GetWidth(), GetHeight(), 0, GL_RG, GL_FLOAT, 0 );
	glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_RECTANGLE, _GBuffer3_tex, 0 );

	GLenum draw_buffers[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };

	glDrawBuffers( 3, draw_buffers );

	framebuffer_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if ( framebuffer_status != GL_FRAMEBUFFER_COMPLETE )
	{
		return false;
	}
	else
	{
		glBindFramebuffer( GL_FRAMEBUFFER, 0 );

		return true;
	}
}
