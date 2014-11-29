#pragma once

#ifndef _DIRECTX11GRAPHICS_POINTLIGHTSYSTEM_HPP_
#define _DIRECTX11GRAPHICS_POINTLIGHTSYSTEM_HPP_

#include "DirectX11GraphicsSystem.hpp"
#include "../../Math/Include/Math.hpp"

#include <d3d11.h>

namespace Fnd
{
namespace DirectX11Graphics
{

class PointLightSystem:
	public Fnd::DirectX11Graphics::DirectX11GraphicsSystem
{
	public:
	
		PointLightSystem( DirectX11Graphics* graphics );

		bool Initialise();

		~PointLightSystem();

	protected:

		void OnUpdate( const Fnd::CommonResources::FrameData& frame_data );

	private:

		ID3D11InputLayout* _input_layout;

		struct TransformMatrices_cbuffer
		{
			Fnd::Math::Matrix4 world_view_proj_matrix;
		};
		ID3D11Buffer* _transform_cbuffer;

		struct PointLightData_cbuffer
		{
			Fnd::Math::Vector3 light_position;
			float range;

			Fnd::Math::Vector3 colour;
			float distance_falloff_start;
			
			Fnd::Math::Vector4 distance_falloff_params;

		};
		ID3D11Buffer* _point_light_buffer;
};

}
}

#endif