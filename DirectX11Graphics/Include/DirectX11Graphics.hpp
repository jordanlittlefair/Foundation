#pragma once

#ifndef _DIRECTX11GRAPHICS_DIRECTX11GRAPHICS_HPP_
#define _DIRECTX11GRAPHICS_DIRECTX11GRAPHICS_HPP_

#include "DirectX11GraphicsBase.hpp"

namespace Fnd
{
namespace DirectX11Graphics
{

/**
	DirectX11 Graphics implementation.
*/
class DirectX11Graphics:
	public DirectX11GraphicsBase
{
	public:

		// Default constructor.
		DirectX11Graphics();

		// Called when Graphics is initialised.
		bool OnInitialise();

		// Called when Graphics is resized.
		void OnResize( unsigned int width, unsigned int height );
				
		// Called when Graphics is rendered.
		void OnRender();
		
		~DirectX11Graphics();
};

}
}

#endif