#pragma once

#ifndef _INPUT_MOUSEINPUT_HPP_
#define _INPUT_MOUSEINPUT_HPP_


#include <Windows.h>

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

#include <dinput.h>
#include "IMouseInput.hpp"

namespace Fnd
{
namespace Input
{

/*
	A class to handle the input from the keyboard.
*/
class MouseInput: 
	public IMouseInput
{
	public:
		
		// Default constructor.
		MouseInput();
		
		// Set the window handle.
		void SetWindow( HWND window );
		
		// Set the direct input device.
		void SetDirectInputDevice( IDirectInput8* direct_input );
		
		// Initialise the mouse input.
		// Returns true if successful.
		bool Initialise();
		
		// Update the mouse input.
		void Update();

		// Methods inherited from IMouseInput
		// Get whether or not the left button is down.
		 bool IsDownLeft() const;
		
		// Get whether or not the right button is down.
		bool IsDownRight() const;
		
		// Get whether or not the middle button is down.
		bool IsDownMiddle() const;

		// Get whether or not the left button is up.
		bool IsUpLeft() const;
		
		// Get whether or not the right button is up.
		bool IsUpRight() const;
		
		// Get whether or not the middle button is up.
		bool IsUpMiddle() const;

		// Get whether or not the left button has been pressed.
		// Returns true if the button is down, but was not down in the previous update.
		bool IsPressedLeft() const;
		
		// Get whether or not the right button has been pressed.
		// Returns true if the button is down, but was not down in the previous update.
		bool IsPressedRight() const;
		
		// Get whether or not the middle button has been pressed.
		// Returns true if the button is down, but was not down in the previous update.
		bool IsPressedMiddle() const;

		// Get whether or not the left button has been released.
		// Returns true if the button is up, but was not up in the previous update.
		bool IsReleasedLeft() const;
		
		// Get whether or not the right button has been released.
		// Returns true if the button is up, but was not up in the previous update.
		bool IsReleasedRight() const;
		
		// Get whether or not the middle button has been released.
		// Returns true if the button is up, but was not up in the previous update.
		bool IsReleasedMiddle() const;

		// Get the X distance moved by the mouse since last update.
		int GetMouseDeltaX() const;
		
		// Get the Y distance moved by the mouse since last update.
		int GetMouseDeltaY() const;
		
		// Get the distance moved by the mouse wheel since last update.
		int GetMouseDeltaWheel() const;
		
		// Destructor.
		~MouseInput();

	private:

		HWND _window;

		IDirectInput8* _direct_input;

		IDirectInputDevice8* _mouse;

		DIMOUSESTATE _mouse_states[2];

		DIMOUSESTATE* _current_state;
		DIMOUSESTATE* _previous_state;
};

}
}

#endif