#include "../Include/ScreenBufferResources.hpp"

#include "../Include/DirectX11GraphicsBase.hpp"

using namespace Fnd::DirectX11Graphics;

ScreenBufferResources::ScreenBufferResources( DirectX11GraphicsBase* graphics ):
	_graphics(graphics),
	_width(0),
	_height(0),
	_GBuffer0_rt(nullptr),
	_GBuffer1_rt(nullptr),
	_GBuffer2_rt(nullptr),
	_GBuffer3_rt(nullptr),
	_GBuffer0_sr(nullptr),
	_GBuffer1_sr(nullptr),
	_GBuffer2_sr(nullptr),
	_GBuffer3_sr(nullptr),
	_GBuffer_ds(nullptr),
	_LBuffer_rt(nullptr),
	_LBuffer_sr(nullptr),
	_LBuffer_tex(nullptr),
	_AOBuffer_rt(nullptr),
	_AOBuffer_sr(nullptr),
	_position_reconstruction_cbuffer(nullptr)
{
}

ScreenBufferResources::~ScreenBufferResources()
{
	ReleaseResources();

	// This is not recreated when resized, just updated with the new dimensions
	if ( _position_reconstruction_cbuffer )
	{
		_position_reconstruction_cbuffer->Release();
		_position_reconstruction_cbuffer = nullptr;
	}
}

bool ScreenBufferResources::Initialise( unsigned int w, unsigned int h )
{
	_width = w;
	_height = h;

	if ( !CreateResources() )
	{
		return false;
	}

	PositionReconstruction_cbuffer data;
	data.screen_size = Fnd::Math::Vector2( (float)w, (float)h );
	data.aspect_ratio = ((float)w) / ((float)h);
	data.tan_half_fov_y = 0;	// requires the first CameraManagerSystem::Update() to get the correct value

	UpdatePositionReconstructionData(data);

	return true;
}

bool ScreenBufferResources::Resize( unsigned int w, unsigned int h )
{
	_width = w;
	_height = h;

	ReleaseResources();
	
	if ( !CreateResources() )
	{
		return false;
	}

	auto data = GetPositionReconstructionData();
	data.screen_size = Fnd::Math::Vector2( (float)w, (float)h );
	data.aspect_ratio = ((float)w) / ((float)h);

	UpdatePositionReconstructionData(data);

	return true;
}

unsigned int ScreenBufferResources::GetWidth() const
{
	return _width;
}

unsigned int ScreenBufferResources::GetHeight() const
{
	return _height;
}

ID3D11RenderTargetView* ScreenBufferResources::GetGBuffer0_rt()
{
	return _GBuffer0_rt;
}

ID3D11RenderTargetView* ScreenBufferResources::GetGBuffer1_rt()
{
	return _GBuffer1_rt;
}

ID3D11RenderTargetView* ScreenBufferResources::GetGBuffer2_rt()
{
	return _GBuffer2_rt;
}

ID3D11RenderTargetView* ScreenBufferResources::GetGBuffer3_rt()
{
	return _GBuffer3_rt;
}


ID3D11ShaderResourceView*  ScreenBufferResources::GetGBuffer0_sr()
{
	return _GBuffer0_sr;
}

ID3D11ShaderResourceView* ScreenBufferResources::GetGBuffer1_sr()
{
	return _GBuffer1_sr;
}

ID3D11ShaderResourceView* ScreenBufferResources::GetGBuffer2_sr()
{
	return _GBuffer2_sr;
}

ID3D11ShaderResourceView* ScreenBufferResources::GetGBuffer3_sr()
{
	return _GBuffer3_sr;
}

ID3D11DepthStencilView* ScreenBufferResources::GetGBuffer_ds()
{
	return _GBuffer_ds;
}

ID3D11RenderTargetView* ScreenBufferResources::GetLBuffer_rt()
{
	return _LBuffer_rt;
}
	
ID3D11ShaderResourceView* ScreenBufferResources::GetLBuffer_sr()
{
	return _LBuffer_sr;
}

ID3D11Texture2D* ScreenBufferResources::GetLBuffer_tex()
{
	return _LBuffer_tex;
}

ID3D11RenderTargetView* ScreenBufferResources::GetAOBuffer_rt()
{
	return _AOBuffer_rt;
}

ID3D11ShaderResourceView* ScreenBufferResources::GetAOBuffer_sr()
{
	return _AOBuffer_sr;
}

ScreenBufferResources::PositionReconstruction_cbuffer ScreenBufferResources::GetPositionReconstructionData() const
{
	return _position_reconstruction_data;
}

