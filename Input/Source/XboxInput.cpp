#include "../Include/XboxInput.hpp"

#include <cmath>

using namespace Fnd::Input;

XboxInput::XboxInput():
	_direct_input(0),
	_current_states(&_controller_states[0]),
	_previous_states(&_controller_states[4])
{
	ZeroMemory( _controller_states, sizeof(XINPUT_STATE) * 8 );

	for ( unsigned int i = 0; i < 4; ++i )
	{
		_connected_controllers[i] = false;
	}
}

void XboxInput::SetDirectInputDevice( IDirectInput8* direct_input )
{
	_direct_input = direct_input;
}

bool XboxInput::Initialise() 
{
	if ( !_direct_input ) 
	{
		return false;
	}

	//XInputEnable( true );

	// first update here to avoid errors
	_current_states = &_controller_states[0];
	_previous_states = &_controller_states[4];

	for ( unsigned int i = 0; i < 4; ++i )
	{
		_connected_controllers[i] = ERROR_DEVICE_NOT_CONNECTED != XInputGetState( i, &_current_states[i] );
	}

	return true;
}

void XboxInput::Activate() 
{
	//XInputEnable( true );
}

void XboxInput::Deactivate()
{
	//XInputEnable( false );
}

void XboxInput::Update() 
{
	{	// swap current and previous state pointers
		XINPUT_STATE* temp = _current_states;
		_current_states = _previous_states;
		_previous_states = temp;
	}

	// update all controllers; fills _connected_controllers[]
	for ( unsigned int i = 0; i < 4; ++i ) 
	{
		_connected_controllers[i] = ERROR_DEVICE_NOT_CONNECTED != XInputGetState( i, &_current_states[i] );
	}
}

bool XboxInput::IsConnected( unsigned int index ) const 
{
	return _connected_controllers[index];
}

bool XboxInput::IsDown( unsigned int button, unsigned int index ) const 
{
	return _connected_controllers[index] && ( _current_states[index].Gamepad.wButtons & button ) != 0;
}

bool XboxInput::IsUp( unsigned int button, unsigned int index ) const
{
	return _connected_controllers[index] && ( _current_states[index].Gamepad.wButtons & button ) == 0;
}

bool XboxInput::IsPressed( unsigned int button, unsigned int index ) const 
{
	return _connected_controllers[index] && ( ( _current_states[index].Gamepad.wButtons & button ) != 0 ) && ( ( _previous_states[index].Gamepad.wButtons & button ) == 0 );
}

bool XboxInput::IsReleased( unsigned int button, unsigned int index ) const 
{
	return _connected_controllers[index] && ( ( _previous_states[index].Gamepad.wButtons & button ) != 0 ) && ( ( _current_states[index].Gamepad.wButtons & button ) == 0 );
}

float XboxInput::GetAxisValue( unsigned short axis, unsigned int index ) const 
{
	// return zero if the controller is not connected
	if ( !_connected_controllers[index] ) 
	{
		return 0.0f;
	}

	switch ( axis ) {
		case XBOX_LT:
			return ( (float)_current_states[index].Gamepad.bLeftTrigger ) / 255.0f;
		case XBOX_RT:
			return ( (float)_current_states[index].Gamepad.bRightTrigger ) / 255.0f;
		case XBOX_LEFT_X:
			return abs( (float)_current_states[index].Gamepad.sThumbLX ) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? ( (float)_current_states[index].Gamepad.sThumbLX ) / 32767.0f : 0.0f;
		case XBOX_LEFT_Y:
			return abs( (float)_current_states[index].Gamepad.sThumbLY ) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? ( (float)_current_states[index].Gamepad.sThumbLY ) / 32767.0f : 0.0f;
		case XBOX_RIGHT_X:
			return abs( (float)_current_states[index].Gamepad.sThumbRX ) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? ( (float)_current_states[index].Gamepad.sThumbRX ) / 32767.0f : 0.0f;
		case XBOX_RIGHT_Y:
			return abs( (float)_current_states[index].Gamepad.sThumbRY ) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? ( (float)_current_states[index].Gamepad.sThumbRY ) / 32767.0f : 0.0f;
		default:
			return 0.0f;
	}
}

XboxInput::~XboxInput()
{
}