#pragma once

#ifndef _DIRECTX11GRAPHICS_SCREENBUFFERRESOURCES_HPP_
#define _DIRECTX11GRAPHICS_SCREENBUFFERRESOURCES_HPP_

#include "../../Math/Include/Math.hpp"

#include "../../GraphicsResources/Include/IScreenBufferResources.hpp"

#include <d3d11.h>


namespace Fnd
{
namespace DirectX11Graphics
{
class DirectX11GraphicsBase;

class ScreenBufferResources:
	public Fnd::GraphicsResources::IScreenBufferResources
{
	public:

		ScreenBufferResources( DirectX11GraphicsBase* graphics );

		bool Initialise( unsigned int w, unsigned int h );

		bool Resize( unsigned int w, unsigned int h );

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;

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

		struct PositionReconstruction_cbuffer
		{
			Fnd::Math::Vector2 screen_size;
			float aspect_ratio;
			float tan_half_fov_y;
		};
		PositionReconstruction_cbuffer GetPositionReconstructionData() const;
		bool UpdatePositionReconstructionData( const PositionReconstruction_cbuffer& data );

		ID3D11Buffer* GetPositionReconstructionBuffer();
		
		~ScreenBufferResources();

	private:

		DirectX11GraphicsBase* _graphics;

		unsigned int _width;
		unsigned int _height;

		void ReleaseResources();
		bool CreateResources();

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

		PositionReconstruction_cbuffer _position_reconstruction_data;
		ID3D11Buffer* _position_reconstruction_cbuffer;
};

}
}

#endif