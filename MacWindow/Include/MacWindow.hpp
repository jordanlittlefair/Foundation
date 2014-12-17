#pragma once

#ifndef _MACWINDOW_MACWINDOW_HPP_
#define _MACWINDOW_MACWINDOW_HPP_

#include <string>

#include "../../GameComponentInterfaces/Include/IWindow.hpp"

namespace Fnd
{
namespace MacWindow
{

/*
    A Window which displays the game and receives messages from the OS (close, resize etc).
*/
class MacWindow:
    public Fnd::GameComponentInterfaces::IWindow
{
    public:
        
        // Default Constructor.
        MacWindow();
        
        // Set the title of the Window.
        void SetWindowTitle( const std::string& title );
        
        // Set the size of the Window.
        void SetWindowSize( unsigned int width, unsigned int height );
        
        void SetWindowResizable( bool resizable );
        
        void SetWindowFullscreen( bool fullscreen );
        
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
        ~MacWindow();
};

}
}

#endif