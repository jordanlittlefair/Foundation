#pragma once

#ifndef _DIRECTX11GRAPHICS_DIRECTX11TEXTURE2D_HPP_
#define _DIRECTX11GRAPHICS_DIRECTX11TEXTURE2D_HPP_

#include "../../AssetManager/Include/Texture2D.hpp"

namespace Fnd
{
namespace DirectX11Graphics
{
class DirectX11GraphicsBase;

class DirectX11Texture2D:
	public Fnd::AssetManager::Texture2D
{
	public:

		DirectX11Texture2D( Fnd::DirectX11Graphics::DirectX11GraphicsBase* graphics );

		bool Create( const Fnd::AssetManager::Texture2DData& data );

		~DirectX11Texture2D();

		struct Resource
		{
			int a;
			int b;
			int c;
		};

		void* GetResource();

	private:

		Fnd::DirectX11Graphics::DirectX11GraphicsBase* _graphics;

		Resource _resource;
};

}
}

#endif