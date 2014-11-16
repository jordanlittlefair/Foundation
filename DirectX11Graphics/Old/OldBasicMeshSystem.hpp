#pragma once

#ifndef _OLDBASICMESHSYSTEM_HPP_
#define _OLDBASICMESHSYSTEM_HPP_

#include "DirectX11GraphicsSystem.hpp"
#include "../Include/DirectX11Model.hpp"
#include "../../Math/Include/Math.hpp"

#include <d3d11.h>

namespace Fnd
{
namespace DirectX11Graphics
{

class OldBasicMeshSystem:
	public Fnd::DirectX11Graphics::DirectX11GraphicsSystem
{
	public:
	
		OldBasicMeshSystem( DirectX11GraphicsBase* graphics );

		bool Initialise();

		void Update();

		~OldBasicMeshSystem();

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

			Fnd::Math::Vector3 cam_pos;
			float pad0;
		};

		Fnd::Math::Vector3 _cam_pos;// This is only temporary for testing cook-torrance stuff

		ID3D11Buffer* _transform_matrices;

		ID3D11DepthStencilState* _depth_state;
};

}
}

#endif