#pragma once

#ifndef _DIRECTIONALLIGHTSYSTEM_HPP_
#define _DIRECTIONALLIGHTSYSTEM_HPP_

#include "DirectX11GraphicsSystem.hpp"
#include "../../Math/Include/Math.hpp"

#include <d3d11.h>

namespace Fnd
{
namespace DirectX11Graphics
{

class DirectionalLightSystem:
	public Fnd::DirectX11Graphics::DirectX11GraphicsSystem
{
	public:
	
		DirectionalLightSystem( DirectX11GraphicsBase* graphics );

		bool Initialise();

		~DirectionalLightSystem();

	protected:

		void OnUpdate( const Fnd::CommonResources::FrameData& frame_data );

	private:

		struct DirectionalLightData_cbuffer
		{
			Fnd::Math::Vector3 light_direction;
			float pad0;

			Fnd::Math::Vector3 light_colour;
			float pad1;

		};
		ID3D11Buffer* _directional_light_buffer;
};

}
}

#endif