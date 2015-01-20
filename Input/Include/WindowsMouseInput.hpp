#pragma once

#ifndef _INPUT_WINDOWSMOUSEINPUT_HPP_
#define _INPUT_WINDOWSMOUSEINPUT_HPP_

#include <Windows.h>

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif
#include <dinput.h>

#include "MouseInputBase.hpp"

namespace Fnd
{
namespace Input
{

/*
	A class to handle the input from the keyboard.
*/
class WindowsMouseInput: 
	public MouseInputBase
{
	public:
		
		WindowsMouseInput();
		
		void SetWindow( HWND window );
		
		void SetDirectInputDevice( IDirectInput8* direct_input );
		
		bool Initialise();
		
		~WindowsMouseInput();

	protected:

		MouseInputBase::MouseState GetNextState();

	private:

		HWND _window;

		IDirectInput8* _direct_input;

		IDirectInputDevice8* _mouse;
};

}
}

#endif