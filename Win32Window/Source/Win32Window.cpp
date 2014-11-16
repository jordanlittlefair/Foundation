#include "../Include/Win32Window.hpp"

#include "../../GameComponentInterfaces/Include/IWindowMessageListener.hpp"

using namespace Fnd::Win32Window;
using namespace Fnd::GameComponentInterfaces;

Win32Window::Win32Window():
	_is_initialised(false),
	_window(nullptr),
	_game(nullptr),
	_width(0),
	_height(0),
	_style(Fixed_Size_Window_Style),
	_title("This window has no title."),
	_is_open(false),
	_is_active(false)
{
}

void Win32Window::SetWindowTitle( const std::string& title )
{
	if ( !_is_initialised )
	{
		_title = title;
	}
}

void Win32Window::SetWindowSize( unsigned int width, unsigned int height )
{
	if ( !_is_initialised )
	{
		_width = width;
		_height = height;
	}
	else
	{
		 SetWindowPos( _window, nullptr, 0, 0, width, height, SWP_NOREPOSITION|SWP_NOZORDER|SWP_NOACTIVATE );
	}
}

void Win32Window::SetWindowResizable( bool resizable )
{
	_style = resizable ? Resizable_Window_Style : Fixed_Size_Window_Style;
}

void Win32Window::SetWindowFullscreen( bool fullscreen )
{
	// TODO: Currently unimplemented.
}

void Win32Window::SetStyle( Win32WindowStyle style )
{
	if ( !_is_initialised )
	{
		_style = style;
	}
}

void Win32Window::SetWindowMessageListener( IWindowMessageListener* game )
{
	if ( !_is_initialised )
	{
		_game = game;
	}
}

bool Win32Window::Initialise()
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

	// Register window class
	WNDCLASSEX window_class;

	window_class.cbSize = sizeof(WNDCLASSEX);
	window_class.style = 0;
	window_class.lpfnWndProc = wndProc;
	window_class.cbClsExtra = 0;
	window_class.cbWndExtra = 0;
	window_class.hInstance = nullptr;
	window_class.hIcon = nullptr;
	window_class.hCursor = LoadCursor( 0, IDC_ARROW );
	window_class.hbrBackground = nullptr;
	window_class.lpszMenuName = nullptr;
	window_class.lpszClassName = "Window";
	window_class.hIconSm = nullptr;

	if ( !RegisterClassEx( &window_class ) )
	{
		//LogError( "Initialisation failed; Cannot register window_class." );
		return false;
	}

	// Adjust the size of the window (by adding the size of the borders).
	RECT client_rectangle = { 0, 0, (int)_width, (int)_height };
	AdjustWindowRect( &client_rectangle, _style, false );

	const unsigned int window_width = client_rectangle.right - client_rectangle.left;
	const unsigned int window_height = client_rectangle.bottom - client_rectangle.top;

	// Create the window.
	_window = CreateWindowEx(	0,
								"Window",
								_title.c_str(),
								_style,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								window_width,
								window_height,
								nullptr,
								nullptr,
								nullptr,
								nullptr );

	if ( !_window )
	{
		//LogError( "Initialisation failed; Cannot create window." );
		return false;
	}

	SetWindowLongPtr( _window, GWL_USERDATA, (LONG_PTR)this );

	_is_open = true;

	_is_initialised = true;

	return true;
}

void* Win32Window::GetHWND() const
{
	return _window;
}

void* Win32Window::GetHDC() const
{
	return GetDC(_window);
}

void Win32Window::Show()
{
	ShowWindow( _window, SW_RESTORE );
}

bool Win32Window::IsOpen() const
{
	return _is_open;
}

bool Win32Window::IsActive() const
{
	return _is_active;
}

void Win32Window::HandleWindowMessages()
{
	// Process messages
	MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void Win32Window::ShowCursor( bool show )
{
	ShowCursor(show);
}

void Win32Window::CloseWindow()
{
	// Post a Quit message which is processed the next time recieveWindowMessages() is called.
	PostMessage( _window, WM_CLOSE, 0, 0 );
}

Win32Window::~Win32Window()
{
	if ( _window )
	{
		DestroyWindow( _window );
		UnregisterClass( "Window", 0 );
	}
}

void Win32Window::Activate()
{
	_is_active = true;

	// Call the Game's onWindowActivate method.
	if ( _game )
	{
		_game->OnWindowActivate();
	}
}

void Win32Window::Deactivate()
{
	_is_active = false;

	// Call the Game's onWindowDeactivate method.
	if ( _game )
	{
		_game->OnWindowDeactivate();
	}
}

void Win32Window::Resize( unsigned int width, unsigned int height )
{
	_width = width;
	_height = height;

	// Call the Game's onWindowResize method.
	if ( _game )
	{
		_game->OnWindowResize( _width, _height );
	}
}

void Win32Window::Close()
{
	_is_open = false;

	// Call the Game's onWindowClose method.
	if( _game )
	{
		_game->OnWindowClose();
	}
}

LRESULT WINAPI Win32Window::wndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	Win32Window* window = (Win32Window*)GetWindowLongPtr( wnd, GWL_USERDATA );

	switch (msg)
	{
		case WM_CLOSE:
			{
				// Call the Window's Close method.
				if ( window->IsOpen() )
				{
					window->Close();
				}
				break;
			}
		case WM_SIZE:
			{
				// Call the Window's Resize method with the new size.
				window->Resize( LOWORD(lParam), HIWORD(lParam) );
				break;
			}
		case WM_ACTIVATEAPP:
			{
				// Call the Window's Activate or Deactivate method.
				( wParam != 0 ) ? window->Activate() : window->Deactivate();
				break;
			}
	}

	return DefWindowProc(wnd, msg, wParam, lParam);
}
