#pragma once

#ifndef _DIRECTX11GRAPHICS_CAMERAMANAGERSYSTEM_HPP_
#define _DIRECTX11GRAPHICS_CAMERAMANAGERSYSTEM_HPP_

#include "DirectX11GraphicsSystem.hpp"

#include "../../GraphicsResources/Include/ICameraManagerSystem.hpp"

namespace Fnd
{
namespace DirectX11Graphics
{

class CameraManagerSystem:
	public DirectX11GraphicsSystem,
	public Fnd::GraphicsResources::ICameraManagerSystem
{
	public:

		CameraManagerSystem( DirectX11Graphics* graphics );

		void SetVREnabled( bool enabled, float lefteye_fov, float righteye_fov );

		void AddNode( Fnd::EntitySystem::SystemNode* node );

		std::vector<std::string> GetRegisteredNodes();

		bool Initialise();

		void UpdateVRCameraOffsets( const Fnd::GameComponentInterfaces::IGraphics::CameraOffsets& camera_offsets );

	protected:

		Fnd::GraphicsResources::ICameraManagerSystem::VRData& GetVRData();

	private:	

		void OnUpdate( const Fnd::CommonResources::FrameData& frame_data );
				
		Fnd::GraphicsResources::ICameraManagerSystem::VRData _vr_data;

		Fnd::GameComponentInterfaces::IGraphics::CameraOffsets _offsets;

};

}
}

#endif