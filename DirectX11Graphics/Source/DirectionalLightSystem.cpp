#include "../Include/DirectionalLightSystem.hpp"

using namespace Fnd::DirectX11Graphics;
using namespace Fnd::EntitySystem;
using namespace Fnd::Math;

DirectionalLightSystem::DirectionalLightSystem( DirectX11GraphicsBase* graphics ):
	DirectX11GraphicsSystem("DirectionalLightSystem",graphics),
	_directional_light_buffer(nullptr)
{
}

bool DirectionalLightSystem::Initialise()
{
	{
		D3D11_BUFFER_DESC cbuffer_desc;
		cbuffer_desc.ByteWidth = sizeof(DirectionalLightData_cbuffer);
		cbuffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		cbuffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbuffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbuffer_desc.MiscFlags = 0;
		cbuffer_desc.StructureByteStride = sizeof(DirectionalLightData_cbuffer);

		if ( FAILED( GetGraphics()->Device()->CreateBuffer( &cbuffer_desc, nullptr, &_directional_light_buffer ) ) )
		{
			return false;
		}
	}

	return true;
}

void DirectionalLightSystem::OnUpdate( const Fnd::CommonResources::FrameData& frame_data )
{
	/*
		IA
	*/
	GetGraphics()->DeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	/*
		VS
	*/
	GetGraphics()->DeviceContext()->VSSetShader( GetGraphics()->GetResources().GetShaders("DirectionalLight").vs, nullptr, 0 );

	/*
		PS
	*/
	GetGraphics()->DeviceContext()->PSSetShader( GetGraphics()->GetResources().GetShaders("DirectionalLight").ps, nullptr, 0 );

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

		/*
			RS
		*/
		D3D11_VIEWPORT viewport = { 0, 0, (float)camera_data.screenbuffer->GetWidth(), (float)camera_data.screenbuffer->GetHeight(), 0, 1 };

		GetGraphics()->DeviceContext()->RSSetViewports( 1, &viewport );

		/*
			PS
		*/
		ID3D11ShaderResourceView* ps_srs[4] = {	camera_data.screenbuffer->GetGBuffer0_sr(),
												camera_data.screenbuffer->GetGBuffer1_sr(),
												camera_data.screenbuffer->GetGBuffer2_sr(),
												camera_data.screenbuffer->GetGBuffer3_sr() };

		GetGraphics()->DeviceContext()->PSSetShaderResources( 0, 4, ps_srs );

		/*
			OM
		*/	
		ID3D11RenderTargetView* rts[1] = { camera_data.screenbuffer->GetLBuffer_rt() };

		GetGraphics()->DeviceContext()->OMSetRenderTargets( 1, rts, camera_data.screenbuffer->GetGBuffer_ds() );
	
		for ( auto light_iter = GetEntitySystem().GetSystemNodesContainer().GetNodeMap<DirectionalLightNode>().begin(); light_iter != GetEntitySystem().GetSystemNodesContainer().GetNodeMap<DirectionalLightNode>().end(); ++light_iter )
		{
			DirectionalLightNode::Pointers light_components;

			if ( !light_iter->second.GetPointers( GetEntitySystem(), light_components ) )
			{
				continue;
			}

			Matrix4 world_matrix = light_components.scenenode->data.transform;
			Vector3 world_light_direction = Vector3( world_matrix.m20, world_matrix.m21, world_matrix.m22 );

			Vector3 view_light_direction = Matrix4Helper<>::TransformDirection( world_light_direction, view_matrix );

			{
				D3D11_MAPPED_SUBRESOURCE data;

				GetGraphics()->DeviceContext()->Map( _directional_light_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data );

				((DirectionalLightData_cbuffer*)data.pData)->light_direction = view_light_direction;
				((DirectionalLightData_cbuffer*)data.pData)->light_colour = light_components.directionallight->data.colour;
				
				GetGraphics()->DeviceContext()->Unmap( _directional_light_buffer, 0 );
			}

			/*
				PS
			*/
			ID3D11Buffer* ps_cbuffers[2] = { camera_data.screenbuffer->GetPositionReconstructionBuffer(), _directional_light_buffer };
	 
			GetGraphics()->DeviceContext()->PSSetConstantBuffers( 0, 2, ps_cbuffers );

			/*
				Draw
			*/
			GetGraphics()->DeviceContext()->Draw( 6, 0 );

			
		}
	} );
	
	GetGraphics()->DeviceContext()->ClearState();
}

DirectionalLightSystem::~DirectionalLightSystem()
{
	if ( _directional_light_buffer )
	{
		_directional_light_buffer->Release();
	}
}