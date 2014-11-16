#include "../Include/InputHandler.hpp"

using namespace Fnd::Input;

InputHandler::InputHandler():
	_window(nullptr),
	_direct_input(nullptr),
	_keyboard(),
	_mouse(),
	_xbox()
{
}

void InputHandler::SetWindow( HWND window )
{
	_window = window;
}

bool InputHandler::Initialise()
{
	if ( !_window )
	{
		return false;
	}

	if ( FAILED( DirectInput8Create(	GetModuleHandle(0), 
										DIRECTINPUT_VERSION,
										IID_IDirectInput8,
										(void**)(&_direct_input),
										0 )))
	{
		return false;
	}

	// create keyboard input
	_keyboard.SetWindow( _window );
	_keyboard.SetDirectInputDevice( _direct_input );
	
	if ( !_keyboard.Initialise() )
	{
		return false;
	}
		
	// create mouse input
	_mouse.SetWindow( _window );
	_mouse.SetDirectInputDevice( _direct_input );
	
	if ( !_mouse.Initialise() )
	{
		return false;
	}

	// create xbox input
	_xbox.SetDirectInputDevice( _direct_input );
	if ( !_xbox.Initialise() )
	{
		return false;
	}

	return true;
}

void InputHandler::Activate()
{
	_xbox.Activate();
}

void InputHandler::Deactivate()
{ 
	_xbox.Deactivate();
}

void InputHandler::Update()
{
	_keyboard.Update();
	_mouse.Update();
	_xbox.Update();
}

const IKeyboardInput* InputHandler::GetKeyboard() const
{
	return &_keyboard;
}

const IMouseInput* InputHandler::GetMouse() const
{
	return &_mouse;
}

const IXboxInput* InputHandler::GetXbox() const
{
	return &_xbox;
}

InputHandler::~InputHandler()
{
	if ( _direct_input )
	{
		_direct_input->Release(); 
	}
}