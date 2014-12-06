#pragma once

#ifndef _DIRECTX11GRAPHICS_SPOTLIGHTSYSTEM_HPP_
#define _DIRECTX11GRAPHICS_SPOTLIGHTSYSTEM_HPP_

#include "DirectX11GraphicsSystem.hpp"
#include "../../Math/Include/Math.hpp"

#include <d3d11.h>

namespace Fnd
{
namespace DirectX11Graphics
{

class SpotLightSystem:
	public Fnd::DirectX11Graphics::DirectX11GraphicsSystem
{
	public:
	
		SpotLightSystem( DirectX11Graphics* graphics );

		bool Initialise();

		~SpotLightSystem();

	protected:

		void OnUpdate( const Fnd::CommonResources::FrameData& frame_data );

	private:

		ID3D11InputLayout* _input_layout;

		struct TransformMatrices_cbuffer
		{
			Fnd::Math::Matrix4 world_view_proj_matrix;
		};
		ID3D11Buffer* _transform_cbuffer;

		struct SpotLightData_cbuffer
		{
			Fnd::Math::Vector3 light_view_position;
			float light_range;

			Fnd::Math::Vector3 light_centre_direction;
			float light_near_plane;

			Fnd::Math::Vector3 light_colour;
			float light_fov;

			float distance_falloff_start;
			float angular_falloff_start;
			float light_size;
			float pad0;

			Fnd::Math::Vector4 distance_falloff_control_points;

			Fnd::Math::Vector4 angular_falloff_control_points;
		};
		ID3D11Buffer* _spot_light_buffer;
};

}
}

#endif