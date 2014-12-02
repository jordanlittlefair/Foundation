#include "../Include/DirectX11Graphics.hpp"

#include <D3D11.h>

#include "../../GameComponentInterfaces/Include/IGraphicsMessageListener.hpp"

#include "../Include/DirectX11Texture2D.hpp"
#include "../Include/DirectX11Model.hpp"
#include "../../EntitySystem/Include/Components.hpp"
#include "../../EntitySystem/Include/Entity.hpp"
#include "../../EntitySystem/Include/ComponentMaps.hpp"
#include "../../EntitySystem/Include/EntitySystem.hpp"
#include "../../EntitySystem/Include/EntityContainer.hpp"
#include "../../EntitySystem/Include/SystemNodes.hpp"
#include "../../EntitySystem/Include/SystemNodesContainer.hpp"

#include "../Include/CameraManagerSystem.hpp"
#include "../Include/MeshSystem.hpp"
#include "../Include/AmbientLightSystem.hpp"
#include "../Include/DirectionalLightSystem.hpp"
#include "../Include/PointLightSystem.hpp"
#include "../Include/SpotLightSystem.hpp"

using namespace Fnd::DirectX11Graphics;
using namespace Fnd::EntitySystem;

DirectX11Graphics::DirectX11Graphics():	
	_is_initialised(false),
	_device(nullptr),
	_immediate_device_context(nullptr),
	_swap_chain(nullptr),
	_back_buffer(nullptr),
	_width(0),
	_height(0),
	_resources(this),
	_vr_eye_texture(nullptr),
	_vr_eye_sr(nullptr),
	_vr_eye_rt(nullptr),
	_oculus_blit_cbuffer(nullptr)
{
}

unsigned int DirectX11Graphics::GetWidth() const
{
	return _width;
}

unsigned int DirectX11Graphics::GetHeight() const
{
	return _height;
}

ID3D11Device* DirectX11Graphics::Device() const
{
	return _device;
}

ID3D11DeviceContext* DirectX11Graphics::DeviceContext() const
{
	return _immediate_device_context;
}

unsigned int DirectX11Graphics::GetScreenWidth() const
{
	return _width;
}
		
unsigned int DirectX11Graphics::GetScreenHeight() const
{
	return _height;
}

ID3D11DeviceContext* DirectX11Graphics::GetNewDeferredDeviceContext() const
{
	ID3D11DeviceContext* to_return = nullptr;

	if ( FAILED( _device->CreateDeferredContext( 0, &to_return ) ) )
	{
		//LogWarning( "F11", "Cannot create deferred device context; returning nullptr." );
		return nullptr;
	}

	return to_return;
}

ID3D11RenderTargetView* DirectX11Graphics::BackBuffer() const
{
	return _back_buffer;
}
		
IDXGISwapChain* DirectX11Graphics::SwapChain() const
{
	return _swap_chain;
}
		
DirectX11Graphics::~DirectX11Graphics()
{
	if ( !_is_initialised )
	{
		//LogWarning( "F11", "Cannot deinitialise F11Graphics; F11Graphics is not currently initialised." );
		return;
	}

	_swap_chain->SetFullscreenState( false, nullptr );
				
	if ( _swap_chain )
	{
		_swap_chain->Release();
		_swap_chain = nullptr;
	}
	
	if ( _back_buffer )
	{
		_back_buffer->Release();
		_back_buffer = nullptr;
	}

	if ( _immediate_device_context )
	{
		_immediate_device_context->Release();
		_immediate_device_context = nullptr;
	}

	if ( _device )
	{
		_device->Release();
		_device = nullptr;
	}

	if ( _vr_eye_texture )
	{
		_vr_eye_texture->Release();
		_vr_eye_texture = nullptr;
	}
	if ( _vr_eye_sr )
	{
		_vr_eye_sr->Release();
		_vr_eye_sr = nullptr;
	}
	if ( _vr_eye_rt )
	{
		_vr_eye_rt->Release();
		_vr_eye_rt = nullptr;
	}
	if ( _oculus_blit_cbuffer )
	{
		_oculus_blit_cbuffer->Release();
		_oculus_blit_cbuffer = nullptr;
	}
		
	_width = 0;
	_height = 0;

	_is_initialised = false;
}
		
bool DirectX11Graphics::VRIsSupported()
{
	return true;
}