bool ScreenBufferResources::UpdatePositionReconstructionData( const ScreenBufferResources::PositionReconstruction_cbuffer& data )
{
	bool equal = 
		( data.screen_size.x == _position_reconstruction_data.screen_size.x ) &&
		( data.screen_size.y == _position_reconstruction_data.screen_size.y ) &&
		( data.aspect_ratio == _position_reconstruction_data.aspect_ratio ) &&
		( data.tan_half_fov_y == _position_reconstruction_data.tan_half_fov_y );

	if ( !equal )
	{
		_position_reconstruction_data = data;

		D3D11_MAPPED_SUBRESOURCE cbuffer;

		_graphics->DeviceContext()->Map( _position_reconstruction_cbuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &cbuffer );

		memcpy( cbuffer.pData, &_position_reconstruction_data, sizeof(PositionReconstruction_cbuffer) );

		_graphics->DeviceContext()->Unmap( _position_reconstruction_cbuffer, 0 );
	}

	return !equal;
}

ID3D11Buffer* ScreenBufferResources::GetPositionReconstructionBuffer()
{
	return _position_reconstruction_cbuffer;
}

void ScreenBufferResources::ReleaseResources()
{
	if ( _GBuffer0_rt )
	{
		_GBuffer0_rt->Release();
		_GBuffer0_rt = nullptr;
	}
	if ( _GBuffer1_rt )
	{
		_GBuffer1_rt->Release();
		_GBuffer1_rt = nullptr;
	}
	if ( _GBuffer2_rt )
	{
		_GBuffer2_rt->Release();
		_GBuffer2_rt = nullptr;
	}
	if ( _GBuffer3_rt )
	{
		_GBuffer3_rt->Release();
		_GBuffer3_rt = nullptr;
	}

	if ( _GBuffer0_sr )
	{
		_GBuffer0_sr->Release();
		_GBuffer0_sr = nullptr;
	}
	if ( _GBuffer1_sr )
	{
		_GBuffer1_sr->Release();
		_GBuffer1_sr = nullptr;
	}
	if ( _GBuffer2_sr )
	{
		_GBuffer2_sr->Release();
		_GBuffer2_sr = nullptr;
	}
	if ( _GBuffer3_sr )
	{
		_GBuffer3_sr->Release();
		_GBuffer3_sr = nullptr;
	}

	if ( _GBuffer_ds )
	{
		_GBuffer_ds->Release();
		_GBuffer_ds = nullptr;
	}

	if ( _LBuffer_rt )
	{
		_LBuffer_rt->Release();
		_LBuffer_rt = nullptr;
	}
	if ( _LBuffer_sr )
	{
		_LBuffer_sr->Release();
		_LBuffer_sr = nullptr;
	}
	if ( _LBuffer_tex )
	{
		_LBuffer_tex->Release();
		_LBuffer_tex = nullptr;
	}

	if ( _AOBuffer_rt )
	{
		_AOBuffer_rt->Release();
		_AOBuffer_rt = nullptr;
	}
	if ( _AOBuffer_sr )
	{
		_AOBuffer_sr->Release();
		_AOBuffer_sr = nullptr;
	}
}

