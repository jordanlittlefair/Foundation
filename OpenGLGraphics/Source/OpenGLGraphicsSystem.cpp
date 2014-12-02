#include "../Include/OpenGLGraphicsSystem.hpp"

using namespace Fnd::OpenGLGraphics;
using namespace Fnd::EntitySystem;

OpenGLGraphicsSystem::OpenGLGraphicsSystem( const std::string& system_name, OpenGLGraphics* graphics ):
	GraphicsSystem(system_name),
	_graphics(graphics)
{
}

void OpenGLGraphicsSystem::Resize( unsigned int width, unsigned int height )
{
}

OpenGLGraphics* OpenGLGraphicsSystem::GetGraphics()
{
	return _graphics;
}

Fnd::GraphicsResources::ScreenBufferResourcesBase* OpenGLGraphicsSystem::GetScreenBufferResources( unsigned int camera_id )
{
	return 0;//_graphics->GetScreenBufferResources(camera_id);
}