#pragma once

#ifndef _GRAPHICSRESOURCES_ICAMERAMANAGERSYSTEM_HPP_
#define	_GRAPHICSRESOURCES_ICAMERAMANAGERSYSTEM_HPP_

#include "../../GameComponentInterfaces/Include/IGraphics.hpp"

namespace Fnd
{
namespace GraphicsResources
{

class ICameraManagerSystem
{
	public:
		
		virtual void SetVREnabled( bool enabled, float lefteye_fov, float righteye_fov ) = 0;

		virtual void UpdateVRCameraOffsets( const Fnd::GameComponentInterfaces::IGraphics::CameraOffsets& camera_offsets ) = 0;

	protected:

		struct VRData
		{
			bool vr_enabled;
			float lefteye_fov;
			float righteye_fov;
		};

		virtual VRData& GetVRData() = 0;
};

}
}
#endif