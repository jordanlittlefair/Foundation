#pragma once

#ifndef _DIRECTX11GRAPHICS_AMBIENTLIGHTSYSTEM_HPP_
#define _DIRECTX11GRAPHICS_AMBIENTLIGHTSYSTEM_HPP_

#include "DirectX11GraphicsSystem.hpp"

#include "../../Math/Include/Math.hpp"

#include <d3d11.h>

namespace Fnd
{
namespace DirectX11Graphics
{

class AmbientLightSystem:
	public Fnd::DirectX11Graphics::DirectX11GraphicsSystem
{
	public:
	
		AmbientLightSystem( DirectX11GraphicsBase* graphics );

		bool Initialise();

		~AmbientLightSystem();

	protected:
		
		void OnUpdate( const Fnd::CommonResources::FrameData& frame_data );

	private:

		struct AmbientLightData_cbuffer
		{
			Fnd::Math::Vector3 colour;
			float pad0;
		};

		ID3D11Buffer* _ambient_light_buffer;
};

}
}

#endif