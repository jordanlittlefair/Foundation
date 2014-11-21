#include "../Include/OpenGLGraphicsBase.hpp"

#include "../../GameComponentInterfaces/Include/IGraphicsMessageListener.hpp"
#include "../Include/OpenGLModel.hpp"

//#ifdef _WIN32
//#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <wingdi.h>
//#endif

#include "../../glew/Include/glew.hpp"

using namespace Fnd::OpenGLGraphics;
using namespace Fnd::GameComponentInterfaces;

OpenGLGraphicsBase::OpenGLGraphicsBase():
	_game(nullptr),
	_hglrc(nullptr)
{
}

void OpenGLGraphicsBase::SetGraphicsMessageListener( IGraphicsMessageListener* game )
{
	_game = game;
}

void OpenGLGraphicsBase::SetConfig( const Fnd::Settings::GraphicsConfig& config )
{
	// TODO
}

void OpenGLGraphicsBase::SetEntitySystem( Fnd::EntitySystem::EntitySystem* entity_system )
{
	// TODO
}

void OpenGLGraphicsBase::EnableVR( bool enable )
{
	// TODO
}

bool OpenGLGraphicsBase::VRIsEnabled() const
{
	return false;
}

bool OpenGLGraphicsBase::Initialise()
{
	if ( !_game )
	{
		return false;
	}

#ifdef _WIN32

	HDC hdc = HDC(_game->GetHDC());
	PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    // set the pixel format for the DC
    memset( &pfd, sizeof( pfd ), 0 );
    pfd.nSize = sizeof( pfd );
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
                  PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat( hdc, &pfd );
    SetPixelFormat( hdc, iFormat, &pfd );

	_hglrc = wglCreateContext(hdc);

	wglMakeCurrent(hdc,(HGLRC)_hglrc);

	GLenum err = glewInit();
	if ( err != GLEW_OK )
	{
		auto a = 0;
	}
#endif

	return OnInitialise();
}

void OpenGLGraphicsBase::Release()
{
	OnRelease();

	HDC hdc = HDC(_game->GetHDC());

	wglMakeCurrent( hdc, nullptr );

	wglDeleteContext( (HGLRC)_hglrc );

	_hglrc = nullptr;
}

void OpenGLGraphicsBase::Present()
{
	glFlush();
	SwapBuffers(HDC(_game->GetHDC()));
}

void OpenGLGraphicsBase::Resize( unsigned int width, unsigned int height )
{
	// TODO: resize resources

	OnResize( width, height );
}

std::vector<std::shared_ptr<Fnd::EntitySystem::System>> OpenGLGraphicsBase::GetSystems()
{
	return std::vector<std::shared_ptr<Fnd::EntitySystem::System>>();
}

Fnd::AssetManager::Texture2D* OpenGLGraphicsBase::GetNewTexture2D()
{
	return nullptr;
}

Fnd::AssetManager::Model* OpenGLGraphicsBase::GetNewModel()
{
	return new OpenGLModel(this);
}

void OpenGLGraphicsBase::SetActiveCamera( unsigned int i, unsigned int j )
{
}

void OpenGLGraphicsBase::SetOculusData( const Fnd::GameComponentInterfaces::IGraphics::OculusData& oculus_data )
{

}

Fnd::GameComponentInterfaces::IGraphics::OculusDataD3D11 OpenGLGraphicsBase::GetOculusDataD3D11()
{
	Fnd::GameComponentInterfaces::IGraphics::OculusDataD3D11 ret;

	memset( &ret, 0, sizeof(ret) );

	return ret;
}

Fnd::GameComponentInterfaces::IGraphics::OculusDataOpenGL OpenGLGraphicsBase::GetOculusDataOpenGL()
{
	Fnd::GameComponentInterfaces::IGraphics::OculusDataOpenGL ret;

	memset( &ret, 0, sizeof(ret) );

	return ret;
}

void OpenGLGraphicsBase::UpdateVRCameraOffsets( const Fnd::GameComponentInterfaces::IGraphics::CameraOffsets& camera_offsets )
{
}