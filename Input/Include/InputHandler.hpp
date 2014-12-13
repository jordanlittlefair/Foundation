#pragma once

#ifndef _INPUT_INPUTHANDLER_HPP_
#define _INPUT_INPUTHANDLER_HPP_

#include <memory>

#include "IInput.hpp"
#include "KeyboardInputBase.hpp"
#include "MouseInputBase.hpp"
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
	A class to handle the input from the keyboard, mouse and gamepad.
*/
class InputHandler: 
	public IInput
{
	public:

		InputHandler();

		void SetWindow( void* window );

		bool Initialise();

		void Update();

		const IKeyboardInput* GetKeyboard() const;
		
		const IMouseInput* GetMouse() const;
		
		const IGamePadInput* GetGamePad() const;
		
		~InputHandler();

	private:

		// Make these optional/internal impl- only needed for windows
		void* _window;

		IDirectInput8* _direct_input;

		std::unique_ptr<KeyboardInputBase> _keyboard;
		std::unique_ptr<MouseInputBase> _mouse;
		std::unique_ptr<GamePadInputBase> _gamepad;
};

}
}

#endif