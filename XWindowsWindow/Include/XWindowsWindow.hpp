#pragma once

#ifndef _XWINDOWSWINDOW_HPP_
#define _XWINDOWSWINDOW_HPP_

#include "../../GameComponentInterfaces/Include/IWindow.hpp"

struct Display;

namespace Fnd
{
namespace XWindowsWindow
{

class XWindowsWindow:
    public Fnd::GameComponentInterfaces::IWindow
{
    public:

		/*
			Virtual Methods inherited from IWindow.
		*/

        // Default Constructor.
		XWindowsWindow();

		// Set the title of the Window.
		void SetWindowTitle( const std::string& title );

		// Set the size of the Window.
		void SetWindowSize( unsigned int width, unsigned int height );

		void SetWindowResizable( bool resizable );

		void SetWindowFullscreen( bool fullscreen );

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
		~XWindowsWindow();

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

		Display* _display;
		Window _window;
		XVisualInfo* _visual_info;


		bool _is_initialised;

		Fnd::GameComponentInterfaces::IWindowMessageListener* _game;

		unsigned int _width;
		unsigned int _height;

		std::string _title;

		bool _is_resizable;
		bool _is_fullscreen;

		bool _is_open;
		bool _is_active;
};

}
}

#endif
