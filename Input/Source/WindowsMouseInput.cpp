#include "../Include/WindowsMouseInput.hpp"

using namespace Fnd::Input;

WindowsMouseInput::WindowsMouseInput():
	_window(nullptr),
	_direct_input(nullptr),
	_mouse(nullptr)
{
}

void WindowsMouseInput::SetWindow( HWND window )
{
	_window = window;
}

void WindowsMouseInput::SetDirectInputDevice( IDirectInput8* direct_input )
{
	_direct_input = direct_input;
}

bool WindowsMouseInput::Initialise()
{
	if ( !_window )
	{
		return false;
	}

	if ( !_direct_input )
	{
		return false;
	}

	if ( !SUCCEEDED( _direct_input->CreateDevice(	GUID_SysMouse,
													&_mouse,
													0 ) ) ) 
	{
		return false;
	}

	// set mouse format and stuff
	if ( FAILED( _mouse->SetDataFormat( &c_dfDIMouse ) ) ) 
	{
		return false;
	}
	if ( FAILED( _mouse->SetCooperativeLevel( _window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) )
	{
		return false;
	}

	_mouse->Acquire();

	return true;
}

WindowsMouseInput::~WindowsMouseInput()
{
	if ( _mouse )
	{ 
		_mouse->Unacquire(); 
		_mouse->Release();
	}
}

WindowsMouseInput::MouseState WindowsMouseInput::GetNextState()
{
	WindowsMouseInput::MouseState state;
	memset( &state, 0, sizeof(state) );

	DIMOUSESTATE di_mouse_state;
	memset( &di_mouse_state, 0, sizeof(DIMOUSESTATE) );

	_mouse->Acquire();
	_mouse->GetDeviceState( sizeof(DIMOUSESTATE), &di_mouse_state );

	state.left_button =	( di_mouse_state.rgbButtons[0] & 0x80 ) != 0;
    state.right_button = ( di_mouse_state.rgbButtons[1] & 0x80 ) != 0;
    state.middle_button = ( di_mouse_state.rgbButtons[2] & 0x80 ) != 0;
    state.delta_x =	di_mouse_state.lX;
    state.delta_y = di_mouse_state.lY;
    state.delta_wheel = di_mouse_state.lZ;

	return state;
}