bool DirectX11Graphics::Initialise()
{
	if ( _is_initialised )
	{
		//LogError( "F11", "Cannot initialise F11Graphics; F11Graphics is currently initialised." );
		return false;
	}

	// Return false if no game has been set.
	if ( !GetGame() )
	{
		//LogError( "F11", "Cannot initialise F11Graphics; F11Graphics has no graphics message listener set." );
		return false;
	}

	// Get the dimensions of the screen.

	RECT rectangle;
	GetClientRect( HWND(GetGame()->GetHWND()), &rectangle );

	unsigned int width = rectangle.right - rectangle.left;
	unsigned int height = rectangle.bottom - rectangle.top;

	if ( VRIsEnabled() )
	{	
		GetGame()->GetVRTextureDimensions( width, height );
	}

	// Use the default adapter and hardware drivers.

	IDXGIFactory* factory = nullptr;
	IDXGIAdapter* adapter = nullptr;

	auto f = CreateDXGIFactory( __uuidof(IDXGIFactory), (void**)&factory );

	auto a = factory->EnumAdapters( 0, &adapter );
	
	// Create a debug device if in debug mode.

#ifdef _DEBUG
	unsigned int device_flags = D3D11_CREATE_DEVICE_DEBUG;
#else
	unsigned int device_flags = 0;
#endif

	// Create a swap chain description.

	DXGI_SWAP_CHAIN_DESC swap_chain_desc;
	
	memset( &swap_chain_desc, 0, sizeof(swap_chain_desc) );
	swap_chain_desc.BufferDesc.Width = width;
	swap_chain_desc.BufferDesc.Height = height;
	swap_chain_desc.BufferDesc.RefreshRate.Numerator = 0;
	swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
	swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
	swap_chain_desc.SampleDesc.Count = 1;
	swap_chain_desc.SampleDesc.Quality = 0;
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_desc.BufferCount = 2;
	swap_chain_desc.OutputWindow = HWND(GetGame()->GetHWND());
	swap_chain_desc.Windowed = true;
	swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;
	swap_chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// Create the swap chain, device and immediate device context.
	
	if ( FAILED( D3D11CreateDevice(	adapter,
									adapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE,
									nullptr,
									device_flags,
									nullptr,
									0,
									D3D11_SDK_VERSION,
									&_device,
									nullptr,
									&_immediate_device_context ) ) )
	{
		//LogError( "F11", "Cannot initialise F11Graphics; cannot create device and swapchain." );
		return false;
	}

	if ( adapter )
	{
		adapter->Release();
	}

	if ( FAILED( factory->CreateSwapChain( _device, &swap_chain_desc, &_swap_chain ) ) )
	{
		return false;
	}
	ID3D11Texture2D* backbuffer = nullptr;
    HRESULT hr = _swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbuffer);
    if (FAILED(hr))
        return false;

    hr = _device->CreateRenderTargetView(backbuffer, nullptr, &_back_buffer);
    if (FAILED(hr))
        return false;

	_width = width;
	_height = height;

	if ( backbuffer )
	{
		backbuffer->Release();
	}

	if ( factory )
	{
		factory->Release();
	}

	if ( VRIsEnabled() )
	{
		{
			D3D11_BUFFER_DESC cbuffer_desc;
			cbuffer_desc.ByteWidth = sizeof(OculusBlit_cbuffer);
			cbuffer_desc.Usage = D3D11_USAGE_DYNAMIC;
			cbuffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbuffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			cbuffer_desc.MiscFlags = 0;
			cbuffer_desc.StructureByteStride = sizeof(OculusBlit_cbuffer);

			if ( FAILED( Device()->CreateBuffer( &cbuffer_desc, nullptr, &_oculus_blit_cbuffer ) ) )
			{
				return false;
			}
		}
		
		_swap_chain->SetFullscreenState( 1, nullptr );
	}


	if (0)
	{
		// Get the dxgi factory and disable fullscreen toggling with alt+enter.

		IDXGIDevice* dxgi_device = nullptr;
		if ( FAILED( _device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgi_device) ) )
		{
			//LogError( "F11", "Cannot initialise F11Graphics; cannot get DXGI device." );
			return false;
		}

		if ( FAILED( dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void **)&adapter) ) )
		{
			//LogError( "F11", "Cannot initialise F11Graphics; cannot get DXGI adapter." );
			return false;
		}

		IDXGIFactory * factory = nullptr;
		if ( FAILED( adapter->GetParent(__uuidof(IDXGIFactory), (void **)&factory) ) )
		{
			//LogError( "F11", "Cannot initialise F11Graphics; cannot get DXGI factory." );
			return false;
		}

		factory->MakeWindowAssociation( HWND(GetGame()->GetHWND()), DXGI_MWA_NO_WINDOW_CHANGES );

		dxgi_device->Release();
		adapter->Release();
		factory->Release();
	}
	
	// Create the back buffer by resizing
	//Resize( width, height );

	_resources.SetConfig(GetGraphicsSettings());
	if ( !_resources.Initialise() )
	{
		return false;
	}
		
	Resize( width, height );

	_is_initialised = true;
	
	return true;
}

