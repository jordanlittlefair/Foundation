#pragma once

#ifndef _DX11GRAPHICS_BASE_HPP_
#define _DX11GRAPHICS_BASE_HPP_

#include "../../GameComponentInterfaces/Include/IGraphics.hpp"
#include "DirectX11Resources.hpp"
#include "ScreenBufferResources.hpp"
#include "../../Configuration/Include/Configuration.hpp"

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
class DirectX11GraphicsBase:
	public Fnd::GameComponentInterfaces::IGraphics
{
	public:

		// Default Constructor.
		DirectX11GraphicsBase();
		
		// Get the width of the screen.
		unsigned int GetWidth() const;
		
		// Get the height of the screen.
		unsigned int GetHeight() const;
		
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
		virtual ~DirectX11GraphicsBase();
		
		/*
			Methods inherited from IGraphics.
		*/
		
		// Sets a pointer to the IGraphicsMessageListener inferface of the Game component.
		// The derived Graphics class calls IGraphicsMessageListener methods to get data needed from the Game class.
		void SetGraphicsMessageListener( Fnd::GameComponentInterfaces::IGraphicsMessageListener* game );

		void SetConfig( const Fnd::Configuration::GraphicsConfig& config );

		void SetEntitySystem( Fnd::EntitySystem::EntitySystem* entity_system );

		void EnableVR( bool enable );

		bool VRIsEnabled() const;

		// Initialise the Graphics.
		// Returns true if successful.
		bool Initialise();
				
		// Render the scene.
		void Render();
		
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

		void SetActiveCamera( unsigned int i, unsigned int j );
		
		void SetOculusData( const Fnd::GameComponentInterfaces::IGraphics::OculusData& oculus_data );
		Fnd::GameComponentInterfaces::IGraphics::OculusDataD3D11 GetOculusDataD3D11();
		Fnd::GameComponentInterfaces::IGraphics::OculusDataOpenGL GetOculusDataOpenGL();

		void UpdateVRCameraOffsets( const CameraOffsets& camera_offsets );

		DirectX11Resources& GetResources();

		bool AddScreenBufferResources( unsigned int id, unsigned int width, unsigned int height );

		ScreenBufferResources* GetScreenBufferResources( unsigned int id );
			
	protected:
	
		/*
			Virtual methods to be implemented in derived Graphics classes.
		*/
		
		// Called when Graphics is initialised.
		virtual bool OnInitialise() = 0;

		// Called when Graphics is resized.
		virtual void OnResize( unsigned int width, unsigned int height ) = 0;
				
		// Called when Graphics is rendered.
		virtual void OnRender() = 0;
		
	private:

		bool _is_initialised;

		bool _vr_enabled;
	
		Fnd::GameComponentInterfaces::IGraphicsMessageListener* _game;
		
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
		OculusData _oculus_data;
		float _lefteye_fov;
		float _righteye_fov;
				
		// Width of the screen.
		unsigned int _width;
		
		// Height of the screen.
		unsigned int _height;

		Fnd::Configuration::GraphicsConfig _config;
		Fnd::EntitySystem::EntitySystem* _entity_system;
		DirectX11Resources _resources;

		unsigned int _active_camera_primary;
		unsigned int _active_camera_secondary;

		std::map<unsigned int,std::shared_ptr<ScreenBufferResources>> _screen_buffer_resources;

		std::shared_ptr<CameraManagerSystem> _camera_system;
};

}
}


#endif