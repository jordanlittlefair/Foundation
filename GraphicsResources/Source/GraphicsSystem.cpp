#include "../Include/GraphicsSystem.hpp"

using namespace Fnd::GraphicsResources;

GraphicsSystem::GraphicsSystem( const std::string& system_name ):
	System(system_name),
	 _vr_enabled(false),
	 _lefteye_fov(0),
	 _righteye_fov(0)
{
}
	
/*void GraphicsSystem::SetVREnabled( bool enabled, float lefteye_fov, float righteye_fov )
{
	_vr_enabled = enabled;
	_lefteye_fov = lefteye_fov;
	_righteye_fov = righteye_fov;
}*/
		
/*void GraphicsSystem::UpdateVRCameraOffsets( const Fnd::GameComponentInterfaces::IGraphics::CameraOffsets& camera_offsets )
{
	_offsets = camera_offsets;
}*/