#pragma once

#ifndef _DIRECTX11GRAPHICS_MESHSYSTEM_HPP_
#define _DIRECTX11GRAPHICS_MESHSYSTEM_HPP_

#include "DirectX11GraphicsSystem.hpp"
#include "../Include/DirectX11Model.hpp"
#include "../../Math/Include/Math.hpp"

#include <d3d11.h>

namespace Fnd
{
namespace DirectX11Graphics
{

class MeshSystem:
	public Fnd::DirectX11Graphics::DirectX11GraphicsSystem
{
	public:
	
		MeshSystem( DirectX11Graphics* graphics );

		bool Initialise();

		~MeshSystem();

	protected:

		void OnUpdate( const Fnd::CommonResources::FrameData& frame_data );

	private:

		void RenderMeshNode(
						DirectX11Model::Model* model, 
						const Fnd::Math::Matrix4& parent_matrix,
						const Fnd::Math::Matrix4& view_matrix, 
						const Fnd::Math::Matrix4& proj_matrix,
						const Fnd::Math::Matrix4& view_proj_matrix,
						DirectX11Model::Model::MeshNode* mesh_node );

		ID3D11InputLayout* _input_layout;

		struct TransformMatrices_cbuffer
		{
			Fnd::Math::Matrix4 world_matrix;
			Fnd::Math::Matrix4 view_matrix;
			Fnd::Math::Matrix4 proj_matrix;
			Fnd::Math::Matrix4 world_view_proj_matrix;

			Fnd::Math::Matrix4 previous_world_view_proj_matrix;
		};

		ID3D11Buffer* _transform_matrices;
};

}
}

#endif