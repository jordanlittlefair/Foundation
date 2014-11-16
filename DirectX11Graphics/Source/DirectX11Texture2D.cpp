#include "../Include/DirectX11Texture2D.hpp"

using namespace Fnd::DirectX11Graphics;

DirectX11Texture2D::DirectX11Texture2D( Fnd::DirectX11Graphics::DirectX11GraphicsBase* graphics ):
	_graphics(graphics)
{
}

bool DirectX11Texture2D::Create( const Fnd::AssetManager::Texture2DData& data )
{
	_resource.a = 1;
	_resource.b = 2;
	_resource.c = 3;

	return true;
}

DirectX11Texture2D::~DirectX11Texture2D()
{
}

void* DirectX11Texture2D::GetResource()
{
	return (void*)&_resource;
}