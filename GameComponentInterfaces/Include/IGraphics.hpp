#pragma once

#ifndef _GAMECOMPONENTINTERFACES_IGRAPHICS_HPP_
#define _GAMECOMPONENTINTERFACES_IGRAPHICS_HPP_

#include <vector>
#include <memory>

#include "../../Math/Include/Vector3.hpp"
#include "../../Math/Include/Quaternion.hpp"
#include "../../Settings/Include/EngineSettings.hpp"

namespace Fnd
{
namespace GameComponentInterfaces
{
	class IGraphicsMessageListener;
}
}

namespace Fnd
{
namespace AssetManager
{
class Texture2D;
class Model;
}
namespace EntitySystem
{
class EntitySystem;
class System;
}
}

namespace Fnd
{
namespace GameComponentInterfaces
{

/**
	Base class for interacting with graphics implementations.

	Handles graphics resources and renders the scene.
*/
class IGraphics
{
	public:

		/**
			Set the a pointer to the game.
			@param game A pointer to the IGraphicsMessageListener inferface of the Game component.
		*/
		virtual void SetGraphicsMessageListener( Fnd::GameComponentInterfaces::IGraphicsMessageListener* game ) = 0;

		virtual void SetGraphicsSettings( const Fnd::Settings::EngineSettings::GraphicsSettings& graphics_settings ) = 0;

		virtual void SetEntitySystem( Fnd::EntitySystem::EntitySystem* entity_system ) = 0;

		virtual bool VRIsSupported() = 0;

		virtual void EnableVR( bool enable ) = 0;

		virtual bool VRIsEnabled() const = 0;

		/** 
			Initialise the Graphics.
			@return Returns true if successful.
		*/
		virtual bool Initialise() = 0;

		/**
			Render the scene.
		*/
		virtual void Render() = 0;

		/**
			Present the backbuffer to the screen.
		*/
		virtual void Present() = 0;

		/**
			Resize the graphics resources.
			@param width The new width of the window.
			@param height The new height of the window.
		*/
		virtual void Resize( unsigned int width, unsigned int height ) = 0;

		/**
			Release the graphics resources.
		*/
		virtual void Release() = 0;

		/**
			Virtual destructor.
		*/
		virtual ~IGraphics() {};

		/**
			Create a Texture2D.
		*/
		virtual Fnd::AssetManager::Texture2D* GetNewTexture2D() = 0;
		virtual Fnd::AssetManager::Model* GetNewModel() = 0;

		/**
			Get a vector of systems implemented by the graphics component.
			Must be uninitialised and in order of execution.
		*/
		virtual std::vector<std::shared_ptr<Fnd::EntitySystem::System>> GetSystems() = 0;

		/**
			Set the active camera(s)
			(2nd param is to enable oculus rift stuff)
		*/
		virtual void SetActiveCamera( unsigned int i, unsigned int j = ~0 ) = 0;

		struct OculusDataD3D11
		{
			void* eye_tex;
			void* eye_srv;

			void* device;
			void* device_context;
			void* back_buffer_rt;
			void* swap_chain;
		};

		struct OculusData
		{
			unsigned int hmd_width;
			unsigned int hmd_height;

			unsigned int righteye_width;
			unsigned int righteye_height;
			unsigned int lefteye_width;
			unsigned int lefteye_height;

			// vertical fov foe eyes
			float lefteye_fov_v;
			float righteye_fov_v;
		};

		virtual void SetOculusData( const OculusData& oculus_data ) = 0;

		virtual OculusDataD3D11 GetOculusDataD3D11() = 0;

		struct OculusDataOpenGL
		{
			int placeholder;
		};

		virtual OculusDataOpenGL GetOculusDataOpenGL() = 0;

		struct CameraOffsets
		{
			Fnd::Math::Vector3 lefteye_position_offset;
			Fnd::Math::Quaternion lefteye_rotation_offset;
			Fnd::Math::Vector3 righteye_position_offset;
			Fnd::Math::Quaternion righteye_rotation_offset;
		};

		virtual void UpdateVRCameraOffsets( const CameraOffsets& camera_offset ) = 0;
};

}
}

#endif