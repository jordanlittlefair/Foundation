#pragma once

#ifndef _IXBOXINPUT_HPP_
#define _IXBOXINPUT_HPP_


#include "GamePadButtons.hpp"

namespace Fnd
{
namespace Input
{

/*
	Interface to xbox controller input.
*/
class IXboxInput
{
	public:
	
		// Get whether or not controller[i] is connected.
		virtual bool IsConnected( unsigned int index = 0 ) const = 0;

		// Get whether or not a button is down.
		virtual bool IsDown( DWORD button, unsigned int index = 0 ) const = 0;
		
		// Get whether or not a button is up.
		virtual bool IsUp( DWORD button, unsigned int index = 0 ) const = 0;
		
		// Get whether or not a button has been pressed.
		// Returns true if the button is down, but was not down in the previous update.
		virtual bool IsPressed( DWORD button, unsigned int index = 0 ) const = 0;
		
		// Get whether or not a button has been released.
		// Returns true if the button is up, but was not up in the previous update.
		virtual bool IsReleased( DWORD button, unsigned int index = 0 ) const = 0;

		// Get the value of an axis.
		virtual float GetAxisValue( WORD axis, unsigned int index = 0 ) const = 0;
};

}
}

#endif