#include "../Include/PointLightSystem.hpp"

using namespace Fnd::DirectX11Graphics;
using namespace Fnd::EntitySystem;
using namespace Fnd::Math;

PointLightSystem::PointLightSystem( DirectX11GraphicsBase* graphics ):
	DirectX11GraphicsSystem("PointLightSystem",graphics),
	_input_layout(nullptr),
	_transform_cbuffer(nullptr),
	_point_light_buffer(nullptr)
{
}

bool PointLightSystem::Initialise()
{
	{
		std::string vs_shader_filename = GetGraphics()->GetResources().GetPipelineData("PointLight").vertex_shader;

		std::vector<char> vs_bytecode;
	
		if ( !GetGraphics()->GetResources().GetBytecodeFromFile( vs_shader_filename, vs_bytecode ) )
		{
			return false;
		}

		D3D11_INPUT_ELEMENT_DESC layout_desc[1] = 
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		if ( !SUCCEEDED( GetGraphics()->Device()->CreateInputLayout(	layout_desc, 
																		1, 
																		&vs_bytecode[0], 
																		vs_bytecode.size(), 
																		&_input_layout ) ) )
		{
			return false;
		}
	}

	{
		D3D11_BUFFER_DESC cbuffer_desc;
		cbuffer_desc.ByteWidth = sizeof(TransformMatrices_cbuffer);
		cbuffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		cbuffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbuffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbuffer_desc.MiscFlags = 0;
		cbuffer_desc.StructureByteStride = sizeof(TransformMatrices_cbuffer);

		if ( FAILED( GetGraphics()->Device()->CreateBuffer( &cbuffer_desc, nullptr, &_transform_cbuffer ) ) )
		{
			return false;
		}
	}

	{
		D3D11_BUFFER_DESC cbuffer_desc;
		cbuffer_desc.ByteWidth = sizeof(PointLightData_cbuffer);
		cbuffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		cbuffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbuffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbuffer_desc.MiscFlags = 0;
		cbuffer_desc.StructureByteStride = sizeof(PointLightData_cbuffer);

		if ( FAILED( GetGraphics()->Device()->CreateBuffer( &cbuffer_desc, nullptr, &_point_light_buffer ) ) )
		{
			return false;
		}
	}

	return true;
}