bool ScreenBufferResources::CreateResources()
{
	/*
		GB0
	*/
	{
		ID3D11Texture2D* tex = nullptr;

		D3D11_TEXTURE2D_DESC tex_desc;
		tex_desc.Width = _width;
		tex_desc.Height = _height;
		tex_desc.MipLevels = 1;
		tex_desc.ArraySize = 1;
		tex_desc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
		tex_desc.SampleDesc.Count = 1;
		tex_desc.SampleDesc.Quality = 0;
		tex_desc.Usage = D3D11_USAGE_DEFAULT;
		tex_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		tex_desc.CPUAccessFlags = 0;
		tex_desc.MiscFlags = 0;

		if ( FAILED( _graphics->Device()->CreateTexture2D( &tex_desc, nullptr, &tex ) ) )
		{
			return false;
		}

		D3D11_RENDER_TARGET_VIEW_DESC rt_desc;
		rt_desc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
		rt_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rt_desc.Texture2D.MipSlice = 0;

		if ( FAILED( _graphics->Device()->CreateRenderTargetView( tex, &rt_desc, &_GBuffer0_rt ) ) )
		{
			return false;
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC sr_desc;
		sr_desc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
		sr_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		sr_desc.Texture2D.MostDetailedMip = 0;
		sr_desc.Texture2D.MipLevels = 1;

		if ( FAILED( _graphics->Device()->CreateShaderResourceView( tex, &sr_desc, &_GBuffer0_sr ) ) )
		{
			return false;
		}

		tex->Release();
	}

	/*
		GB1
	*/
	{
		ID3D11Texture2D* tex = nullptr;

		D3D11_TEXTURE2D_DESC tex_desc;
		tex_desc.Width = _width;
		tex_desc.Height = _height;
		tex_desc.MipLevels = 1;
		tex_desc.ArraySize = 1;
		tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		tex_desc.SampleDesc.Count = 1;
		tex_desc.SampleDesc.Quality = 0;
		tex_desc.Usage = D3D11_USAGE_DEFAULT;
		tex_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		tex_desc.CPUAccessFlags = 0;
		tex_desc.MiscFlags = 0;

		if ( FAILED( _graphics->Device()->CreateTexture2D( &tex_desc, nullptr, &tex ) ) )
		{
			return false;
		}

		D3D11_RENDER_TARGET_VIEW_DESC rt_desc;
		rt_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		rt_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rt_desc.Texture2D.MipSlice = 0;

		if ( FAILED( _graphics->Device()->CreateRenderTargetView( tex, &rt_desc, &_GBuffer1_rt ) ) )
		{
			return false;
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC sr_desc;
		sr_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sr_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		sr_desc.Texture2D.MostDetailedMip = 0;
		sr_desc.Texture2D.MipLevels = 1;

		if ( FAILED( _graphics->Device()->CreateShaderResourceView( tex, &sr_desc, &_GBuffer1_sr ) ) )
		{
			return false;
		}

		tex->Release();
	}

	/*
		GB2
	*/
	{
		ID3D11Texture2D* tex = nullptr;

		D3D11_TEXTURE2D_DESC tex_desc;
		tex_desc.Width = _width;
		tex_desc.Height = _height;
		tex_desc.MipLevels = 1;
		tex_desc.ArraySize = 1;
		tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		tex_desc.SampleDesc.Count = 1;
		tex_desc.SampleDesc.Quality = 0;
		tex_desc.Usage = D3D11_USAGE_DEFAULT;
		tex_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		tex_desc.CPUAccessFlags = 0;
		tex_desc.MiscFlags = 0;

		if ( FAILED( _graphics->Device()->CreateTexture2D( &tex_desc, nullptr, &tex ) ) )
		{
			return false;
		}

		D3D11_RENDER_TARGET_VIEW_DESC rt_desc;
		rt_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		rt_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rt_desc.Texture2D.MipSlice = 0;

		if ( FAILED( _graphics->Device()->CreateRenderTargetView( tex, &rt_desc, &_GBuffer2_rt ) ) )
		{
			return false;
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC sr_desc;
		sr_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sr_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		sr_desc.Texture2D.MostDetailedMip = 0;
		sr_desc.Texture2D.MipLevels = 1;

		if ( FAILED( _graphics->Device()->CreateShaderResourceView( tex, &sr_desc, &_GBuffer2_sr ) ) )
		{
			return false;
		}

		tex->Release();
	}

	/*
		GB3 - currently unused (motion vectors)
	*/
	{
		ID3D11Texture2D* tex = nullptr;

		D3D11_TEXTURE2D_DESC tex_desc;
		tex_desc.Width = _width;
		tex_desc.Height = _height;
		tex_desc.MipLevels = 1;
		tex_desc.ArraySize = 1;
		tex_desc.Format = DXGI_FORMAT_R16G16_FLOAT;
		tex_desc.SampleDesc.Count = 1;
		tex_desc.SampleDesc.Quality = 0;
		tex_desc.Usage = D3D11_USAGE_DEFAULT;
		tex_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		tex_desc.CPUAccessFlags = 0;
		tex_desc.MiscFlags = 0;

		if ( FAILED( _graphics->Device()->CreateTexture2D( &tex_desc, nullptr, &tex ) ) )
		{
			return false;
		}

		D3D11_RENDER_TARGET_VIEW_DESC rt_desc;
		rt_desc.Format = DXGI_FORMAT_R16G16_FLOAT;
		rt_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rt_desc.Texture2D.MipSlice = 0;

		if ( FAILED( _graphics->Device()->CreateRenderTargetView( tex, &rt_desc, &_GBuffer3_rt ) ) )
		{
			return false;
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC sr_desc;
		sr_desc.Format = DXGI_FORMAT_R16G16_FLOAT;
		sr_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		sr_desc.Texture2D.MostDetailedMip = 0;
		sr_desc.Texture2D.MipLevels = 1;

		if ( FAILED( _graphics->Device()->CreateShaderResourceView( tex, &sr_desc, &_GBuffer3_sr ) ) )
		{
			return false;
		}

		tex->Release();
	}

	/*
		Depth stencil
	*/
	{	
		ID3D11Texture2D* tex = nullptr;

		D3D11_TEXTURE2D_DESC tex_desc;
		tex_desc.Width = _width;
		tex_desc.Height = _height;
		tex_desc.MipLevels = 1;
		tex_desc.ArraySize = 1;
		tex_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		tex_desc.SampleDesc.Count = 1;
		tex_desc.SampleDesc.Quality = 0;
		tex_desc.Usage = D3D11_USAGE_DEFAULT;
		tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		tex_desc.CPUAccessFlags = 0;
		tex_desc.MiscFlags = 0;

		if ( FAILED( _graphics->Device()->CreateTexture2D( &tex_desc, nullptr, &tex ) ) )
		{
			return false;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC ds_desc;
		ds_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		ds_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		ds_desc.Flags = 0;
		ds_desc.Texture2D.MipSlice = 0;

		if ( FAILED( _graphics->Device()->CreateDepthStencilView( tex, &ds_desc, &_GBuffer_ds ) ) )
		{
			return false;
		}

		tex->Release();
	}

	/*
		LBuffer
	*/
	{	
		D3D11_TEXTURE2D_DESC tex_desc;
		tex_desc.Width = _width;
		tex_desc.Height = _height;
		tex_desc.MipLevels = 1;
		tex_desc.ArraySize = 1;
		tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		tex_desc.SampleDesc.Count = 1;
		tex_desc.SampleDesc.Quality = 0;
		tex_desc.Usage = D3D11_USAGE_DEFAULT;
		tex_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		tex_desc.CPUAccessFlags = 0;
		tex_desc.MiscFlags = 0;

		if ( FAILED( _graphics->Device()->CreateTexture2D( &tex_desc, nullptr, &_LBuffer_tex ) ) )
		{
			return false;
		}

		D3D11_RENDER_TARGET_VIEW_DESC rt_desc;
		rt_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		rt_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rt_desc.Texture2D.MipSlice = 0;

		if ( FAILED( _graphics->Device()->CreateRenderTargetView( _LBuffer_tex, &rt_desc, &_LBuffer_rt ) ) )
		{
			return false;
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC sr_desc;
		sr_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sr_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		sr_desc.Texture2D.MostDetailedMip = 0;
		sr_desc.Texture2D.MipLevels = 1;

		if ( FAILED( _graphics->Device()->CreateShaderResourceView( _LBuffer_tex, &sr_desc, &_LBuffer_sr ) ) )
		{
			return false;
		}
	}

	/*
		AOBuffer
	*/
	{	
		ID3D11Texture2D* tex = nullptr;

		D3D11_TEXTURE2D_DESC tex_desc;
		tex_desc.Width = _width;
		tex_desc.Height = _height;
		tex_desc.MipLevels = 1;
		tex_desc.ArraySize = 1;
		tex_desc.Format = DXGI_FORMAT_R8_UNORM;
		tex_desc.SampleDesc.Count = 1;
		tex_desc.SampleDesc.Quality = 0;
		tex_desc.Usage = D3D11_USAGE_DEFAULT;
		tex_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		tex_desc.CPUAccessFlags = 0;
		tex_desc.MiscFlags = 0;

		if ( FAILED( _graphics->Device()->CreateTexture2D( &tex_desc, nullptr, &tex ) ) )
		{
			return false;
		}

		D3D11_RENDER_TARGET_VIEW_DESC rt_desc;
		rt_desc.Format = DXGI_FORMAT_R8_UNORM;
		rt_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rt_desc.Texture2D.MipSlice = 0;

		if ( FAILED( _graphics->Device()->CreateRenderTargetView( tex, &rt_desc, &_AOBuffer_rt ) ) )
		{
			return false;
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC sr_desc;
		sr_desc.Format = DXGI_FORMAT_R8_UNORM;
		sr_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		sr_desc.Texture2D.MostDetailedMip = 0;
		sr_desc.Texture2D.MipLevels = 1;

		if ( FAILED( _graphics->Device()->CreateShaderResourceView( tex, &sr_desc, &_AOBuffer_sr ) ) )
		{
			return false;
		}

		tex->Release();
	}

	// Doesn't need recreating, just updating if it already exists
	if ( !_position_reconstruction_cbuffer )
	{
		D3D11_BUFFER_DESC cbuffer_desc;
		cbuffer_desc.ByteWidth = sizeof(PositionReconstruction_cbuffer);
		cbuffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		cbuffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbuffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbuffer_desc.MiscFlags = 0;
		cbuffer_desc.StructureByteStride = sizeof(PositionReconstruction_cbuffer);

		if ( FAILED( _graphics->Device()->CreateBuffer( &cbuffer_desc, nullptr, &_position_reconstruction_cbuffer ) ) )
		{
			return false;
		}
	}

	return true;
}