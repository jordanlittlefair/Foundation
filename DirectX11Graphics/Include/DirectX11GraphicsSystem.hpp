#pragma once

#ifndef _DIRECTX11GRAPHICSSYSTEM_HPP_
#define _DIRECTX11GRAPHICSSYSTEM_HPP_

#include "../Include/DirectX11GraphicsBase.hpp"
#include "../../EntitySystem/Include/Components.hpp"
#include "../../EntitySystem/Include/Entity.hpp"
#include "../../EntitySystem/Include/ComponentMaps.hpp"
#include "../../EntitySystem/Include/EntitySystem.hpp"
#include "../../EntitySystem/Include/EntityContainer.hpp"
#include "../../EntitySystem/Include/SystemNodes.hpp"
#include "../../EntitySystem/Include/SystemNodesContainer.hpp"
#include "../../EntitySystem/Include/System.hpp"

namespace Fnd
{
namespace DirectX11Graphics
{

class DirectX11GraphicsSystem:
	public Fnd::EntitySystem::System
{
	public:

		DirectX11GraphicsSystem( const std::string& system_name, DirectX11GraphicsBase* graphics );

		virtual void Resize( unsigned int width, unsigned int height );

	protected:

		DirectX11GraphicsBase* GetGraphics();

		struct CameraData
		{
			Fnd::EntitySystem::CameraNode::Pointers camera_components;
			Fnd::DirectX11Graphics::ScreenBufferResources* screenbuffer;
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

				ScreenBufferResources* screenbuffer = GetGraphics()->GetScreenBufferResources( camera_components.cameraproperties->data.camera_id );
				if ( !screenbuffer )
				{
					continue;
				}

				CameraData camera_data = { camera_components, screenbuffer };

				function( camera_data );
			}
		}

	private:

		DirectX11GraphicsBase* _graphics;
};

}
}

#endif