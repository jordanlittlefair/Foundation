#include "../Include/CameraManagerSystem.hpp"

#include "../Include/ScreenBufferResources.hpp"

#include <map>

using namespace Fnd::DirectX11Graphics;
using namespace Fnd::EntitySystem;

CameraManagerSystem::CameraManagerSystem( DirectX11Graphics* graphics ):
	DirectX11GraphicsSystem("CameraManagerSystem",graphics)
{
	_vr_data.vr_enabled = false;
	_vr_data.lefteye_fov = 0;
	_vr_data.righteye_fov = 0;
}

void CameraManagerSystem::SetVREnabled( bool enabled, float lefteye_fov, float righteye_fov )
{
	_vr_data.vr_enabled = enabled;
	_vr_data.lefteye_fov = lefteye_fov;
	_vr_data.righteye_fov = righteye_fov;
}

void CameraManagerSystem::AddNode( Fnd::EntitySystem::SystemNode* node )
{
	if ( node->GetName() == "CameraNode" )
	{
		Fnd::EntitySystem::CameraNode* cameranode = (Fnd::EntitySystem::CameraNode*)node;

		Fnd::EntitySystem::CameraNode::Pointers components;

		if ( !cameranode->GetPointers( GetEntitySystem(), components ) )
		{
			return;
		}

		unsigned int camera_id = components.cameraproperties->data.camera_id;

		GetGraphics()->AddScreenBufferResources( camera_id, GetGraphics()->GetWidth(), GetGraphics()->GetHeight() );
	}
}

std::vector<std::string> CameraManagerSystem::GetRegisteredNodes()
{
	std::vector<std::string> ret;

	ret.push_back("CameraNode");

	return ret;
}

bool CameraManagerSystem::Initialise()
{
	_offsets.lefteye_position_offset = Fnd::Math::Vector3( 0, 0, 0 );
	_offsets.lefteye_rotation_offset = Fnd::Math::Quaternion( 0, 0, 0, 1 );

	_offsets.righteye_position_offset = _offsets.lefteye_position_offset;
	_offsets.righteye_rotation_offset = _offsets.lefteye_rotation_offset;

	return true;
}

void CameraManagerSystem::OnUpdate( const Fnd::CommonResources::FrameData& frame_data )
{
	ForEachCamera( [this]( CameraData& camera_data )
	{		
		auto scene_node = camera_data.camera_components.scenenode;
		auto camera_properties = camera_data.camera_components.cameraproperties;

		// Need to update the fov if VR is enabled
		if ( _vr_data.vr_enabled )
		{
			if ( camera_properties->data.camera_id == 0 )
			{	
				camera_properties->data.fov = _vr_data.lefteye_fov;

				auto rotation_offset_matrix = Fnd::Math::Matrix4Helper<>::CreateRotationMatrix( _offsets.lefteye_rotation_offset );
				auto position_offset_matrix = Fnd::Math::Matrix4Helper<>::CreateTranslationMatrix( _offsets.lefteye_position_offset );

				scene_node->data.transform = ( rotation_offset_matrix * position_offset_matrix ) * scene_node->data.transform;
			}
			else
			if ( camera_properties->data.camera_id == 1 )
			{
				camera_properties->data.fov = _vr_data.righteye_fov;

				auto rotation_offset_matrix = Fnd::Math::Matrix4Helper<>::CreateRotationMatrix( _offsets.righteye_rotation_offset );
				auto position_offset_matrix = Fnd::Math::Matrix4Helper<>::CreateTranslationMatrix( _offsets.righteye_position_offset );

				scene_node->data.transform = ( rotation_offset_matrix * position_offset_matrix ) * scene_node->data.transform;
			}
		}

		auto bufferdata = ((ScreenBufferResources*)camera_data.screenbuffer)->GetPositionReconstructionData();
		bufferdata.tan_half_fov_y = tan( Fnd::Math::ToRadians(camera_data.camera_components.cameraproperties->data.fov) / 2 );

		if ( ((ScreenBufferResources*)camera_data.screenbuffer)->UpdatePositionReconstructionData( bufferdata ) )
		{
			auto a = 0;
		}
	}
	);
}

void CameraManagerSystem::UpdateVRCameraOffsets( const Fnd::GameComponentInterfaces::IGraphics::CameraOffsets& camera_offsets )
{
	_offsets = camera_offsets;
}

Fnd::GraphicsResources::ICameraManagerSystem::VRData& CameraManagerSystem::GetVRData()
{
	return _vr_data;
}