#pragma once

#ifndef _OPENGLGRAPHICS_MESHSYSTEM_HPP_
#define _OPENGLGRAPHICS_MESHSYSTEM_HPP_

#include "OpenGLGraphicsSystem.hpp"
#include "OpenGLModel.hpp"
#include "../../Math/Include/Math.hpp"

#include "../../glew/Include/glew.hpp"

namespace Fnd
{
namespace OpenGLGraphics
{

class MeshSystem:
	public Fnd::OpenGLGraphics::OpenGLGraphicsSystem
{
	public:
	
		MeshSystem( OpenGLGraphics* graphics );

		bool Initialise();

		~MeshSystem();

	protected:

		void OnUpdate( const Fnd::CommonResources::FrameData& frame_data );

	private:

		void RenderMeshNode(
						OpenGLModel::Model* model, 
						const Fnd::Math::Matrix4& parent_matrix,
						const Fnd::Math::Matrix4& view_matrix, 
						const Fnd::Math::Matrix4& proj_matrix,
						const Fnd::Math::Matrix4& view_proj_matrix,
						OpenGLModel::Model::MeshNode* mesh_node );

		//ID3D11InputLayout* _input_layout;

		struct TransformMatrices_cbuffer
		{
			Fnd::Math::Matrix4 world_matrix;
			Fnd::Math::Matrix4 view_matrix;
			Fnd::Math::Matrix4 proj_matrix;
			Fnd::Math::Matrix4 world_view_proj_matrix;

			Fnd::Math::Matrix4 previous_world_view_proj_matrix;
		};

		//ID3D11Buffer* _transform_matrices;
};

}
}

#endif