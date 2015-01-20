#pragma once

#ifndef _DIRECTX11GRAPHICS_CAMERAMANAGERSYSTEM_HPP_
#define _DIRECTX11GRAPHICS_CAMERAMANAGERSYSTEM_HPP_

#include "DirectX11GraphicsSystem.hpp"
#include "DirectX11GraphicsSystem.hpp"

#include "../../GraphicsResources/Include/CameraManagerSystemTemplate.hpp"

namespace Fnd
{
namespace DirectX11Graphics
{

typedef Fnd::GraphicsResources::CameraManagerSystemTemplate<DirectX11GraphicsSystem,DirectX11Graphics> CameraManagerSystem;

}
}

#endif