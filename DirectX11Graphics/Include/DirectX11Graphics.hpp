#pragma once

#ifndef _DIRECTX11GRAPHICS_DIRECTX11GRAPHICS_HPP_
#define _DIRECTX11GRAPHICS_DIRECTX11GRAPHICS_HPP_

#include "../../GameComponentInterfaces/Include/IGraphics.hpp"
#include "DirectX11Resources.hpp"
#include "ScreenBufferResources.hpp"
#include "../../Settings/Include/EngineSettings.hpp"
#include "../../GraphicsResources/Include/GraphicsImplementation.hpp"

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;
struct IDXGISwapChain;

namespace Fnd
{
namespace DirectX11Graphics
{

class CameraManagerSystem;

/**
	Base class for DX11 graphics implementations which handles creation of the back buffer and swap chain.
*/
class DirectX11Graphics:
	public Fnd::GraphicsResources::GraphicsImplementation
{
	public:

		// Default Constructor.
		DirectX11Graphics();
				
		// Get the device.
		ID3D11Device* Device() const;
		
		// Get the immediate device context.
		ID3D11DeviceContext* DeviceContext() const;

		// Get the screen width.
		unsigned int GetScreenWidth() const;
		
		// Get the screen height.
		unsigned int GetScreenHeight() const;
		
		// Get a new deferred device context.
		// Returned Context must be released before device is destroyed.
		ID3D11DeviceContext* GetNewDeferredDeviceContext() const;
		
		// Get the back buffer render target.
		ID3D11RenderTargetView* BackBuffer() const;
		
		// Get the swap chain.
		IDXGISwapChain* SwapChain() const;
		
		// Destructor.
		virtual ~DirectX11Graphics();
		
		/*
			Methods inherited from IGraphics.
		*/
		bool VRIsSupported();

		// Initialise the Graphics.
		// Returns true if successful.
		bool Initialise();
				
		// Render the scene.
		void BeginRender();
		
		// Present the backbuffer to the screen.
		void Present();

		void Release();
		
		// Resize the Graphics.
		// Called from the Game class when the Window has resized.
		void Resize( unsigned int width, unsigned int height );

		void MakeFullscreen( bool fullscreen );

		std::vector<std::shared_ptr<Fnd::EntitySystem::System>> GetSystems();

		Fnd::AssetManager::Texture2D* GetNewTexture2D();
		Fnd::AssetManager::Model* GetNewModel();
				
		Fnd::GameComponentInterfaces::IGraphics::OculusDataD3D11 GetOculusDataD3D11();

		DirectX11Resources& GetResources();
		
		ScreenBufferResources* GetScreenBufferResources( unsigned int id );

		/*
			Methods inherited from GraphicsImplementation.
		*/
		bool AddScreenBufferResources( unsigned int id, unsigned int width, unsigned int height );

	protected:

		/*
			Methods inherited from GraphicsImplementation.
		*/
		void OnSetOculusData( const Fnd::GameComponentInterfaces::IGraphics::OculusData& oculus_data );
				
	private:

		bool _is_initialised;
			
		ID3D11Device* _device;
		
		ID3D11DeviceContext* _immediate_device_context;
				
		IDXGISwapChain* _swap_chain;
		ID3D11RenderTargetView* _back_buffer;

		ID3D11Texture2D* _vr_eye_texture;
		ID3D11ShaderResourceView* _vr_eye_sr;
		ID3D11RenderTargetView* _vr_eye_rt;
		struct OculusBlit_cbuffer
		{
			Fnd::Math::Vector2 lefteye_pos;
			Fnd::Math::Vector2 righteye_pos;
		};
		ID3D11Buffer* _oculus_blit_cbuffer;

		DirectX11Resources _resources;
};

}
}


#endif