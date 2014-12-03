#include "../Include/GraphicsImplementation.hpp"

#include "../../EntitySystem/Include/System.hpp"

using namespace Fnd::GraphicsResources;

GraphicsImplementation::GraphicsImplementation():
	_game(nullptr),
	_entity_system(nullptr),
	_i_camera_manager_system(nullptr),
	_vr_enabled(false),
	_lefteye_fov(0),
	_righteye_fov(0),
	_width(0),
	_height(0)
{
	memset( _active_camera, ~0, ActiveCamera_Count );
	memset( &_oculus_data, 0, sizeof(_oculus_data) );
}

void GraphicsImplementation::SetCameraManagerSystem( Fnd::EntitySystem::System* camera_manager_system, ICameraManagerSystem* icamera_manager_system )
{
	_camera_manager_system = std::shared_ptr<Fnd::EntitySystem::System>( camera_manager_system );
	_i_camera_manager_system = icamera_manager_system;
}

std::shared_ptr<Fnd::EntitySystem::System> GraphicsImplementation::GetCameraManagerSystem()
{
	return _camera_manager_system;
}

ICameraManagerSystem* GraphicsImplementation::GetCameraManager()
{
	return _i_camera_manager_system;
}

std::map<unsigned int,std::shared_ptr<ScreenBufferResourcesBase>>& GraphicsImplementation::GetScreenBufferResourcesBase()
{
	return _screen_buffer_resources;
}

unsigned int GraphicsImplementation::GetWidth() const
{
	return _width;
}

unsigned int GraphicsImplementation::GetHeight() const
{
	return _height;
}

void GraphicsImplementation::SetWidth( unsigned int width )
{
	_width = width;
}

void GraphicsImplementation::SetHeight( unsigned int height )
{
	_height = height;
}

void GraphicsImplementation::SetGraphicsMessageListener( Fnd::GameComponentInterfaces::IGraphicsMessageListener* game )
{
	_game = game;
}

void GraphicsImplementation::SetGraphicsSettings( const Fnd::Settings::EngineSettings::GraphicsSettings& config )
{
	_config = config;
}

void GraphicsImplementation::SetEntitySystem( Fnd::EntitySystem::EntitySystem* entity_system )
{
	_entity_system = entity_system;
}

void GraphicsImplementation::SetActiveCamera( ActiveCameraType type, unsigned int index )
{
	_active_camera[type] = index;
}
		
unsigned int GraphicsImplementation::GetActiveCamera( ActiveCameraType type )
{
	return _active_camera[type];
}

void GraphicsImplementation::EnableVR( bool enable )
{
	_vr_enabled = enable;
}
		
bool GraphicsImplementation::VRIsEnabled() const
{
	return _vr_enabled;
}

void GraphicsImplementation::SetOculusData( const Fnd::GameComponentInterfaces::IGraphics::OculusData& oculus_data )
{
	_oculus_data = oculus_data;

	_lefteye_fov = Fnd::Math::ToDegrees( oculus_data.lefteye_fov_v );
	_righteye_fov = Fnd::Math::ToDegrees( oculus_data.righteye_fov_v );

	AddScreenBufferResources( 0, oculus_data.lefteye_width, oculus_data.lefteye_height );
	AddScreenBufferResources( 1, oculus_data.righteye_width, oculus_data.righteye_height );
	
	if ( GetCameraManager() )
		GetCameraManager()->SetVREnabled( VRIsEnabled(), _lefteye_fov, _righteye_fov );

	OnSetOculusData( oculus_data );
}

Fnd::GameComponentInterfaces::IGraphics::OculusDataD3D11 GraphicsImplementation::GetOculusDataD3D11()
{
	Fnd::GameComponentInterfaces::IGraphics::OculusDataD3D11 ret;
	
	memset( &ret, 0, sizeof(ret) );
	
	return ret;
}

Fnd::GameComponentInterfaces::IGraphics::OculusDataOpenGL GraphicsImplementation::GetOculusDataOpenGL()
{
	Fnd::GameComponentInterfaces::IGraphics::OculusDataOpenGL ret;

	memset( &ret, 0, sizeof(ret) );

	return ret;
}

void GraphicsImplementation::UpdateVRCameraOffsets( const Fnd::GameComponentInterfaces::IGraphics::CameraOffsets& camera_offsets )
{
	if ( GetCameraManager() )
	{
		GetCameraManager()->UpdateVRCameraOffsets( camera_offsets );
	}
}

Fnd::GameComponentInterfaces::IGraphicsMessageListener* GraphicsImplementation::GetGame()
{
	return _game;
}

Fnd::Settings::EngineSettings::GraphicsSettings& GraphicsImplementation::GetGraphicsSettings()
{
	return _config;
}

Fnd::EntitySystem::EntitySystem* GraphicsImplementation::GetEntitySystem()
{
	return _entity_system;
}

const Fnd::GameComponentInterfaces::IGraphics::OculusData& GraphicsImplementation::GetOculusData()
{
	return _oculus_data;
}