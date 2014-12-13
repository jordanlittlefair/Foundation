#pragma once

#ifndef _INPUT_WINDOWSGAMEPADINPUT_HPP_
#define _INPUT_WINDOWSGAMEPADINPUT_HPP_

#include "GamePadInputBase.hpp"

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif
#include <dinput.h>

namespace Fnd
{
namespace Input
{

/*
	A class to handle the input from the xbox controller.
*/
class WindowsGamePadInput: 
	public GamePadInputBase
{
	public:

		WindowsGamePadInput();

		void SetDirectInputDevice( IDirectInput8* direct_input );

		bool Initialise();
		
	protected:
	
		GamePadInputBase::GamePadState GetNextState();

	private:

		IDirectInput8* _direct_input;
};

}
}

#endif