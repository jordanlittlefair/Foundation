#pragma once

#ifndef _WIN32WINDOW_HPP_
#define _WIN32WINDOW_HPP_

#ifndef	WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <string>

#include "../../GameComponentInterfaces/Include/IWindow.hpp"

namespace Fnd
{
namespace Win32Window
{

/*
	A Window which displays the game and receives messages from the OS (close, resize etc).
*/
class Win32Window:
	public Fnd::GameComponentInterfaces::IWindow
{
	public:

		// An enum to describe the 'style' of the window.
		enum Win32WindowStyle
		{
			Default_Window_Style =		0,
			Resizable_Window_Style =	( WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME ),
			Fixed_Size_Window_Style =	( WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX )
		};

		// Default Constructor.
		Win32Window();

		// Set the title of the Window.
		void SetWindowTitle( const std::string& title );

		// Set the size of the Window.
		void SetWindowSize( unsigned int width, unsigned int height );

		void SetWindowResizable( bool resizable );

		void SetWindowFullscreen( bool fullscreen );
		
		void SetStyle( Win32WindowStyle style );

		/*
			Virtual Methods inherited from IWindow.
		*/

		// Set a pointer to the IWindowMessageListener inferface of the Game component.
		// The window calls IWindowMessageListener methods when the Window's state changes.
		// This method is called by the Game class's initialise method.
		void SetWindowMessageListener( Fnd::GameComponentInterfaces::IWindowMessageListener* game );

		// Initialise the Window.
		// Returns true if successful.
		bool Initialise();
		
		// Returns a pointer to the HWND window handle.
		void* GetHWND() const;

		/**
			Get a pointer to the HCD device context handle.
			@note Only implemented for Win32.\n
			All other implementations return null.
			@return Returns the device context handle.
		*/
		void* GetHDC() const;

		// Show the window.
		void Show();

		// Return whether or not the Window is open.
		bool IsOpen() const;

		// Return whether or not the Window is active.
		bool IsActive() const;

		// Receive and handle window messages; close, resize, paint, activate etc.
		void HandleWindowMessages();

		// Set whether or not to show the cursor.
		void ShowCursor( bool show );

		// Close the window.
		void CloseWindow();

		// Destructor.
		~Win32Window();

	protected:

		// Activate the Window and call the Games OnWindowActivate method.
		// Called when the Window receives WM_ACTIVATEAPP (true) in wndProc.
		void Activate();

		// Deactivate the Window and call the Games OnWindowDeactivate method.
		// Called when the window receives WM_ACTIVATEAPP (false) in wndProc.
		void Deactivate();

		// Resize the Window and call the Games onWindowResize method with the new size.
		// Called when the window receives WM_SIZE in wndProc.
		void Resize( unsigned int width, unsigned int height );

		// Close the Window and call the Games OnWindowClose method.
		// Called when the window receives WM_CLOSE in wndProc()
		void Close();

	private:

		// Receive OS messages ( activate, close, etc. ).
		static LRESULT WINAPI wndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam );

		bool _is_initialised;

		HWND _window;

		Fnd::GameComponentInterfaces::IWindowMessageListener* _game;
	
		unsigned int _width;
		unsigned int _height;

		Win32WindowStyle _style;

		std::string _title;

		bool _is_open;
		bool _is_active;
};

}
}

#endif