void DirectX11Graphics::MakeFullscreen( bool fullscreen )
{
	/*DXGI_MODE_DESC new_mode;
	new_mode.Width = 1920;
	new_mode.Height = 1080;
	new_mode.RefreshRate.Numerator = 60;
	new_mode.RefreshRate.Denominator = 1;
	new_mode.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	new_mode.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	new_mode.Scaling = DXGI_MODE_SCALING_CENTERED;

	_swap_chain->ResizeTarget( &new_mode );*/
	//_swap_chain->SetFullscreenState( fullscreen, nullptr );
	
	//Resize( 1920, 1080 );

}
				
void DirectX11Graphics::BeginRender()
{
	// Clear the back buffer.
	float default_colour[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	_immediate_device_context->ClearRenderTargetView( _back_buffer, default_colour );
	
	for ( auto iter = GetScreenBufferResourcesBase().begin(); iter != GetScreenBufferResourcesBase().end(); ++iter )
	{
		DeviceContext()->ClearDepthStencilView( ((ScreenBufferResources*)iter->second.get())->GetGBuffer_ds(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0 );

		//DeviceContext()->ClearRenderTargetView( ((ScreenBufferResources*)iter->second.get())->GetGBuffer0_rt(), default_colour );
		//DeviceContext()->ClearRenderTargetView( ((ScreenBufferResources*)iter->second.get())->GetGBuffer1_rt(), default_colour );
		//DeviceContext()->ClearRenderTargetView( ((ScreenBufferResources*)iter->second.get())->GetGBuffer2_rt(), default_colour );
		//DeviceContext()->ClearRenderTargetView( ((ScreenBufferResources*)iter->second.get())->GetGBuffer3_rt(), default_colour );

		//DeviceContext()->ClearRenderTargetView( ((ScreenBufferResources*)iter->second.get())->GetAOBuffer_rt(), default_colour );

		DeviceContext()->ClearRenderTargetView( ((ScreenBufferResources*)iter->second.get())->GetLBuffer_rt(), default_colour );
	}
}

void DirectX11Graphics::Present()
{
	unsigned int chosen_camera = GetActiveCamera(Primary_ActiveCamera);

	CameraNode* camera_node = nullptr;

	for ( auto iter = GetEntitySystem()->GetSystemNodesContainer().GetNodeMap<CameraNode>().begin();
		iter != GetEntitySystem()->GetSystemNodesContainer().GetNodeMap<CameraNode>().end();
		++iter )
	{
		CameraNode::Pointers camera_components;

		if ( iter->second.GetPointers( *GetEntitySystem(), camera_components ) )
		{
			if ( camera_components.cameraproperties->data.camera_id == chosen_camera )
			{
				camera_node = &iter->second;
				break;
			}
		}
	}
	

	CameraNode::Pointers camera_components;

	if ( camera_node && camera_node->GetPointers( *GetEntitySystem(), camera_components ) )
	{
		DeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

		DeviceContext()->VSSetShader( _resources.GetShaders("Blit").vs, nullptr, 0 );

		D3D11_VIEWPORT viewport = { 0, 0, (float)_width, (float)_height, 0, 1 };

		DeviceContext()->RSSetViewports( 1, &viewport );

		DeviceContext()->PSSetShader( _resources.GetShaders("Blit").ps, nullptr, 0 );

		ID3D11ShaderResourceView* ps_srvs[1] = { GetScreenBufferResources(chosen_camera)->GetLBuffer_sr() };

		DeviceContext()->PSSetShaderResources( 0, 1, ps_srvs );

		ID3D11RenderTargetView* om_rts[1] = { BackBuffer() };

		DeviceContext()->OMSetRenderTargets( 1, om_rts, nullptr );

		DeviceContext()->Draw( 6, 0 );	

		DeviceContext()->ClearState();
	}
	else
	{
		float error_colour[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
		_immediate_device_context->ClearRenderTargetView( _back_buffer, error_colour );
	}

	if ( VRIsEnabled() )
	{
		float col[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
		this->_immediate_device_context->ClearRenderTargetView( _vr_eye_rt, col );

		DeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

		DeviceContext()->VSSetShader( _resources.GetShaders("OculusBlit").vs, nullptr, 0 );

		D3D11_VIEWPORT viewport = { 0, 0, (float)GetOculusData().lefteye_width+GetOculusData().righteye_width, (float)max(GetOculusData().lefteye_height,GetOculusData().righteye_height), 0, 1 };

		DeviceContext()->RSSetViewports( 1, &viewport );

		DeviceContext()->PSSetShader( _resources.GetShaders("OculusBlit").ps, nullptr, 0 );

		ID3D11ShaderResourceView* ps_srvs[2] = { GetScreenBufferResources(chosen_camera)->GetLBuffer_sr(), GetScreenBufferResources(chosen_camera+1)->GetLBuffer_sr() };

		DeviceContext()->PSSetShaderResources( 0, 2, ps_srvs );

		ID3D11Buffer* ps_cbuffers[1] = { _oculus_blit_cbuffer };

		DeviceContext()->PSSetConstantBuffers( 0, 1, ps_cbuffers );

		ID3D11RenderTargetView* om_rts[1] = { _vr_eye_rt };

		DeviceContext()->OMSetRenderTargets( 1, om_rts, nullptr );

		DeviceContext()->Draw( 6, 0 );	

		DeviceContext()->ClearState();

		return;
	}	

	_swap_chain->Present( 0, 0 );
}

void DirectX11Graphics::Resize( unsigned int width, unsigned int height )
{
	if ( VRIsEnabled() )
	{	
		GetGame()->GetVRTextureDimensions( width, height );
	}

	//std::stringstream ss;
	//ss << "Changing resolution to: " << width << " x " << height << std::endl;
	//Error::Log( ss.str() );
	// Don't do anything if the new size is the same as the old.
	if ( _width == width && _height == height )
	{
		return;
	}

	// If the width and height are zero, don't bother resizing, just wait until theres a new non zero size.
	if ( width == 0 || height == 0 )
	{
		return;
	}

	_width = width;
	_height = height;

	//return;
	// Release the current back buffer.
	if ( _back_buffer )
	{
		_back_buffer->Release();
	}



	
	// Resize the swap chain and create a new back buffer.
	_swap_chain->ResizeBuffers( 2, _width, _height, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH );

	ID3D11Texture2D* buffer = nullptr;

	_swap_chain->GetBuffer( 0, __uuidof(buffer), (void**)&buffer );

	_device->CreateRenderTargetView( buffer, nullptr, &_back_buffer );

	buffer->Release();

	for ( auto iter = GetScreenBufferResourcesBase().begin(); iter != GetScreenBufferResourcesBase().end(); ++iter )
	{
		iter->second->Resize( _width, _height );
	}
}

void DirectX11Graphics::Release()
{
}

Fnd::AssetManager::Texture2D* DirectX11Graphics::GetNewTexture2D()
{
	return new DirectX11Texture2D(this);
}

Fnd::AssetManager::Model* DirectX11Graphics::GetNewModel()
{
	return new DirectX11Model(this);
}

void DirectX11Graphics::OnSetOculusData( const Fnd::GameComponentInterfaces::IGraphics::OculusData& oculus_data )
{
	{
		D3D11_MAPPED_SUBRESOURCE data;

		DeviceContext()->Map( _oculus_blit_cbuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data );

		((OculusBlit_cbuffer*)data.pData)->lefteye_pos = Fnd::Math::Vector2( 0, 0 );
		((OculusBlit_cbuffer*)data.pData)->righteye_pos = Fnd::Math::Vector2( (float)oculus_data.lefteye_width, 0.0f );

		DeviceContext()->Unmap( _oculus_blit_cbuffer, 0 );
	}

	{
		D3D11_TEXTURE2D_DESC tex_desc;
		tex_desc.Width = oculus_data.lefteye_width + oculus_data.righteye_width;
		tex_desc.Height = oculus_data.lefteye_height;
		tex_desc.MipLevels = 1;
		tex_desc.ArraySize = 1;
		tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		tex_desc.SampleDesc.Count = 1;
		tex_desc.SampleDesc.Quality = 0;
		tex_desc.Usage = D3D11_USAGE_DEFAULT;
		tex_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		tex_desc.CPUAccessFlags = 0;
		tex_desc.MiscFlags = 0;

		if ( FAILED( Device()->CreateTexture2D( &tex_desc, nullptr, &_vr_eye_texture ) ) )
		{
			return;// false;
		}

		D3D11_RENDER_TARGET_VIEW_DESC rt_desc;
		rt_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		rt_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rt_desc.Texture2D.MipSlice = 0;

		if ( FAILED( Device()->CreateRenderTargetView( _vr_eye_texture, &rt_desc, &_vr_eye_rt ) ) )
		{
			return;// false;
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC sr_desc;
		sr_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sr_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		sr_desc.Texture2D.MostDetailedMip = 0;
		sr_desc.Texture2D.MipLevels = 1;

		if ( FAILED( Device()->CreateShaderResourceView( _vr_eye_texture, &sr_desc, &_vr_eye_sr ) ) )
		{
			return;// false;
		}
	}
	
	float col[4] = { 1, 0, 0, 1 };
	DeviceContext()->ClearRenderTargetView( _vr_eye_rt, col );

	//_swap_chain->SetFullscreenState( true, nullptr );
}

Fnd::GameComponentInterfaces::IGraphics::OculusDataD3D11 DirectX11Graphics::GetOculusDataD3D11()
{
	Fnd::GameComponentInterfaces::IGraphics::OculusDataD3D11 ret;
	
	ret.eye_tex = _vr_eye_texture;
	ret.eye_srv = _vr_eye_sr;
	
	ret.device = _device;
	ret.device_context = _immediate_device_context;
	ret.back_buffer_rt = _back_buffer;
	ret.swap_chain = _swap_chain;
	
	return ret;
}

DirectX11Resources& DirectX11Graphics::GetResources()
{
	return _resources;
}

bool DirectX11Graphics::AddScreenBufferResources( unsigned int id, unsigned int width, unsigned int height )
{
	if ( !GetScreenBufferResources(id) )
	{
		std::shared_ptr<ScreenBufferResources> srb( new ScreenBufferResources(this));

		if ( srb->Initialise( width, height ) )
		{
			GetScreenBufferResourcesBase().insert( std::make_pair( id, srb ) );

			return true;
		}
	}

	return false;
}

ScreenBufferResources* DirectX11Graphics::GetScreenBufferResources( unsigned int id )
{
	auto found = GetScreenBufferResourcesBase().find(id);

	if ( found != GetScreenBufferResourcesBase().end() )
	{
		return (ScreenBufferResources*)found->second.get();
	}
	else
	{
		return nullptr;
	}
}

std::vector<std::shared_ptr<Fnd::EntitySystem::System>> DirectX11Graphics::GetSystems()
{
	auto systems = std::vector<std::shared_ptr<Fnd::EntitySystem::System>>();

	CameraManagerSystem* camera_manager_system = new CameraManagerSystem( this );
	SetCameraManagerSystem( camera_manager_system, camera_manager_system );
	
	systems.push_back( (std::shared_ptr<Fnd::EntitySystem::System>)GetCameraManagerSystem() );
	systems.push_back( std::shared_ptr<MeshSystem>( new MeshSystem( this ) ) );
	systems.push_back( std::shared_ptr<AmbientLightSystem>( new AmbientLightSystem( this ) ) );
	systems.push_back( std::shared_ptr<DirectionalLightSystem>( new DirectionalLightSystem( this ) ) );
	systems.push_back( std::shared_ptr<PointLightSystem>( new PointLightSystem( this ) ) );
	systems.push_back( std::shared_ptr<SpotLightSystem>( new SpotLightSystem( this ) ) );

	return systems;
}