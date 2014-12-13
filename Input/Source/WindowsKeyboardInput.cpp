#include "../Include/WindowsKeyboardInput.hpp"

using namespace Fnd::Input;

WindowsKeyboardInput::WindowsKeyboardInput():
	_window(nullptr),
	_direct_input(nullptr),
	_keyboard(nullptr)
{
}

void WindowsKeyboardInput::SetWindow( HWND window )
{
	_window = window;
}

void WindowsKeyboardInput::SetDirectInputDevice( IDirectInput8* direct_input )
{
	_direct_input = direct_input;
}

bool WindowsKeyboardInput::Initialise()
{
	if ( !_window ) 
	{
		return false;
	}

	if ( !_direct_input ) 
	{
		return false;
	}

	if ( FAILED( _direct_input->CreateDevice(	GUID_SysKeyboard, 
												&_keyboard,
												0 ) ) )
	{
		return false;
	}

	// set keyboard format and stuff
	if ( FAILED( _keyboard->SetDataFormat( &c_dfDIKeyboard ) ) ) 
	{
		return false;
	}
	if ( FAILED( _keyboard->SetCooperativeLevel( _window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) )
	{
		return false;
	}

	_keyboard->Acquire();

	return true;
}

WindowsKeyboardInput::~WindowsKeyboardInput()
{
	if ( _keyboard )
	{ 
		_keyboard->Unacquire();
		_keyboard->Release();
	}
}

KeyboardInputBase::KeyboardState WindowsKeyboardInput::GetNextState()
{
	KeyboardInputBase::KeyboardState state;
	memset( &state, 0, sizeof(state) );
	
	return state;
}