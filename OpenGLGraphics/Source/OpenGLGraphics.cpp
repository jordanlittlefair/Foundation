#include "../Include/OpenGLGraphics.hpp"
#include <Windows.h>
#include "../../glew/Include/glew.hpp"
#include "../../Math/Include/Math.hpp"
using namespace Fnd::OpenGLGraphics;

void OpenGLGraphics::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glClearColor( 0, 0.5f, 1.0f, 1 );
}

bool OpenGLGraphics::OnInitialise()
{
	return true;
}

void OpenGLGraphics::OnResize( unsigned int width, unsigned int height )
{
}

void OpenGLGraphics::OnRelease()
{
}