#pragma once

#ifndef _OPENGLGRAPHICS_CAMERAMANAGERSYSTEM_HPP_
#define _OPENGLGRAPHICS_CAMERAMANAGERSYSTEM_HPP_

#include "OpenGLGraphics.hpp"
#include "OpenGLGraphicsSystem.hpp"
#include "../../GraphicsResources/Include/ICameraManagerSystem.hpp"

namespace Fnd
{
namespace OpenGLGraphics
{

class CameraManagerSystem:
	public OpenGLGraphicsSystem,
	public Fnd::GraphicsResources::ICameraManagerSystem
{
	public:

		CameraManagerSystem( OpenGLGraphics* graphics );

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