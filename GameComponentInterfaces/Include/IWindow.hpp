#pragma once

#ifndef _GAMECOMPONENTINTERFACES_IWINDOW_HPP_
#define _GAMECOMPONENTINTERFACES_IWINDOW_HPP_

#include <string>

namespace Fnd
{
namespace GameComponentInterfaces
{

class IWindowMessageListener;

/**
	Base class for interacting with window implementations.

	Handles window messages.
*/
class IWindow
{
	public:

		/**
			Set a pointer Game's IWindowMessafeListener interface.
			The window calls IWindowMessageListener methods when the window's state changes.
			@param game A pointer to the IWindowMessageListener interface of the game.
		*/
		virtual void SetWindowMessageListener( IWindowMessageListener* game ) = 0;

		/**
			Set the window's title.
			@param title The title of the window.
		*/
		virtual void SetWindowTitle( const std::string& title ) = 0;

		/**
			Set the size of the window.
			@param width The desired width of the window.
			@param height The desired height of the window.
		*/
		virtual void SetWindowSize( unsigned int width, unsigned int height ) = 0;

		/**
			Set whether or not the window is resizable.
			@param resizable Whether the is window resizable or not.
		*/
		virtual void SetWindowResizable( bool resizable ) = 0;

		/**
			Set whether or not the window starts fullscreen.
			@param resizable Whether the is window starts fullscreen or not.
		*/
		virtual void SetWindowFullscreen( bool fullscreen ) = 0;

		/**
			Initialise the window.
			@return Returns true if successful.
		*/
		virtual bool Initialise() = 0;

		/**
			Get a pointer to the HWND window handle.
			@note Only implemented for Win32 windows.\n
			All other implementations return null.
			@return Returns the window handle.
		*/
		virtual void* GetHWND() const = 0;

		/**
			Get a pointer to the HCD device context handle.
			@note Only implemented for Win32.\n
			All other implementations return null.
			@return Returns the device context handle.
		*/
		virtual void* GetHDC() const = 0;
    
        virtual void* GetXWindowsDisplay() const = 0;
        
        virtual unsigned long GetXWindowsWindow() const = 0;

		/**
			Show the window.
		*/
		virtual void Show() = 0;

		/**
			Get whether or not the window is open.
			@return Returns true if the window is open.
		*/
		virtual bool IsOpen() const = 0;

		/**
			Get whether or not the window is active.
			@return Returns true if the window is active.
		*/
		virtual bool IsActive() const = 0;

		/**
			Receive and handle window messages; close, resize, paint, activate etc.
		*/
		virtual void HandleWindowMessages() = 0;

		/**
			Set whether or not to show the cursor.
			@param show True to show the cursor, false to hide the cursor.
		*/
		virtual void ShowCursor( bool show ) = 0;

		/**
			Close the window.
		*/
		virtual void CloseWindow() = 0;

		virtual ~IWindow() {};
};

}
}

#endif