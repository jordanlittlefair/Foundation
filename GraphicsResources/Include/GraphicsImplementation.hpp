#pragma once

#ifndef _GRAPHICSRESOURCES_GRAPHICSIMPLEMENTATION_HPP_
#define	_GRAPHICSRESOURCES_GRAPHICSIMPLEMENTATION_HPP_

#include "IScreenBufferResources.hpp"
#include "ICameraManagerSystem.hpp"

#include "../../GameComponentInterfaces/Include/IGraphics.hpp"

namespace Fnd
{
namespace GraphicsResources
{

class GraphicsImplementation:
	public Fnd::GameComponentInterfaces::IGraphics
{
	protected:

		GraphicsImplementation();

		void SetCameraManagerSystem( Fnd::EntitySystem::System* camera_manager_system, ICameraManagerSystem* icamera_manager_system );

		std::shared_ptr<Fnd::EntitySystem::System> GetCameraManagerSystem();

		ICameraManagerSystem* GetCameraManager();

		virtual bool AddScreenBufferResources( unsigned int id, unsigned int width, unsigned int height ) = 0;

		std::map<unsigned int,std::shared_ptr<IScreenBufferResources>>& GetIScreenBufferResources();

		/*
			Inherited from IGraphics
		*/
		void SetGraphicsMessageListener( Fnd::GameComponentInterfaces::IGraphicsMessageListener* game );

		void SetGraphicsSettings( const Fnd::Settings::EngineSettings::GraphicsSettings& config );

		void SetEntitySystem( Fnd::EntitySystem::EntitySystem* entity_system );

		void SetActiveCamera( ActiveCameraType type, unsigned int index );
		
		unsigned int GetActiveCamera( ActiveCameraType type );

		void EnableVR( bool enable );

		bool VRIsEnabled() const;

		void SetOculusData( const Fnd::GameComponentInterfaces::IGraphics::OculusData& oculus_data );

		virtual Fnd::GameComponentInterfaces::IGraphics::OculusDataD3D11 GetOculusDataD3D11();

		virtual Fnd::GameComponentInterfaces::IGraphics::OculusDataOpenGL GetOculusDataOpenGL();

		void UpdateVRCameraOffsets( const CameraOffsets& camera_offsets );

	protected:

		Fnd::GameComponentInterfaces::IGraphicsMessageListener* GetGame();

		Fnd::Settings::EngineSettings::GraphicsSettings& GetGraphicsSettings();

		Fnd::EntitySystem::EntitySystem* GetEntitySystem();

		virtual void OnSetOculusData( const Fnd::GameComponentInterfaces::IGraphics::OculusData& oculus_data ) = 0;

		const Fnd::GameComponentInterfaces::IGraphics::OculusData& GetOculusData();

	private:

		Fnd::GameComponentInterfaces::IGraphicsMessageListener* _game;
		Fnd::Settings::EngineSettings::GraphicsSettings _config;
		Fnd::EntitySystem::EntitySystem* _entity_system;
		
		// Not great but the camera manager ptr must be stored twice-
		// 'DirectX/OpenGLCameraManagerSystem' inherits both DirectX/OpenGLSystem and
		// 'ICameraManagerSystem'- _camera_manager_system (a 'System') cannot
		// be cast to a 'ICameraManagerSystem' without a dynamic cast.
		std::shared_ptr<Fnd::EntitySystem::System> _camera_manager_system;
		ICameraManagerSystem* _i_camera_manager_system;

		std::map<unsigned int,std::shared_ptr<IScreenBufferResources>> _screen_buffer_resources;

		unsigned int _active_camera[ActiveCamera_Count];

		bool _vr_enabled;

		OculusData _oculus_data;
		float _lefteye_fov;
		float _righteye_fov;

};

}
}
#endif