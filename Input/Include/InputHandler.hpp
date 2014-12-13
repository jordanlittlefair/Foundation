#pragma once

#ifndef _INPUT_INPUTHANDLER_HPP_
#define _INPUT_INPUTHANDLER_HPP_

#include <memory>

#include "IInput.hpp"
#include "KeyboardInputBase.hpp"
#include "MouseInputBase.hpp"
#include "GamePadInputBase.hpp"

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

        struct WindowsData
        {
            WindowsData();
            
            void* _window;
            void* _direct_input;
        };
    
        WindowsData _windows_data;

		std::unique_ptr<KeyboardInputBase> _keyboard;
		std::unique_ptr<MouseInputBase> _mouse;
		std::unique_ptr<GamePadInputBase> _gamepad;
};

}
}

#endif