#pragma once

#ifndef _DIRECTX11GRAPHICS_DIRECTX11GRAPHICSSYSTEM_HPP_
#define _DIRECTX11GRAPHICS_DIRECTX11GRAPHICSSYSTEM_HPP_

#include "../Include/DirectX11GraphicsBase.hpp"
#include "../../EntitySystem/Include/Components.hpp"
#include "../../EntitySystem/Include/Entity.hpp"
#include "../../EntitySystem/Include/ComponentMaps.hpp"
#include "../../EntitySystem/Include/EntitySystem.hpp"
#include "../../EntitySystem/Include/EntityContainer.hpp"
#include "../../EntitySystem/Include/SystemNodes.hpp"
#include "../../EntitySystem/Include/SystemNodesContainer.hpp"
#include "../../EntitySystem/Include/System.hpp"

#include "../../GraphicsResources/Include/GraphicsSystem.hpp"

namespace Fnd
{
namespace DirectX11Graphics
{

class DirectX11GraphicsSystem:
	public Fnd::GraphicsResources::GraphicsSystem
{
	public:

		DirectX11GraphicsSystem( const std::string& system_name, DirectX11GraphicsBase* graphics );

		virtual void Resize( unsigned int width, unsigned int height );

	protected:

		DirectX11GraphicsBase* GetGraphics();

		Fnd::GraphicsResources::IScreenBufferResources* GetScreenBufferResources( unsigned int camera_id );

	private:

		DirectX11GraphicsBase* _graphics;
};

}
}

#endif