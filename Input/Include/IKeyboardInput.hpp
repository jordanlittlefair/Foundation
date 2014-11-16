#pragma once

#ifndef _IKEYBOARDINPUT_HPP_
#define _IKEYBOARDINPUT_HPP_


#include <Windows.h>

namespace Fnd
{
namespace Input
{

/*
	Interface to keyboard input.
*/
class IKeyboardInput
{
	public:

		// Get whether or not a key is down.
		virtual bool IsDown( DWORD key ) const = 0;
		
		// Get whether or not a key is up.
		virtual bool IsUp( DWORD key ) const = 0;
		
		// Get whether or not a key has been pressed.
		// Returns true if the key is down, but was not down in the previous update.
		virtual bool IsPressed( DWORD key ) const = 0;
		
		// Get whether or not a key has been released.
		// Returns true if the key is up, but was not up in the previous update.
		virtual bool IsReleased( DWORD key ) const = 0;
};

}
}


#endif