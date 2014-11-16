#pragma once

#ifndef _KEYBOARDINPUT_HPP_
#define _KEYBOARDINPUT_HPP_


#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif
#include <dinput.h>
#include "IKeyboardInput.hpp"

namespace Fnd
{
namespace Input
{

/*
	A class to handle the input from the keyboard.
*/
class KeyboardInput:
	public IKeyboardInput
{
	public:
		
		// Default constructor.
		KeyboardInput();
		
		// Set the window handle;
		void SetWindow( HWND window );
		
		// Set the direct input device.
		void SetDirectInputDevice( IDirectInput8* direct_input );
		
		// Initialise the keyboard input.
		// Returns true if successful.
		bool Initialise();
		
		// Update the ksyboard input.
		void Update();

		// Get whether or not a key is down.
		bool IsDown( DWORD key ) const;
		
		// Get whether or not a key is up.
		bool IsUp( DWORD key ) const;
		
		// Get whether or not a key has been pressed.
		// Returns true if the key is down, but was not down in the previous update.
		bool IsPressed( DWORD key ) const;
		
		// Get whether or not a key has been released.
		// Returns true if the key is up, but was not up in the previous update.
		bool IsReleased( DWORD key ) const;
		
		// Destructor.
		~KeyboardInput();

	private:

		HWND _window;

		IDirectInput8* _direct_input;

		IDirectInputDevice8* _keyboard;

		unsigned char _keyboard_states[512];

		unsigned char* _current_state;
		unsigned char* _previous_state;
};

}
}

#endif