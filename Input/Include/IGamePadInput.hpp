#pragma once

#ifndef _INPUT_IGAMEPADINPUT_HPP_
#define _INPUT_IGAMEPADINPUT_HPP_

#include "GamePadButtons.hpp"

namespace Fnd
{
namespace Input
{

/*
	Interface to gamepad input.
*/
class IGamePadInput
{
	public:
	
		// Get whether or not controller[i] is connected.
		virtual bool IsConnected( unsigned int index = 0 ) const = 0;

		// Get whether or not a button is down.
		virtual bool IsDown( Xbox::Button button, unsigned int index = 0 ) const = 0;
		
		// Get whether or not a button is up.
		virtual bool IsUp( Xbox::Button button, unsigned int index = 0 ) const = 0;
		
		// Get whether or not a button has been pressed.
		// Returns true if the button is down, but was not down in the previous update.
		virtual bool IsPressed( Xbox::Button button, unsigned int index = 0 ) const = 0;
		
		// Get whether or not a button has been released.
		// Returns true if the button is up, but was not up in the previous update.
		virtual bool IsReleased( Xbox::Button button, unsigned int index = 0 ) const = 0;

		// Get the value of an axis.
		virtual float GetAxisValue( Xbox::Axis axis, unsigned int index = 0 ) const = 0;
};

}
}

#endif