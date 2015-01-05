#pragma once

#ifndef _INPUT_WINDOWSKEYBOARDINPUT_HPP_
#define _INPUT_WINDOWSKEYBOARDINPUT_HPP_

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif
#include <dinput.h>

#include "KeyboardInputBase.hpp"

namespace Fnd
{
namespace Input
{

/*
	A class to handle the input from the keyboard.
*/
class WindowsKeyboardInput:
	public KeyboardInputBase
{
	public:
		
		WindowsKeyboardInput();
		
		void SetWindow( HWND window );
		
		void SetDirectInputDevice( IDirectInput8* direct_input );
		
		bool Initialise();
		
		~WindowsKeyboardInput();
	
	protected:

		KeyboardInputBase::KeyboardState GetNextState();

	private:

		HWND _window;

		IDirectInput8* _direct_input;

		IDirectInputDevice8* _keyboard;
};

}
}

#endif