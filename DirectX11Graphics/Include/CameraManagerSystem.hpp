#pragma once

#ifndef _CAMERAMANAGERSYSTEM_HPP_
#define _CAMERAMANAGERSYSTEM_HPP_

#include "DirectX11GraphicsSystem.hpp"

namespace Fnd
{
namespace DirectX11Graphics
{

class CameraManagerSystem:
	public Fnd::DirectX11Graphics::DirectX11GraphicsSystem
{
	public:

		CameraManagerSystem( DirectX11GraphicsBase* graphics );

		void SetVREnabled( bool enabled, float lefteye_fov, float righteye_fov );

		void AddNode( Fnd::EntitySystem::SystemNode* node );

		std::vector<std::string> GetRegisteredNodes();

		bool Initialise();

		void UpdateVRCameraOffsets( const Fnd::GameComponentInterfaces::IGraphics::CameraOffsets& camera_offsets );

	private:	

		void OnUpdate( const Fnd::CommonResources::FrameData& frame_data );
				
		Fnd::GameComponentInterfaces::IGraphics::CameraOffsets _offsets;

		bool _vr_enabled;
		float _lefteye_fov;
		float _righteye_fov;

};

}
}

#endif