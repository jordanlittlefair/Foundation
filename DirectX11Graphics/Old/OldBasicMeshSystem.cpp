#include "../Include/OldBasicMeshSystem.hpp"

#include "../../Logger/Include/Logger.hpp"

#include "../Include/DirectX11GraphicsBase.hpp"
#include "../Include/DirectX11Resources.hpp"

using namespace Fnd::DirectX11Graphics;
using namespace Fnd::EntitySystem;
using namespace Fnd::Math;
using namespace Fnd::Logger;

OldBasicMeshSystem::OldBasicMeshSystem( DirectX11GraphicsBase* graphics ):
	DirectX11GraphicsSystem( "OldBasicMeshSystem", graphics ),
	_input_layout(nullptr),
	_transform_matrices(nullptr),
	_depth_state(nullptr)
{
}

bool OldBasicMeshSystem::Initialise()
{
	std::string vs_shader_filename = GetGraphics()->GetResources().GetPipelineData("RenderSimpleMeshForward").vertex_shader;

	std::vector<char> vs_bytecode;
	
	if ( !GetGraphics()->GetResources().GetBytecodeFromFile( vs_shader_filename, vs_bytecode ) )
	{
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC layout_desc[4] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	if ( !SUCCEEDED( GetGraphics()->Device()->CreateInputLayout(	layout_desc, 
														4, 
														&vs_bytecode[0], 
														vs_bytecode.size(), 
														&_input_layout ) ) )
	{
		return false;
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

	{
		D3D11_DEPTH_STENCIL_DESC ds_desc;
		ds_desc.DepthEnable = true;
		ds_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		ds_desc.DepthFunc = D3D11_COMPARISON_LESS;
		ds_desc.StencilEnable = true;
		ds_desc.StencilReadMask = ~0;
		ds_desc.StencilWriteMask = ~0;
		ds_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		ds_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		ds_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
		ds_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		ds_desc.BackFace = ds_desc.FrontFace;

		if ( !SUCCEEDED( GetGraphics()->Device()->CreateDepthStencilState( &ds_desc, &_depth_state ) ) )
		{
			return false;
		}
	}

	return true;
}

void OldBasicMeshSystem::Update()
{
	auto& es = GetEntitySystem();
	auto& a = es.GetSystemNodesContainer();
	auto& camera_nodes = GetEntitySystem().GetSystemNodesContainer().GetCameraNodeMap();
	assert(camera_nodes.size() != 0);
	CameraNode& camera_node = camera_nodes.begin()->second;

	CameraNode::Pointers camera_components;

	if ( !camera_node.GetPointers( GetEntitySystem(), camera_components ) )
	{
		return;
	}

	Vector3 camera_pos = camera_components.scenenode->data.position;
	Quaternion camera_rot = camera_components.scenenode->data.rotation.GetNormalised();
	_cam_pos = camera_pos;
	Matrix4 view_matrix = Matrix4Helper<>::CreateLookAtMatrixLH( camera_pos, camera_pos + camera_rot.GetZAxis(), camera_rot.GetYAxis() );
	Matrix4 proj_matrix = Matrix4Helper<>::CreateProjectionMatrixLH( ToRadians(camera_components.cameraproperties->data.fov), 1920/1080.0f, 0.01f, 10000 );

	Matrix4 view_proj_matrix = view_matrix * proj_matrix;

	/*
		IA
	*/
	GetGraphics()->DeviceContext()->IASetInputLayout( _input_layout );
	GetGraphics()->DeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	/*
		VS
	*/
	GetGraphics()->DeviceContext()->VSSetShader( GetGraphics()->GetResources().GetShaders("RenderSimpleMeshForward").vs, nullptr, 0 );

	/*
		RS
	*/
	D3D11_VIEWPORT viewport = { 0, 0, (float)GetGraphics()->GetWidth(), (float)GetGraphics()->GetHeight(), 0, 1 };

	GetGraphics()->DeviceContext()->RSSetViewports( 1, &viewport );

	/*
		PS
	*/
	GetGraphics()->DeviceContext()->PSSetShader( GetGraphics()->GetResources().GetShaders("RenderSimpleMeshForward").ps, nullptr, 0 );

	/*
		OM
	*/
	GetGraphics()->DeviceContext()->OMSetDepthStencilState( _depth_state, 1 );

	ID3D11RenderTargetView* rts[1] = {	GetGraphics()->BackBuffer() };

	GetGraphics()->DeviceContext()->OMSetRenderTargets( 1, rts, GetGraphics()->GetDepthStencil() );

	auto& model_nodes = GetEntitySystem().GetSystemNodesContainer().GetModelNodeMap();

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
}

void OldBasicMeshSystem::RenderMeshNode(
		DirectX11Model::Model* model, 
		const Matrix4& parent_matrix,
		const Matrix4& view_matrix, 
		const Matrix4& proj_matrix,
		const Matrix4& view_proj_matrix,
		DirectX11Model::Model::MeshNode* mesh_node )
{
	Matrix4 world_matrix = parent_matrix;//mesh_node->transform * parent_matrix;

	for ( unsigned int i = 0; i < mesh_node->mesh_indices.size(); ++i )
	{
		/*
			IA
		*/
		auto mesh = model->meshes[mesh_node->mesh_indices[i]];

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
		vs_cbuffer_data.cam_pos = _cam_pos;
		D3D11_MAPPED_SUBRESOURCE vs_cbuffer;

		GetGraphics()->DeviceContext()->Map( _transform_matrices, 0, D3D11_MAP_WRITE_DISCARD, 0, &vs_cbuffer );
		
		memcpy( vs_cbuffer.pData, &vs_cbuffer_data, sizeof(TransformMatrices_cbuffer) );

		GetGraphics()->DeviceContext()->Unmap( _transform_matrices, 0 );

		ID3D11Buffer* vs_cbuffers[1] = { _transform_matrices };

		GetGraphics()->DeviceContext()->VSSetConstantBuffers( 0, 1, vs_cbuffers );

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

OldBasicMeshSystem::~OldBasicMeshSystem()
{
	if ( _input_layout )
	{
		_input_layout->Release();
	}
	if ( _transform_matrices )
	{
		_transform_matrices->Release();
	}
	if ( _depth_state )
	{
		_depth_state->Release();
	}
}