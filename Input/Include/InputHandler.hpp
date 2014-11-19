#pragma once

#ifndef _INPUT_INPUTHANDLER_HPP_
#define _INPUT_INPUTHANDLER_HPP_

#include "IInput.hpp"
#include "KeyboardInput.hpp"
#include "MouseInput.hpp"
#include "XboxInput.hpp"

struct IDirectInput8;

namespace Fnd
{
namespace Input
{

/*
	A class to handle the input from the keyboard, mouse and xbox controller.
*/
class InputHandler: 
	public IInput
{
	public:

		// Default constructor.
		InputHandler();

		// Set the window handle.
		void SetWindow( HWND window );

		// Initialise the input handler.
		// Returns true if successful
		bool Initialise();

		// Activate the input.
		void Activate();
		
		// Deactivate the input.
		void Deactivate();

		// Update the input.
		void Update();

		// Get the keyboard input.
		const IKeyboardInput* GetKeyboard() const;
		
		// Get the mouse input.
		const IMouseInput* GetMouse() const;
		
		// Get the xbox input.
		const IXboxInput* GetXbox() const;
		
		// Destructor.
		~InputHandler();

	private:

		HWND _window;

		IDirectInput8* _direct_input;

		KeyboardInput _keyboard;
		MouseInput _mouse;
		XboxInput _xbox;
};

}
}

#endif