void PointLightSystem::OnUpdate( const Fnd::CommonResources::FrameData& frame_data )
{
	/*
		IA
	*/
	GetGraphics()->DeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	GetGraphics()->DeviceContext()->IASetInputLayout( _input_layout );

	/*
		VS
	*/
	GetGraphics()->DeviceContext()->VSSetShader( GetGraphics()->GetResources().GetShaders("PointLight").vs, nullptr, 0 );

	/*
		PS
	*/
	GetGraphics()->DeviceContext()->PSSetShader( GetGraphics()->GetResources().GetShaders("PointLight").ps, nullptr, 0 );

	/*
		OM
	*/
	GetGraphics()->DeviceContext()->OMSetDepthStencilState( GetGraphics()->GetResources().GetLightQuadRenderDepthState(), 1 );

	GetGraphics()->DeviceContext()->OMSetBlendState( GetGraphics()->GetResources().GetAdditiveLightBlendState(), nullptr, ~0 );

	ForEachCamera( [this]( const CameraData& camera_data )
	{
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
			RS
		*/
		D3D11_VIEWPORT viewport = { 0, 0, (float)camera_data.screenbuffer->GetWidth(), (float)camera_data.screenbuffer->GetHeight(), 0, 1 };
		GetGraphics()->DeviceContext()->RSSetState( GetGraphics()->GetResources().GetLightQuadRasteriser() );
		GetGraphics()->DeviceContext()->RSSetViewports( 1, &viewport );

		/*
			PS
		*/

		ID3D11ShaderResourceView* ps_srs[4] = {	camera_data.screenbuffer->GetGBuffer0_sr(),
												camera_data.screenbuffer->GetGBuffer1_sr(),
												camera_data.screenbuffer->GetGBuffer2_sr(),
												camera_data.screenbuffer->GetGBuffer3_sr() };

		GetGraphics()->DeviceContext()->PSSetShaderResources( 0, 4, ps_srs );

		for ( auto light_iter = GetEntitySystem().GetSystemNodesContainer().GetNodeMap<PointLightNode>().begin(); light_iter != GetEntitySystem().GetSystemNodesContainer().GetNodeMap<PointLightNode>().end(); ++light_iter )
		{
			PointLightNode::Pointers pointlight_components;
			if ( !light_iter->second.GetPointers( GetEntitySystem(), pointlight_components ) )
			{
				continue;
			}

			auto mesh = GetGraphics()->GetResources().GetMesh("LightSphere");

			/*
				IA
			*/
			ID3D11Buffer* vbs[1] = { mesh.vertex_buffer };

			unsigned int strides[1] = { sizeof(EngineMesh::Vertex) };
			unsigned int offsets[1] = { 0 };

			GetGraphics()->DeviceContext()->IASetVertexBuffers( 0, 1, vbs, strides, offsets );

			GetGraphics()->DeviceContext()->IASetIndexBuffer( mesh.index_buffer, DXGI_FORMAT_R32_UINT, 0 );

			/*
				VS
			*/
			Matrix4 world_matrix = Matrix4Helper<>::CreateScaleMatrix( pointlight_components.pointlight->data.range ) * pointlight_components.scenenode->data.transform;
			Vector3 world_position = Vector3( world_matrix.m30, world_matrix.m31, world_matrix.m32 );

			D3D11_MAPPED_SUBRESOURCE vsbuffer_res;

			GetGraphics()->DeviceContext()->Map( _transform_cbuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &vsbuffer_res );

			((TransformMatrices_cbuffer*)(vsbuffer_res.pData))->world_view_proj_matrix = Matrix4::Transpose( world_matrix * view_proj_matrix );

			GetGraphics()->DeviceContext()->Unmap( _transform_cbuffer, 0 );
		
			ID3D11Buffer* vs_cbuffers[1] = { _transform_cbuffer };

			GetGraphics()->DeviceContext()->VSSetConstantBuffers( 0, 1, vs_cbuffers );

			/*
				PS
			*/
			D3D11_MAPPED_SUBRESOURCE lightbuffer_res;
		
			GetGraphics()->DeviceContext()->Map( _point_light_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &lightbuffer_res );

			((PointLightData_cbuffer*)(lightbuffer_res.pData))->light_position = Matrix4Helper<>::TransformPosition( world_position, view_matrix );
			((PointLightData_cbuffer*)(lightbuffer_res.pData))->range = pointlight_components.pointlight->data.range;
			((PointLightData_cbuffer*)(lightbuffer_res.pData))->colour = pointlight_components.pointlight->data.colour;
			((PointLightData_cbuffer*)(lightbuffer_res.pData))->distance_falloff_start = pointlight_components.pointlight->data.distance_falloff_start;
			((PointLightData_cbuffer*)(lightbuffer_res.pData))->distance_falloff_params = pointlight_components.pointlight->data.distance_falloff_params;

			GetGraphics()->DeviceContext()->Unmap( _point_light_buffer, 0 );

			ID3D11Buffer* ps_cbuffers[2] = { camera_data.screenbuffer->GetPositionReconstructionBuffer(), _point_light_buffer };
			GetGraphics()->DeviceContext()->PSSetConstantBuffers( 0, 2, ps_cbuffers );

			/*
				OM
			*/

			// Prepass
			//GetGraphics()->DeviceContext()->OMSetDepthStencilState( GetGraphics()->GetResources().GetLightVolumePrePassDepthState(), 1 );
			//GetGraphics()->DeviceContext()->DrawIndexed( mesh.num_indices, 0, 0 );
			// end prepass

			//GetGraphics()->DeviceContext()->OMSetDepthStencilState( GetGraphics()->GetResources().GetLightVolumeLightPassDepthState(), 1 );
			
			ID3D11RenderTargetView* rts[1] = { camera_data.screenbuffer->GetLBuffer_rt() };

			GetGraphics()->DeviceContext()->OMSetRenderTargets( 1, rts, camera_data.screenbuffer->GetGBuffer_ds() );

			/*
				Draw
			*/
			GetGraphics()->DeviceContext()->DrawIndexed( mesh.num_indices, 0, 0 );
		}

		
	}
	);
	
	GetGraphics()->DeviceContext()->ClearState();
}

PointLightSystem::~PointLightSystem()
{
	if ( _input_layout )
	{
		_input_layout->Release();
	}

	if ( _transform_cbuffer )
	{
		_transform_cbuffer->Release();
	}

	if ( _point_light_buffer )
	{
		_point_light_buffer->Release();
	}
}