#include "../Include/XWindowsWindow.hpp"

#include "../../GameComponentInterfaces/Include/IWindowMessageListener.hpp"

#include <iostream>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

using namespace Fnd::XWindowsWindow;

struct XWindowsWindow::XWindowsData
{
    XWindowsData():
        display(nullptr),
        window(0),
        visual_info(nullptr)
    {
    }
    Display* display;
    Window window;
    XVisualInfo* visual_info;
};

XWindowsWindow::XWindowsWindow():
    _width(0),
    _height(0),
    _is_resizable(false),
    _is_fullscreen(false),
    _game(nullptr),
    _is_initialised(false),
    _is_open(false),
    _is_active(false),
    _data(nullptr)
{
    _data.reset( new XWindowsData() );
}

void XWindowsWindow::SetWindowTitle( const std::string& title )
{
    _title = title;
}

void XWindowsWindow::SetWindowSize( unsigned int width, unsigned int height )
{
    _width = width;
    _height = height;
}

void XWindowsWindow::SetWindowResizable( bool resizable )
{
    _is_resizable = resizable;
}

void XWindowsWindow::SetWindowFullscreen( bool fullscreen )
{
    _is_fullscreen = fullscreen;
}

void XWindowsWindow::SetWindowMessageListener( Fnd::GameComponentInterfaces::IWindowMessageListener* game )
{
    _game = game;
}

bool XWindowsWindow::Initialise()
{
    if ( _is_initialised )
	{
		//LogError( "Cannot initialise the Window; Window is already initialised." );
		return false;
	}

	// Return false if the window has no area.
	if ( _width == 0 || _height == 0 )
	{
		//LogError( "Cannot initialise the Window; Window has zero area." );
		return false;
	}

	/*
        Initialise window.
    */
    _data->display = XOpenDisplay(nullptr);

    if( !_data->display )
    {
       std::cout << "Cannot connect to X server\n";
       return false;
    }

    _data->window = DefaultRootWindow(_data->display);

    GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

    _data->visual_info = glXChooseVisual( _data->display, 0, att );

    if( !_data->visual_info )
    {
        std::cout << "No appropriate visual found.\n";
    //    return false;
    }

   Colormap cmap = XCreateColormap(_data->display, _data->window, _data->visual_info->visual, AllocNone);

    XSetWindowAttributes swa;
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask;

    Window win = XCreateWindow( _data->display, _data->window, 0, 0, _width, _height, 0, _data->visual_info->depth, InputOutput, _data->visual_info->visual, CWColormap | CWEventMask, &swa);

    XMapWindow( _data->display, win );
    XStoreName( _data->display, win, _title.c_str() );

    GLXContext glc = glXCreateContext( _data->display, _data->visual_info, nullptr, GL_TRUE);
    glXMakeCurrent( _data->display , win, glc );

	_is_open = true;

	_is_initialised = true;

	return true;
}

void* XWindowsWindow::GetHWND() const
{
    return nullptr;
}

void* XWindowsWindow::GetHDC() const
{
    return nullptr;
}

void* XWindowsWindow::GetXWindowsDisplay() const
{
    return _data->display;
}

unsigned long XWindowsWindow::GetXWindowsWindow() const
{
    return _data->window;
}

void XWindowsWindow::Show()
{
    // TODO: show
}

bool XWindowsWindow::IsOpen() const
{
    return _is_open;
}

bool XWindowsWindow::IsActive() const
{
    return _is_active;
}

void XWindowsWindow::HandleWindowMessages()
{
    // TODO : messages

    //XCheckWindowEvent() -> peekmessages
}

void XWindowsWindow::ShowCursor( bool show )
{
    // TODO: show cursor
}

void XWindowsWindow::CloseWindow()
{
    // TODO: 'post' close message (?)
}

XWindowsWindow::~XWindowsWindow()
{
    // TODO: release window
}

void XWindowsWindow::Activate()
{
    _is_active = true;

	// Call the Game's onWindowActivate method.
	if ( _game )
	{
		_game->OnWindowActivate();
	}
}

void XWindowsWindow::Deactivate()
{
    _is_active = false;

	// Call the Game's onWindowDeactivate method.
	if ( _game )
	{
		_game->OnWindowDeactivate();
	}
}

void XWindowsWindow::Resize( unsigned int width, unsigned int height )
{
    _width = width;
	_height = height;

	// Call the Game's onWindowResize method.
	if ( _game )
	{
		_game->OnWindowResize( _width, _height );
	}
}

void XWindowsWindow::Close()
{
    _is_open = false;

	// Call the Game's onWindowClose method.
	if( _game )
	{
		_game->OnWindowClose();
	}
}

/*
Display                 *dpy;
Window                  root;
GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo             *vi;
Colormap                cmap;
XSetWindowAttributes    swa;
Window                  win;
GLXContext              glc;
XWindowAttributes       gwa;
XEvent                  xev;

void DrawAQuad() {
 glClearColor(1.0, 0.5, 0.0, 1.0);
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main() {

 dpy = XOpenDisplay(NULL);

 if(dpy == NULL) {
        printf("\n\tcannot connect to X server\n\n");
        exit(0);
 }

 root = DefaultRootWindow(dpy);

 vi = glXChooseVisual(dpy, 0, att);

 if(vi == NULL) {
        printf("\n\tno appropriate visual found\n\n");
        exit(0);
 }
 else {
        printf("\n\tvisual %p selected\n", (void *)vi->visualid); %p creates hexadecimal output like in glxinfo
 }


 cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

 swa.colormap = cmap;
 swa.event_mask = ExposureMask | KeyPressMask;

 win = XCreateWindow(dpy, root, 0, 0, 600, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

 XMapWindow(dpy, win);
 XStoreName(dpy, win, "VERY SIMPLE APPLICATION");

 glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
 glXMakeCurrent(dpy, win, glc);

 glEnable(GL_DEPTH_TEST);

 while(1) {
        XNextEvent(dpy, &xev);

        if(xev.type == Expose) {
                XGetWindowAttributes(dpy, win, &gwa);
                glViewport(0, 0, gwa.width, gwa.height);
                DrawAQuad();
                glXSwapBuffers(dpy, win);
        }

        else if(xev.type == KeyPress) {
                glXMakeCurrent(dpy, None, NULL);
                glXDestroyContext(dpy, glc);
                XDestroyWindow(dpy, win);
                XCloseDisplay(dpy);
                exit(0);
        }
    }
}*/
