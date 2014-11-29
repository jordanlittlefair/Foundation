#include "../Include/MeshSystem.hpp"

#include "../../EntitySystem/Include/Components.hpp"
#include "../../EntitySystem/Include/Entity.hpp"
#include "../../EntitySystem/Include/ComponentMaps.hpp"
#include "../../EntitySystem/Include/EntitySystem.hpp"
#include "../../EntitySystem/Include/EntityContainer.hpp"
#include "../../EntitySystem/Include/SystemNodes.hpp"
#include "../../EntitySystem/Include/SystemNodesContainer.hpp"

using namespace Fnd::DirectX11Graphics;
using namespace Fnd::EntitySystem;
using namespace Fnd::Math;

MeshSystem::MeshSystem( DirectX11GraphicsBase* graphics ):
	DirectX11GraphicsSystem( "MeshSystem", graphics ),
	_input_layout(nullptr),
	_transform_matrices(nullptr)
{
}

bool MeshSystem::Initialise()
{
	{
		std::string vs_shader_filename = GetGraphics()->GetResources().GetPipelineData("RenderMesh").vertex_shader;

		std::vector<char> vs_bytecode;
	
		if ( !GetGraphics()->GetResources().GetBytecodeFromFile( vs_shader_filename, vs_bytecode ) )
		{
			return false;
		}

		D3D11_INPUT_ELEMENT_DESC layout_desc[5] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		if ( !SUCCEEDED( GetGraphics()->Device()->CreateInputLayout(	layout_desc, 
															5, 
															&vs_bytecode[0], 
															vs_bytecode.size(), 
															&_input_layout ) ) )
		{
			return false;
		}
	}


	D3D11_BUFFER_DESC vs_cbuffer_desc;
	vs_cbuffer_desc.ByteWidth = sizeof(TransformMatrices_cbuffer);
	vs_cbuffer_desc.Usage = D3D11_USAGE_DYNAMIC;
	vs_cbuffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	vs_cbuffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vs_cbuffer_desc.MiscFlags = 0;
	vs_cbuffer_desc.StructureByteStride = sizeof(TransformMatrices_cbuffer);

	if ( !SUCCEEDED( GetGraphics()->Device()->CreateBuffer( &vs_cbuffer_desc, nullptr, &_transform_matrices ) ) )
	{
		return false;
	}

	return true;
}

void MeshSystem::OnUpdate( const Fnd::CommonResources::FrameData& frame_data )
{
	ForEachCamera( [this]( const CameraData& camera_data )
	{
		/*
			IA
		*/
		GetGraphics()->DeviceContext()->IASetInputLayout( _input_layout );
		GetGraphics()->DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
		
		/*
			VS
		*/
		GetGraphics()->DeviceContext()->VSSetShader( GetGraphics()->GetResources().GetShaders("RenderMesh").vs, nullptr, 0 );

		/*
			RS
		*/
		D3D11_VIEWPORT viewport = { 0, 0, (float)camera_data.screenbuffer->GetWidth(), (float)camera_data.screenbuffer->GetHeight(), 0, 1 };
		GetGraphics()->DeviceContext()->RSSetViewports( 1, &viewport );
		//GetGraphics()->DeviceContext()->RSSetState( ?rs );

		/*
			PS
		*/
		GetGraphics()->DeviceContext()->PSSetShader( GetGraphics()->GetResources().GetShaders("RenderMesh").ps, nullptr, 0 );

		ID3D11SamplerState* ps_samplers[6] = {	GetGraphics()->GetResources().GetDefaultSampler(),
										GetGraphics()->GetResources().GetDefaultSampler(),
										GetGraphics()->GetResources().GetDefaultSampler(),
										GetGraphics()->GetResources().GetDefaultSampler(),
										GetGraphics()->GetResources().GetDefaultSampler(),
										GetGraphics()->GetResources().GetDefaultSampler() };

												

		GetGraphics()->DeviceContext()->PSSetSamplers( 0, 6, ps_samplers );

		/*
			OM
		*/
		GetGraphics()->DeviceContext()->OMSetDepthStencilState( GetGraphics()->GetResources().GetGeometryDepthState(), 1 );

		ID3D11RenderTargetView* render_targets[4] = 
		{
			((ScreenBufferResources*)camera_data.screenbuffer)->GetGBuffer0_rt(),
			((ScreenBufferResources*)camera_data.screenbuffer)->GetGBuffer1_rt(),
			((ScreenBufferResources*)camera_data.screenbuffer)->GetGBuffer2_rt(),
			((ScreenBufferResources*)camera_data.screenbuffer)->GetGBuffer3_rt()
		};
		GetGraphics()->DeviceContext()->OMSetRenderTargets( 4, render_targets, ((ScreenBufferResources*)camera_data.screenbuffer)->GetGBuffer_ds() );

		/*
			Get required/common data
		*/
		Matrix4 camera_xform = camera_data.camera_components.scenenode->data.transform;
		Vector3 camera_pos = Vector3( camera_xform.m30, camera_xform.m31, camera_xform.m32 );
		Vector3 camera_dir = Vector3( camera_xform.m20, camera_xform.m21, camera_xform.m22 );
		Vector3 camera_up = Vector3( camera_xform.m10, camera_xform.m11, camera_xform.m12 );

		Matrix4 view_matrix = Matrix4Helper<>::CreateLookAtMatrixLH( camera_pos, camera_pos + camera_dir, camera_up );
		Matrix4 proj_matrix = Matrix4Helper<>::CreateProjectionMatrixLH( ToRadians(camera_data.camera_components.cameraproperties->data.fov), ((float)camera_data.screenbuffer->GetWidth()) / ((float)camera_data.screenbuffer->GetHeight()), 0.01f, 10000 );

		Matrix4 view_proj_matrix = view_matrix * proj_matrix;

		/*
			Iterate through meshes
		*/
		auto& model_nodes = GetEntitySystem().GetSystemNodesContainer().GetNodeMap<ModelNode>();

		for ( auto model_node = model_nodes.begin(); model_node != model_nodes.end(); ++model_node )
		{
			Fnd::EntitySystem::ModelNode::Pointers model_components;
			if ( !model_node->second.GetPointers( GetEntitySystem(), model_components ) )
			{
				continue;
			}

			Matrix4 world_matrix = model_components.scenenode->data.transform;

			auto& am = GetAssetManager();
			auto model = (DirectX11Model::Model*)GetAssetManager().GetModel(model_components.model->data.model_id)->GetResource();
		
			RenderMeshNode( model,
							world_matrix,
							view_matrix,
							proj_matrix,
							view_proj_matrix,
							&model->root_node );
		}

		GetGraphics()->DeviceContext()->ClearState();
	}
	);
}

