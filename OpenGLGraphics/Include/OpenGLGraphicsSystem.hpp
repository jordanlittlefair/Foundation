#pragma once

#ifndef _OPENGLGRAPHICS_DIRECTX11GRAPHICSSYSTEM_HPP_
#define _OPENGLGRAPHICS_DIRECTX11GRAPHICSSYSTEM_HPP_

#include "../Include/OpenGLGraphics.hpp"
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
namespace OpenGLGraphics
{

class OpenGLGraphicsSystem:
	public Fnd::GraphicsResources::GraphicsSystem
{
	public:

		OpenGLGraphicsSystem( const std::string& system_name, OpenGLGraphics* graphics );

		virtual void Resize( unsigned int width, unsigned int height );

	protected:

		OpenGLGraphics* GetGraphics();

		Fnd::GraphicsResources::ScreenBufferResourcesBase* GetScreenBufferResources( unsigned int camera_id );

	private:

		OpenGLGraphics* _graphics;
};

}
}

#endif