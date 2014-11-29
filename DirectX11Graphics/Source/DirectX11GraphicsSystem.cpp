#include "../Include/DirectX11GraphicsSystem.hpp"

using namespace Fnd::DirectX11Graphics;
using namespace Fnd::EntitySystem;

DirectX11GraphicsSystem::DirectX11GraphicsSystem( const std::string& system_name, DirectX11Graphics* graphics ):
	GraphicsSystem(system_name),
	_graphics(graphics)
{
}

void DirectX11GraphicsSystem::Resize( unsigned int width, unsigned int height )
{
}

DirectX11Graphics* DirectX11GraphicsSystem::GetGraphics()
{
	return _graphics;
}

Fnd::GraphicsResources::IScreenBufferResources* DirectX11GraphicsSystem::GetScreenBufferResources( unsigned int camera_id )
{
	return _graphics->GetScreenBufferResources(camera_id);
}