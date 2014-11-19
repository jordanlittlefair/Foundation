#pragma once

#ifndef _INPUT_XBOXINPUT_HPP_
#define _INPUT_XBOXINPUT_HPP_


#include "IXboxInput.hpp"

namespace Fnd
{
namespace Input
{

/*
	A class to handle the input from the xbox controller.
*/
class XboxInput: 
	public IXboxInput
{
	public:

		// Default constructor.
		XboxInput();

		// Set the direct input device.
		void SetDirectInputDevice( IDirectInput8* direct_input );

		// Initialise the xbox controller.
		// Returns true if successful.
		bool Initialise();

		// Activate the controllers.
		void Activate();
		
		// Deactivate the controllers.
		void Deactivate();

		// Update the xbox controller input.
		void Update();

		// Get whether or not controller[i] is connected.
		bool IsConnected( unsigned int index = 0 ) const;

		// Get whether or not a button is down.
		bool IsDown( DWORD button, unsigned int index = 0 ) const;
		
		// Get whether or not a button is up.
		bool IsUp( DWORD button, unsigned int index = 0 ) const; 
		
		// Get whether or not a button has been pressed.
		// Returns true if the button is down, but was not down in the previous update.
		bool IsPressed( DWORD button, unsigned int index = 0 ) const;
		
		// Get whether or not a button has been released.
		// Returns true if the button is up, but was not up in the previous update.
		bool IsReleased( DWORD button, unsigned int index = 0 ) const;

		// Get the value of an axis.
		float GetAxisValue( WORD axis, unsigned int index = 0 ) const;
		
		// Destructor.
		~XboxInput();

	private:

		IDirectInput8* _direct_input;

		// stores current and previous states of each controller { c1, c2, c3, c4, c1, c2, c3, c4 }
		XINPUT_STATE _controller_states[8];

		// array of booleans representing which controllers are connected
		bool _connected_controllers[4];

		XINPUT_STATE* _current_states;
		XINPUT_STATE* _previous_states;
};

}
}

#endif