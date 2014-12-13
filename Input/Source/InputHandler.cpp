#include "../Include/InputHandler.hpp"

#ifdef _WIN32
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif
#include <dinput.h>
#endif

using namespace Fnd::Input;

InputHandler::InputHandler():
    _windows_data(),
	_keyboard(),
	_mouse(),
	_gamepad()
{

}

void InputHandler::SetWindow( void* window )
{
	_windows_data._window = window;
}

#ifdef _WIN32
#include "../Include/WindowsMouseInput.hpp"
#include "../Include/WindowsKeyboardInput.hpp"
#include "../Include/WindowsGamePadInput.hpp"
#else
#include "../Include/MacMouseInput.hpp"
#include "../Include/MacKeyboardInput.hpp"
#include "../Include/MacGamePadInput.hpp"
#endif

bool InputHandler::Initialise()
{
#ifdef _WIN32
	if ( !_window )
	{
		return false;
	}

	std::unique_ptr<WindowsMouseInput> mouse( new WindowsMouseInput() );
	std::unique_ptr<WindowsKeyboardInput> keyboard( new WindowsKeyboardInput() );
	std::unique_ptr<WindowsGamePadInput> gamepad( new WindowsGamePadInput() );
	
	if ( FAILED( DirectInput8Create(	GetModuleHandle(0), 
										DIRECTINPUT_VERSION,
										IID_IDirectInput8,
										(void**)(&_direct_input),
										0 )))
	{
		return false;
	}

	// create keyboard input
	keyboard->SetWindow( (HWND)_window );
	keyboard->SetDirectInputDevice( _direct_input );
	
	if ( !keyboard->Initialise() )
	{
		return false;
	}
		
	// create mouse input
	mouse->SetWindow( (HWND)_window );
	mouse->SetDirectInputDevice( _direct_input );
	
	if ( !mouse->Initialise() )
	{
		return false;
	}

	// create xbox input
	gamepad->SetDirectInputDevice( _direct_input );
	if ( !gamepad->Initialise() )
	{
		return false;
	}

	_mouse = std::move(mouse);
	_keyboard = std::move(keyboard);
	_gamepad = std::move(gamepad);
	
	return true;
#else

    std::unique_ptr<MacMouseInput> mouse( new MacMouseInput() );
    std::unique_ptr<MacKeyboardInput> keyboard( new MacKeyboardInput() );
    std::unique_ptr<MacGamePadInput> gamepad( new MacGamePadInput() );

    _mouse = std::move(mouse);
    _keyboard = std::move(keyboard);
    _gamepad = std::move(gamepad);
    
    return true;
#endif
}

void InputHandler::Update()
{
	_keyboard->Update();
	_mouse->Update();
	_gamepad->Update();
}

const IKeyboardInput* InputHandler::GetKeyboard() const
{
	return _keyboard.get();
}

const IMouseInput* InputHandler::GetMouse() const
{
	return _mouse.get();
}

const IGamePadInput* InputHandler::GetGamePad() const
{
	return _gamepad.get();
}

InputHandler::~InputHandler()
{
#ifdef _WIN32
	if ( _windows_data._direct_input )
	{
		((IDirectInput8*)_windows_data._direct_input))->Release();
	}
#endif
}

InputHandler::WindowsData::WindowsData():
    _window(nullptr),
    _direct_input(nullptr)
{
}