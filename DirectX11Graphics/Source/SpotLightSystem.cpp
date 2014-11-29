#include "../Include/SpotLightSystem.hpp"

using namespace Fnd::DirectX11Graphics;
using namespace Fnd::EntitySystem;
using namespace Fnd::Math;

SpotLightSystem::SpotLightSystem( DirectX11GraphicsBase* graphics ):
	DirectX11GraphicsSystem("SpotLightSystem",graphics),
	_input_layout(nullptr),
	_transform_cbuffer(nullptr),
	_spot_light_buffer(nullptr)
{
}

bool SpotLightSystem::Initialise()
{
	{
		std::string vs_shader_filename = GetGraphics()->GetResources().GetPipelineData("SpotLight").vertex_shader;

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
		cbuffer_desc.ByteWidth = sizeof(SpotLightData_cbuffer);
		cbuffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		cbuffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbuffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbuffer_desc.MiscFlags = 0;
		cbuffer_desc.StructureByteStride = sizeof(SpotLightData_cbuffer);

		if ( FAILED( GetGraphics()->Device()->CreateBuffer( &cbuffer_desc, nullptr, &_spot_light_buffer ) ) )
		{
			return false;
		}
	}

	return true;
}

void SpotLightSystem::OnUpdate( const Fnd::CommonResources::FrameData& frame_data )
{
	/*
		IA
	*/
	GetGraphics()->DeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	GetGraphics()->DeviceContext()->IASetInputLayout( _input_layout );

	/*
		VS
	*/
	GetGraphics()->DeviceContext()->VSSetShader( GetGraphics()->GetResources().GetShaders("SpotLight").vs, nullptr, 0 );

	/*
		PS
	*/
	GetGraphics()->DeviceContext()->PSSetShader( GetGraphics()->GetResources().GetShaders("SpotLight").ps, nullptr, 0 );

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

		ID3D11ShaderResourceView* ps_srs[4] = {	((ScreenBufferResources*)camera_data.screenbuffer)->GetGBuffer0_sr(),
												((ScreenBufferResources*)camera_data.screenbuffer)->GetGBuffer1_sr(),
												((ScreenBufferResources*)camera_data.screenbuffer)->GetGBuffer2_sr(),
												((ScreenBufferResources*)camera_data.screenbuffer)->GetGBuffer3_sr() };

		GetGraphics()->DeviceContext()->PSSetShaderResources( 0, 4, ps_srs );

		for ( auto light_iter = GetEntitySystem().GetSystemNodesContainer().GetNodeMap<SpotLightNode>().begin(); light_iter != GetEntitySystem().GetSystemNodesContainer().GetNodeMap<SpotLightNode>().end(); ++light_iter )
		{
			SpotLightNode::Pointers spotlight_components;
			if ( !light_iter->second.GetPointers( GetEntitySystem(), spotlight_components ) )
			{
				continue;
			}

			auto mesh = GetGraphics()->GetResources().GetMesh("LightCone");

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
			float radius = spotlight_components.spotlight->data.range * tan( ToRadians( spotlight_components.spotlight->data.fov ) / 2 ) / 2;

			Matrix4 world_matrix = Matrix4Helper<>::CreateScaleMatrix( radius, radius, spotlight_components.spotlight->data.range ) * spotlight_components.scenenode->data.transform;
			Vector3 world_position = Vector3( world_matrix.m30, world_matrix.m31, world_matrix.m32 );
			Vector3 world_direction = normalise( Vector3( world_matrix.m20, world_matrix.m21, world_matrix.m22 ) );

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
		
			GetGraphics()->DeviceContext()->Map( _spot_light_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &lightbuffer_res );

			((SpotLightData_cbuffer*)(lightbuffer_res.pData))->light_view_position = Matrix4Helper<>::TransformPosition( world_position, view_matrix );
			((SpotLightData_cbuffer*)(lightbuffer_res.pData))->light_range = spotlight_components.spotlight->data.range;
			((SpotLightData_cbuffer*)(lightbuffer_res.pData))->light_centre_direction = Matrix4Helper<>::TransformDirection( world_direction, view_matrix );
			((SpotLightData_cbuffer*)(lightbuffer_res.pData))->light_near_plane = spotlight_components.spotlight->data.near_plane;
			((SpotLightData_cbuffer*)(lightbuffer_res.pData))->light_colour = spotlight_components.spotlight->data.colour;
			((SpotLightData_cbuffer*)(lightbuffer_res.pData))->light_fov = ToRadians( spotlight_components.spotlight->data.fov );
			((SpotLightData_cbuffer*)(lightbuffer_res.pData))->distance_falloff_start = spotlight_components.spotlight->data.distance_falloff_start;
			((SpotLightData_cbuffer*)(lightbuffer_res.pData))->angular_falloff_start = spotlight_components.spotlight->data.angular_falloff_start;
			((SpotLightData_cbuffer*)(lightbuffer_res.pData))->light_size = 0;
			((SpotLightData_cbuffer*)(lightbuffer_res.pData))->distance_falloff_control_points = spotlight_components.spotlight->data.distance_falloff_params;
			((SpotLightData_cbuffer*)(lightbuffer_res.pData))->angular_falloff_control_points = spotlight_components.spotlight->data.angular_falloff_params;

			GetGraphics()->DeviceContext()->Unmap( _spot_light_buffer, 0 );

			ID3D11Buffer* ps_cbuffers[2] = { ((ScreenBufferResources*)camera_data.screenbuffer)->GetPositionReconstructionBuffer(), _spot_light_buffer };
			GetGraphics()->DeviceContext()->PSSetConstantBuffers( 0, 2, ps_cbuffers );

			/*
				OM
			*/

			// Prepass
			//GetGraphics()->DeviceContext()->OMSetDepthStencilState( GetGraphics()->GetResources().GetLightVolumePrePassDepthState(), 1 );
			//GetGraphics()->DeviceContext()->DrawIndexed( mesh.num_indices, 0, 0 );
			// end prepass

			//GetGraphics()->DeviceContext()->OMSetDepthStencilState( GetGraphics()->GetResources().GetLightVolumeLightPassDepthState(), 1 );
			
			ID3D11RenderTargetView* rts[1] = { ((ScreenBufferResources*)camera_data.screenbuffer)->GetLBuffer_rt() };

			GetGraphics()->DeviceContext()->OMSetRenderTargets( 1, rts, ((ScreenBufferResources*)camera_data.screenbuffer)->GetGBuffer_ds() );

			/*
				Draw
			*/
			GetGraphics()->DeviceContext()->DrawIndexed( mesh.num_indices, 0, 0 );
		}

	} );

	GetGraphics()->DeviceContext()->ClearState();
}

SpotLightSystem::~SpotLightSystem()
{
	if ( _input_layout )
	{
		_input_layout->Release();
	}

	if ( _transform_cbuffer )
	{
		_transform_cbuffer->Release();
	}

	if ( _spot_light_buffer )
	{
		_spot_light_buffer->Release();
	}
}