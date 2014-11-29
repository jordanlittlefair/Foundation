#include "../Include/OpenGLGraphics.hpp"

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

OpenGLGraphics::OpenGLGraphics():
	_game(nullptr),
	_hglrc(nullptr)
{
}

void OpenGLGraphics::SetGraphicsMessageListener( IGraphicsMessageListener* game )
{
	_game = game;
}

void OpenGLGraphics::SetGraphicsSettings( const Fnd::Settings::EngineSettings::GraphicsSettings& config )
{
	// TODO
}

void OpenGLGraphics::SetEntitySystem( Fnd::EntitySystem::EntitySystem* entity_system )
{
	// TODO
}

bool OpenGLGraphics::VRIsSupported()
{
	return false;
}

void OpenGLGraphics::EnableVR( bool enable )
{
	// TODO
}

bool OpenGLGraphics::VRIsEnabled() const
{
	return false;
}

bool OpenGLGraphics::Initialise()
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

	return true;
}

void OpenGLGraphics::Release()
{
	HDC hdc = HDC(_game->GetHDC());

	wglMakeCurrent( hdc, nullptr );

	wglDeleteContext( (HGLRC)_hglrc );

	_hglrc = nullptr;
}

void OpenGLGraphics::Present()
{
	glFlush();
	SwapBuffers(HDC(_game->GetHDC()));
}

void OpenGLGraphics::Resize( unsigned int width, unsigned int height )
{
	// TODO: resize resources
}

void OpenGLGraphics::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glClearColor( 0, 0.5f, 1.0f, 1 );
}

std::vector<std::shared_ptr<Fnd::EntitySystem::System>> OpenGLGraphics::GetSystems()
{
	return std::vector<std::shared_ptr<Fnd::EntitySystem::System>>();
}

Fnd::AssetManager::Texture2D* OpenGLGraphics::GetNewTexture2D()
{
	return nullptr;
}

Fnd::AssetManager::Model* OpenGLGraphics::GetNewModel()
{
	return new OpenGLModel(this);
}

void OpenGLGraphics::SetActiveCamera( unsigned int i, unsigned int j )
{
}

void OpenGLGraphics::OnSetOculusData( const Fnd::GameComponentInterfaces::IGraphics::OculusData& oculus_data )
{

}

Fnd::GameComponentInterfaces::IGraphics::OculusDataOpenGL OpenGLGraphics::GetOculusDataOpenGL()
{
	Fnd::GameComponentInterfaces::IGraphics::OculusDataOpenGL ret;

	memset( &ret, 0, sizeof(ret) );

	return ret;
}

void OpenGLGraphics::UpdateVRCameraOffsets( const Fnd::GameComponentInterfaces::IGraphics::CameraOffsets& camera_offsets )
{
}

bool OpenGLGraphics::AddScreenBufferResources( unsigned int id, unsigned int width, unsigned int height )
{
	return false;
}