void MeshSystem::RenderMeshNode(
						DirectX11Model::Model* model, 
						const Fnd::Math::Matrix4& parent_matrix,
						const Fnd::Math::Matrix4& view_matrix, 
						const Fnd::Math::Matrix4& proj_matrix,
						const Fnd::Math::Matrix4& view_proj_matrix,
						DirectX11Model::Model::MeshNode* mesh_node )
{
	Matrix4 world_matrix = mesh_node->transform * parent_matrix;

	//Matrix4 prev_world_matrix = mesh_node->world_matrix * prev_parent_matrix;

	for ( unsigned int mesh_index = 0; mesh_index < mesh_node->mesh_indices.size(); ++mesh_index )
	{
		/*
			IA
		*/
		auto mesh = model->meshes[mesh_node->mesh_indices[mesh_index]];

		ID3D11Buffer* vbs[1] = { mesh.vb };

		unsigned int strides[1] = { sizeof(DirectX11Model::Model::Mesh::Vertex) };
		unsigned int offsets[1] = { 0 };

		GetGraphics()->DeviceContext()->IASetVertexBuffers( 0, 1, vbs, strides, offsets );
		
		GetGraphics()->DeviceContext()->IASetIndexBuffer( mesh.ib, DXGI_FORMAT_R32_UINT, 0 );

		/*
			VS
		*/
		TransformMatrices_cbuffer vs_cbuffer_data;
		vs_cbuffer_data.world_matrix = Matrix4::Transpose( world_matrix );
		vs_cbuffer_data.view_matrix = Matrix4::Transpose( view_matrix );
		vs_cbuffer_data.proj_matrix = Matrix4::Transpose( proj_matrix );
		vs_cbuffer_data.world_view_proj_matrix = Matrix4::Transpose( world_matrix * view_proj_matrix );
		D3D11_MAPPED_SUBRESOURCE vs_cbuffer;

		GetGraphics()->DeviceContext()->Map( _transform_matrices, 0, D3D11_MAP_WRITE_DISCARD, 0, &vs_cbuffer );
		
		memcpy( vs_cbuffer.pData, &vs_cbuffer_data, sizeof(TransformMatrices_cbuffer) );

		GetGraphics()->DeviceContext()->Unmap( _transform_matrices, 0 );

		ID3D11Buffer* vs_cbuffers[1] = { _transform_matrices };

		GetGraphics()->DeviceContext()->VSSetConstantBuffers( 0, 1, vs_cbuffers );

		/*
			PS
		*/		
		auto& material = model->materials[mesh_node->material_index];
		ID3D11ShaderResourceView* ps_srs[6] = {	material.GetOpacityMap().sr,
												material.GetNormalMap().sr,
												material.GetDiffuseTexture().sr,
												material.GetRoughnessTexture().sr,
												material.GetSpecularTexture().sr,
												material.GetFresnelTexture().sr };

		GetGraphics()->DeviceContext()->PSSetShaderResources( 0, 6, ps_srs );

		/*
			Draw
		*/
		GetGraphics()->DeviceContext()->DrawIndexed( mesh.num_indices, 0, 0 );

	}

	for ( unsigned int i = 0; i < mesh_node->children.size(); ++i )
	{
		RenderMeshNode(	model,
						world_matrix,
						view_matrix,
						proj_matrix,
						view_proj_matrix,
						&mesh_node->children[i] );
	}
}

MeshSystem::~MeshSystem()
{
	if ( _input_layout )
	{
		_input_layout->Release();
	}
	if ( _transform_matrices )
	{
		_transform_matrices->Release();
	}
}