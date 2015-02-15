#pragma once

#ifndef _GRAPHICSRESOURCES_CAMERAMANAGERSYSTEMTEMPLATE_HPP_
#define _GRAPHICSRESOURCES_CAMERAMANAGERSYSTEMTEMPLATE_HPP_

#include "ICameraManagerSystem.hpp"

namespace Fnd
{
namespace GraphicsResources
{

/*
	Both dx11 and opengl CameraManagerSystems contain the same code, but must derive from different types.

	This template should be used to avoid duplicate code.
*/

template <typename GraphicsSystemType, typename GraphicsImplementationType>
class CameraManagerSystemTemplate:
	public GraphicsSystemType,
	public Fnd::GraphicsResources::ICameraManagerSystem
{
	public:

		CameraManagerSystemTemplate( GraphicsImplementationType* graphics ):
			GraphicsSystemType("CameraManagerSystem",graphics)
		{
			_vr_data.vr_enabled = false;
			_vr_data.lefteye_fov = 0;
			_vr_data.righteye_fov = 0;
		}

		void SetVREnabled( bool enabled, float lefteye_fov, float righteye_fov )
		{
			_vr_data.vr_enabled = enabled;
			_vr_data.lefteye_fov = lefteye_fov;
			_vr_data.righteye_fov = righteye_fov;
		}

		void AddNode( Fnd::EntitySystem::SystemNode* node )
		{
			if ( node->GetName() == "CameraNode" )
			{
				Fnd::EntitySystem::CameraNode* cameranode = (Fnd::EntitySystem::CameraNode*)node;

				Fnd::EntitySystem::CameraNode::Pointers components;

				if ( !cameranode->GetPointers( this->GetEntitySystem(), components ) )
				{
					return;
				}

				unsigned int camera_id = components.cameraproperties->data.camera_id;

				this->GetGraphics()->AddScreenBufferResources( camera_id, this->GetGraphics()->GetWidth(), this->GetGraphics()->GetHeight() );
			}
		}

		std::vector<std::string> GetRegisteredNodes()
		{
			std::vector<std::string> ret;

			ret.push_back("CameraNode");

			return ret;
		}

		bool Initialise()
		{
			_offsets.lefteye_position_offset = Fnd::Math::Vector3( 0, 0, 0 );
			_offsets.lefteye_rotation_offset = Fnd::Math::Quaternion( 0, 0, 0, 1 );

			_offsets.righteye_position_offset = _offsets.lefteye_position_offset;
			_offsets.righteye_rotation_offset = _offsets.lefteye_rotation_offset;

			return true;
		}

		void UpdateVRCameraOffsets( const Fnd::GameComponentInterfaces::IGraphics::CameraOffsets& camera_offsets )
		{
			_offsets = camera_offsets;
		}


	protected:

		Fnd::GraphicsResources::ICameraManagerSystem::VRData& GetVRData()
		{
			return _vr_data;
		}

	private:	

		void OnUpdate( const Fnd::CommonResources::FrameData& frame_data )
		{
			this->ForEachCamera( [this]( typename GraphicsSystemType::CameraData& camera_data )
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

				auto bufferdata = ((OpenGLGraphics::ScreenBufferResources*)camera_data.screenbuffer)->GetPositionReconstructionData();
				bufferdata.tan_half_fov_y = tan( Fnd::Math::ToRadians(camera_data.camera_components.cameraproperties->data.fov) / 2 );

				if ( ((OpenGLGraphics::ScreenBufferResources*)camera_data.screenbuffer)->UpdatePositionReconstructionData( bufferdata ) )
				{
					//auto a = 0;
				}
			}
			);
		}

		Fnd::GraphicsResources::ICameraManagerSystem::VRData _vr_data;

		Fnd::GameComponentInterfaces::IGraphics::CameraOffsets _offsets;

};

}
}

#endif