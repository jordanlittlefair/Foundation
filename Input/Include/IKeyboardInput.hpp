#pragma once

#ifndef _INPUT_IKEYBOARDINPUT_HPP_
#define _INPUT_IKEYBOARDINPUT_HPP_


//#include <Windows.h>

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
		virtual bool IsDown( unsigned int key ) const = 0;
		
		// Get whether or not a key is up.
		virtual bool IsUp( unsigned int key ) const = 0;
		
		// Get whether or not a key has been pressed.
		// Returns true if the key is down, but was not down in the previous update.
		virtual bool IsPressed( unsigned int key ) const = 0;
		
		// Get whether or not a key has been released.
		// Returns true if the key is up, but was not up in the previous update.
		virtual bool IsReleased( unsigned int key ) const = 0;
};

}
}


#endif