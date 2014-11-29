#pragma once

#ifndef _GRAPHICSRESOURCES_GRAPHICSSYSTEM_HPP_
#define	_GRAPHICSRESOURCES_GRAPHICSSYSTEM_HPP_

#include "IScreenBufferResources.hpp"

#include "../../GameComponentInterfaces/Include/IGraphics.hpp"
#include "../../EntitySystem/Include/EntitySystem.hpp"
#include "../../EntitySystem/Include/SystemNodes.hpp"
#include "../../EntitySystem/Include/System.hpp"

namespace Fnd
{
namespace GraphicsResources
{

class GraphicsSystem:
	public Fnd::EntitySystem::System
{
	public:

		GraphicsSystem( const std::string& system_name );
	
		//void SetVREnabled( bool enabled, float lefteye_fov, float righteye_fov );
		//need to somehow generalise the cameramanagersystem to handle vr
		//may just need a helper class?
		//or a template, which has a template param of DirectX11System, or OpenGLSystem, and inherits from this? 
		//void UpdateVRCameraOffsets( const Fnd::GameComponentInterfaces::IGraphics::CameraOffsets& camera_offsets );
		
	protected:
	
		virtual IScreenBufferResources* GetScreenBufferResources( unsigned int camera_id ) = 0;
		
		struct CameraData
		{
			Fnd::EntitySystem::CameraNode::Pointers camera_components;
			IScreenBufferResources* screenbuffer;
		};
	
		template <typename FunctionType>
		void ForEachCamera( FunctionType function )
		{
			for (	auto camera_iter = GetEntitySystem().GetSystemNodesContainer().GetNodeMap<CameraNode>().begin();
					camera_iter != GetEntitySystem().GetSystemNodesContainer().GetNodeMap<CameraNode>().end();
					++camera_iter )
			{
				CameraNode::Pointers camera_components;
				if ( !camera_iter->second.GetPointers( GetEntitySystem(), camera_components ) )
				{
					continue;
				}
				
				IScreenBufferResources* screenbuffer = GetScreenBufferResources( camera_components.cameraproperties->data.camera_id );
				if ( !screenbuffer )
				{
					continue;
				}
				
				CameraData camera_data = { camera_components, screenbuffer };
				
				function( camera_data );
			}
		}

	private:

		Fnd::GameComponentInterfaces::IGraphics::CameraOffsets _offsets;

		bool _vr_enabled;
		float _lefteye_fov;
		float _righteye_fov;
};

}
}
#endif