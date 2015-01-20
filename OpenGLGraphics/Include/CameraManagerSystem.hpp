#pragma once

#ifndef _OPENGLGRAPHICS_CAMERAMANAGERSYSTEM_HPP_
#define _OPENGLGRAPHICS_CAMERAMANAGERSYSTEM_HPP_

#include "OpenGLGraphics.hpp"
#include "OpenGLGraphicsSystem.hpp"

#include "../../GraphicsResources/Include/CameraManagerSystemTemplate.hpp"

namespace Fnd
{
namespace OpenGLGraphics
{

typedef Fnd::GraphicsResources::CameraManagerSystemTemplate<OpenGLGraphicsSystem,OpenGLGraphics> CameraManagerSystem;

}
}

#endif