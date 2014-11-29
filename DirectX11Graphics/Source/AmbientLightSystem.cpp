#include "../Include/AmbientLightSystem.hpp"

using namespace Fnd::DirectX11Graphics;
using namespace Fnd::EntitySystem;
using namespace Fnd::Math;

AmbientLightSystem::AmbientLightSystem( DirectX11Graphics* graphics ):
	DirectX11GraphicsSystem("AmbientLightSystem",graphics),
	_ambient_light_buffer(nullptr)
{
}

bool AmbientLightSystem::Initialise()
{
	{
		D3D11_BUFFER_DESC cbuffer_desc;
		cbuffer_desc.ByteWidth = sizeof(AmbientLightData_cbuffer);
		cbuffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		cbuffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbuffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbuffer_desc.MiscFlags = 0;
		cbuffer_desc.StructureByteStride = sizeof(AmbientLightData_cbuffer);

		if ( FAILED( GetGraphics()->Device()->CreateBuffer( &cbuffer_desc, nullptr, &_ambient_light_buffer ) ) )
		{
			return false;
		}
	}

	return true;
}

void AmbientLightSystem::OnUpdate( const Fnd::CommonResources::FrameData& frame_data )
{
	Vector3 ambient_light_sum = Vector3::Zero();

	for ( auto ambient_light_node_iter = GetEntitySystem().GetSystemNodesContainer().GetNodeMap<AmbientLightNode>().begin(); 
		ambient_light_node_iter != GetEntitySystem().GetSystemNodesContainer().GetNodeMap<AmbientLightNode>().end(); 
		++ambient_light_node_iter )
	{
		AmbientLightNode::Pointers ambient_light_components;

		if ( !ambient_light_node_iter->second.GetPointers( GetEntitySystem(), ambient_light_components ) )
		{
			continue;
		}

		Vector3 ambient_light = ambient_light_components.ambientlight->data.colour;

		ambient_light_sum += ambient_light;
	}

	{
		D3D11_MAPPED_SUBRESOURCE data;

		GetGraphics()->DeviceContext()->Map( _ambient_light_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data );

		((AmbientLightData_cbuffer*)data.pData)->colour = ambient_light_sum;

		GetGraphics()->DeviceContext()->Unmap( _ambient_light_buffer, 0 );
	}

	/*
		IA
	*/
	GetGraphics()->DeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	/*
		VS
	*/
	GetGraphics()->DeviceContext()->VSSetShader( GetGraphics()->GetResources().GetShaders("AmbientLight").vs, nullptr, 0 );

	/*
		PS
	*/
	GetGraphics()->DeviceContext()->PSSetShader( GetGraphics()->GetResources().GetShaders("AmbientLight").ps, nullptr, 0 );

	/*
		OM
	*/
	GetGraphics()->DeviceContext()->OMSetDepthStencilState( GetGraphics()->GetResources().GetLightQuadRenderDepthState(), 1 );

	ForEachCamera( [this,ambient_light_sum]( const CameraData& camera_data )
	{
		/*
			RS
		*/
		D3D11_VIEWPORT viewport = { 0, 0, (float)camera_data.screenbuffer->GetWidth(), (float)camera_data.screenbuffer->GetHeight(), 0, 1 };

		GetGraphics()->DeviceContext()->RSSetViewports( 1, &viewport );

		/*
			PS
		*/
		ID3D11ShaderResourceView* ps_srs[4] = {	((ScreenBufferResources*)camera_data.screenbuffer)->GetGBuffer0_sr(),
												((ScreenBufferResources*)camera_data.screenbuffer)->GetGBuffer1_sr(),
												((ScreenBufferResources*)camera_data.screenbuffer)->GetGBuffer2_sr(),
												((ScreenBufferResources*)camera_data.screenbuffer)->GetGBuffer3_sr() };

		GetGraphics()->DeviceContext()->PSSetShaderResources( 0, 4, ps_srs );
		
		ID3D11Buffer* ps_cbuffers[2] = { ((ScreenBufferResources*)camera_data.screenbuffer)->GetPositionReconstructionBuffer(), _ambient_light_buffer };
	 
		GetGraphics()->DeviceContext()->PSSetConstantBuffers( 0, 2, ps_cbuffers );

		/*
			OM
		*/	
		ID3D11RenderTargetView* rts[1] = { ((ScreenBufferResources*)camera_data.screenbuffer)->GetLBuffer_rt() };

		GetGraphics()->DeviceContext()->OMSetRenderTargets( 1, rts, ((ScreenBufferResources*)camera_data.screenbuffer)->GetGBuffer_ds() );
	
		/*
			Draw
		*/
		GetGraphics()->DeviceContext()->Draw( 6, 0 );
	}
	);
	
	GetGraphics()->DeviceContext()->ClearState();
}

AmbientLightSystem::~AmbientLightSystem()
{
	if ( _ambient_light_buffer )
	{
		_ambient_light_buffer->Release();
	}
}