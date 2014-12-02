#pragma once

#ifndef _DIRECTX11GRAPHICS_SCREENBUFFERRESOURCES_HPP_
#define _DIRECTX11GRAPHICS_SCREENBUFFERRESOURCES_HPP_

#include "../../Math/Include/Math.hpp"

#include "../../GraphicsResources/Include/ScreenBufferResourcesBase.hpp"

#include <d3d11.h>


namespace Fnd
{
namespace DirectX11Graphics
{
class DirectX11Graphics;

class ScreenBufferResources:
	public Fnd::GraphicsResources::ScreenBufferResourcesBase
{
	public:

		ScreenBufferResources( DirectX11Graphics* graphics );
				
		/*
			Gbuffer
		*/
		ID3D11RenderTargetView* GetGBuffer0_rt();
		ID3D11RenderTargetView* GetGBuffer1_rt();
		ID3D11RenderTargetView* GetGBuffer2_rt();
		ID3D11RenderTargetView* GetGBuffer3_rt();

		ID3D11ShaderResourceView* GetGBuffer0_sr();
		ID3D11ShaderResourceView* GetGBuffer1_sr();
		ID3D11ShaderResourceView* GetGBuffer2_sr();
		ID3D11ShaderResourceView* GetGBuffer3_sr();

		ID3D11DepthStencilView* GetGBuffer_ds();

		/*
			LBuffer
		*/
		ID3D11RenderTargetView* GetLBuffer_rt();
		ID3D11ShaderResourceView* GetLBuffer_sr();
		ID3D11Texture2D* GetLBuffer_tex();

		/*
			AO buffer (half res) (blur must use an intermediate buffer stored in 'general resources')
		*/
		ID3D11RenderTargetView* GetAOBuffer_rt();
		ID3D11ShaderResourceView* GetAOBuffer_sr();


		ID3D11Buffer* GetPositionReconstructionBuffer();
		
		~ScreenBufferResources();

	protected:

		void OnUpdatePositionReconstructionData( const ScreenBufferResources::PositionReconstruction_cbuffer& data );

		void ReleaseResources();
		bool CreateResources();

	private:

		DirectX11Graphics* _graphics;

		ID3D11RenderTargetView* _GBuffer0_rt;
		ID3D11RenderTargetView* _GBuffer1_rt;
		ID3D11RenderTargetView* _GBuffer2_rt;
		ID3D11RenderTargetView* _GBuffer3_rt;

		ID3D11ShaderResourceView* _GBuffer0_sr;
		ID3D11ShaderResourceView* _GBuffer1_sr;
		ID3D11ShaderResourceView* _GBuffer2_sr;
		ID3D11ShaderResourceView* _GBuffer3_sr;

		ID3D11DepthStencilView* _GBuffer_ds;

		ID3D11RenderTargetView* _LBuffer_rt;
		ID3D11ShaderResourceView* _LBuffer_sr;
		ID3D11Texture2D* _LBuffer_tex;

		ID3D11RenderTargetView* _AOBuffer_rt;
		ID3D11ShaderResourceView* _AOBuffer_sr;

		ID3D11Buffer* _position_reconstruction_cbuffer;
};

}
}

#endif