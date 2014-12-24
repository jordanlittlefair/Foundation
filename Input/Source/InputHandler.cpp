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
    _xwindows_data(),
	_keyboard(),
	_mouse(),
	_gamepad()
{

}

void InputHandler::SetWindow( void* window )
{
	_windows_data._window = window;
}

void InputHandler::SetDisplay( void* display )
{
    _xwindows_data.display = display;
}

#ifdef _WIN32
#include "../Include/WindowsMouseInput.hpp"
#include "../Include/WindowsKeyboardInput.hpp"
#include "../Include/WindowsGamePadInput.hpp"
#else
#ifdef __APPLE__
#include "../Include/MacMouseInput.hpp"
#include "../Include/MacKeyboardInput.hpp"
#include "../Include/MacGamePadInput.hpp"
#endif
#include "../Include/XWindowsMouseInput.hpp"
#include "../Include/XWindowsKeyboardInput.hpp"
#include "../Include/XWindowsGamePadInput.hpp"
#endif

bool InputHandler::Initialise()
{
#ifdef _WIN32
	if ( !_windows_data._window )
	{
		return false;
	}

	std::unique_ptr<WindowsMouseInput> mouse( new WindowsMouseInput() );
	std::unique_ptr<WindowsKeyboardInput> keyboard( new WindowsKeyboardInput() );
	std::unique_ptr<WindowsGamePadInput> gamepad( new WindowsGamePadInput() );
	
	if ( FAILED( DirectInput8Create(	GetModuleHandle(0), 
										DIRECTINPUT_VERSION,
										IID_IDirectInput8,
										(void**)(&_windows_data._direct_input),
										0 )))
	{
		return false;
	}

	// create keyboard input
	keyboard->SetWindow( (HWND)_windows_data._window );
	keyboard->SetDirectInputDevice( (IDirectInput8*)_windows_data._direct_input );
	
	if ( !keyboard->Initialise() )
	{
		return false;
	}
		
	// create mouse input
	mouse->SetWindow( (HWND)_windows_data._window );
	mouse->SetDirectInputDevice( (IDirectInput8*)_windows_data._direct_input );
	
	if ( !mouse->Initialise() )
	{
		return false;
	}

	// create xbox input
	gamepad->SetDirectInputDevice( (IDirectInput8*)_windows_data._direct_input );
	if ( !gamepad->Initialise() )
	{
		return false;
	}

	_mouse = std::move(mouse);
	_keyboard = std::move(keyboard);
	_gamepad = std::move(gamepad);
	
	return true;
#else

    std::unique_ptr<XWindowsMouseInput> mouse( new XWindowsMouseInput() );
    std::unique_ptr<XWindowsKeyboardInput> keyboard( new XWindowsKeyboardInput() );
    std::unique_ptr<XWindowsGamePadInput> gamepad( new XWindowsGamePadInput() );

    keyboard->SetDisplay(_xwindows_data.display);
    
    mouse->Initialise();
    keyboard->Initialise();
    gamepad->Initialise();
    
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
		((IDirectInput8*)_windows_data._direct_input)->Release();
	}
#endif
}

InputHandler::WindowsData::WindowsData():
    _window(nullptr),
    _direct_input(nullptr)
{
}

InputHandler::XWindowsData::XWindowsData():
    display(nullptr)
{
}