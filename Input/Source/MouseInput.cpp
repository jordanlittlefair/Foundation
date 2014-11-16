#include "../Include/MouseInput.hpp"

using namespace Fnd::Input;

MouseInput::MouseInput():
	_window(0),
	_direct_input(0),
	_mouse(0),
	_current_state(&_mouse_states[0]),
	_previous_state(&_mouse_states[1])
{
	ZeroMemory( &_mouse_states[0], sizeof(DIMOUSESTATE) * 2 );
}

void MouseInput::SetWindow( HWND window )
{
	_window = window;
}

void MouseInput::SetDirectInputDevice( IDirectInput8* direct_input )
{
	_direct_input = direct_input;
}

bool MouseInput::Initialise()
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

	// first update is here to avoid errors with zero data
	_current_state = &_mouse_states[0];
	_previous_state = &_mouse_states[1];

	_mouse->Acquire();
	_mouse->GetDeviceState( sizeof(DIMOUSESTATE), _current_state );

	return true;
}

void MouseInput::Update() 
{
	{	// swap current and previous state pointers
		DIMOUSESTATE* temp = _current_state;
		_current_state = _previous_state;
		_previous_state = temp;
	}

	// fill current state with data
	_mouse->Acquire();
	_mouse->GetDeviceState( sizeof(DIMOUSESTATE), _current_state );
}

bool MouseInput::IsDownLeft() const 
{
	return _current_state->rgbButtons[0] != 0;
}

bool MouseInput::IsDownRight() const 
{
	return _current_state->rgbButtons[1] != 0;
}

bool MouseInput::IsDownMiddle() const 
{
	return _current_state->rgbButtons[2] != 0;
}

bool MouseInput::IsUpLeft() const 
{
	return _current_state->rgbButtons[0] == 0;
}

bool MouseInput::IsUpRight() const 
{
	return _current_state->rgbButtons[1] == 0;
}

bool MouseInput::IsUpMiddle() const
{
	return _current_state->rgbButtons[2] == 0;
}

bool MouseInput::IsPressedLeft() const
{
	return _current_state->rgbButtons[0] != 0 && _previous_state->rgbButtons[0] == 0;
}

bool MouseInput::IsPressedRight() const 
{
	return _current_state->rgbButtons[1] != 0 && _previous_state->rgbButtons[1] == 0;
}

bool MouseInput::IsPressedMiddle() const 
{
	return _current_state->rgbButtons[2] != 0 && _previous_state->rgbButtons[2] == 0;
}

bool MouseInput::IsReleasedLeft() const 
{
	return _current_state->rgbButtons[0] == 0 && _previous_state->rgbButtons[0] != 0;
}

bool MouseInput::IsReleasedRight() const 
{
	return _current_state->rgbButtons[1] == 0 && _previous_state->rgbButtons[1] != 0;
}

bool MouseInput::IsReleasedMiddle() const
{
	return _current_state->rgbButtons[2] == 0 && _previous_state->rgbButtons[2] != 0;
}

int MouseInput::GetMouseDeltaX() const 
{
	return (int)_current_state->lX;
}

int MouseInput::GetMouseDeltaY() const 
{
	return (int)_current_state->lY;
}

int MouseInput::GetMouseDeltaWheel() const 
{
	return (int)_current_state->lZ;
}

MouseInput::~MouseInput()
{
	if ( _mouse )
	{ 
		_mouse->Unacquire(); 
		_mouse->Release();
	}
}