#pragma once

#ifndef _INPUT_IINPUT_HPP_
#define _INPUT_IINPUT_HPP_


#include "IKeyboardInput.hpp"
#include "IMouseInput.hpp"
#include "IGamePadInput.hpp"

namespace Fnd
{
namespace Input
{

/*
	Interface passed classes which use input.
*/
class IInput
{
	public:
		
		// Get the keyboard input.
		virtual const IKeyboardInput* GetKeyboard() const = 0;
		
		// Get the mouse input.
		virtual const IMouseInput* GetMouse() const = 0;
		
		// Get the xbox input.
		virtual const IGamePadInput* GetGamePad() const = 0;
};

}
}

#endif