#pragma once

#ifndef _INPUT_IMOUSEINPUT_HPP_
#define _INPUT_IMOUSEINPUT_HPP_

namespace Fnd
{
namespace Input
{

/*
	Interface to mouse input.
*/
class IMouseInput
{
	public:

		// Get whether or not the left button is down.
		virtual bool IsDownLeft() const = 0;
		
		// Get whether or not the right button is down.
		virtual bool IsDownRight() const = 0;
		
		// Get whether or not the middle button is down.
		virtual bool IsDownMiddle() const = 0;

		// Get whether or not the left button is up.
		virtual bool IsUpLeft() const = 0;
		
		// Get whether or not the right button is up.
		virtual bool IsUpRight() const = 0;
		
		// Get whether or not the middle button is up.
		virtual bool IsUpMiddle() const = 0;

		// Get whether or not the left button has been pressed.
		// Returns true if the button is down, but was not down in the previous update.
		virtual bool IsPressedLeft() const = 0;
		
		// Get whether or not the right button has been pressed.
		// Returns true if the button is down, but was not down in the previous update.
		virtual bool IsPressedRight() const = 0;
		
		// Get whether or not the middle button has been pressed.
		// Returns true if the button is down, but was not down in the previous update.
		virtual bool IsPressedMiddle() const = 0;

		// Get whether or not the left button has been released.
		// Returns true if the button is up, but was not up in the previous update.
		virtual bool IsReleasedLeft() const = 0;
		
		// Get whether or not the right button has been released.
		// Returns true if the button is up, but was not up in the previous update.
		virtual bool IsReleasedRight() const = 0;
		
		// Get whether or not the middle button has been released.
		// Returns true if the button is up, but was not up in the previous update.
		virtual bool IsReleasedMiddle() const = 0;

		// Get the X distance moved by the mouse since last update.
		virtual int GetMouseDeltaX() const = 0;
		
		// Get the Y distance moved by the mouse since last update.
		virtual int GetMouseDeltaY() const = 0;
		
		// Get the distance moved by the mouse wheel since last update.
		virtual int GetMouseDeltaWheel() const = 0;
};

}
}

#endif