#include "../Include/OpenGLGraphics.hpp"

#include "../../GameComponentInterfaces/Include/IGraphicsMessageListener.hpp"
#include "../Include/OpenGLModel.hpp"
#include "../Include/CameraManagerSystem.hpp"
#include "../Include/MeshSystem.hpp"

#ifdef _WIN32
#include <Windows.h>
#include <wingdi.h>
#else
#include <X11/Xlib.h>
#include "../../glew/Include/glew.hpp"
#include <GL/glx.h>
#endif

using namespace Fnd::OpenGLGraphics;
using namespace Fnd::GameComponentInterfaces;

OpenGLGraphics::OpenGLGraphics():
	_hglrc(nullptr),
	_resources(this)
{
}

bool OpenGLGraphics::VRIsSupported()
{
	return false;
}

bool OpenGLGraphics::Initialise()
{
	if ( !GetGame() )
	{
		return false;
	}

#ifdef _WIN32

	HDC hdc = HDC(GetGame()->GetHDC());
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
	
#endif

    glewExperimental = GL_TRUE; 
    GLenum err = glewInit();
	if ( err != GLEW_OK )
	{
		// TODO: failed to initialise glew
	}

#ifdef WIN32
	RECT rectangle;
	GetClientRect( HWND(GetGame()->GetHWND()), &rectangle );

	unsigned int width = rectangle.right - rectangle.left;
	unsigned int height = rectangle.bottom - rectangle.top;
#else
    unsigned int width = 1280;
    unsigned int height = 720;
#endif
	SetWidth( width );
	SetHeight( height );

	_resources.SetConfig(GetGraphicsSettings());
	if ( !_resources.Initialise() )
	{
		return false;
	}

	return true;
}

void OpenGLGraphics::Release()
{
#ifdef _WIN32
	HDC hdc = HDC(GetGame()->GetHDC());

	wglMakeCurrent( hdc, nullptr );

	wglDeleteContext( (HGLRC)_hglrc );

	_hglrc = nullptr;
#endif
}

void OpenGLGraphics::Present()
{
	glFlush();
    
#ifdef _WIN32
	SwapBuffers(HDC(GetGame()->GetHDC()));
#else
    glXSwapBuffers((Display*)GetGame()->GetXWindowsDisplay(), (GLXDrawable)GetGame()->GetXWindowsWindow());
#endif
}

void OpenGLGraphics::Resize( unsigned int width, unsigned int height )
{
	if ( GetWidth() == width && GetHeight() == height )
	{
		return;
	}

	SetWidth( width );
	SetHeight( height );

	for ( auto iter = GetScreenBufferResourcesBase().begin(); iter != GetScreenBufferResourcesBase().end(); ++iter )
	{
		iter->second->Resize( GetWidth(), GetHeight() );
	}}

void OpenGLGraphics::BeginRender()
{
	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glClearColor( 0, 0.5f, 1.0f, 1 );
}

std::vector<std::shared_ptr<Fnd::EntitySystem::System>> OpenGLGraphics::GetSystems()
{
	auto systems = std::vector<std::shared_ptr<Fnd::EntitySystem::System>>();

	CameraManagerSystem* camera_manager_system = new CameraManagerSystem( this );
	SetCameraManagerSystem( camera_manager_system, camera_manager_system );

	systems.push_back( (std::shared_ptr<Fnd::EntitySystem::System>)GetCameraManagerSystem() );
	systems.push_back( (std::shared_ptr<Fnd::EntitySystem::System>)new MeshSystem( this ) );

	return systems;
}

Fnd::AssetManager::Texture2D* OpenGLGraphics::GetNewTexture2D()
{
	return nullptr;
}

Fnd::AssetManager::Model* OpenGLGraphics::GetNewModel()
{
	return new OpenGLModel(this);
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

ScreenBufferResources* OpenGLGraphics::GetScreenBufferResources( unsigned int id )
{
	auto found = GetScreenBufferResourcesBase().find(id);

	if ( found != GetScreenBufferResourcesBase().end() )
	{
		return (ScreenBufferResources*)found->second.get();
	}
	else
	{
		return nullptr;
	}
}
bool OpenGLGraphics::AddScreenBufferResources( unsigned int id, unsigned int width, unsigned int height )
{
	if ( !GetScreenBufferResources(id) )
	{
		std::shared_ptr<ScreenBufferResources> srb( new ScreenBufferResources(this));

		if ( srb->Initialise( width, height ) )
		{
			GetScreenBufferResourcesBase().insert( std::make_pair( id, srb ) );

			return true;
		}
	}

	return false;
}