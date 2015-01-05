#include "../Include/WindowsGamePadInput.hpp"

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

#include <dinput.h>
#include <XInput.h>

#include <cmath>

using namespace Fnd::Input;

WindowsGamePadInput::WindowsGamePadInput():
	_direct_input(nullptr)
{
}

void WindowsGamePadInput::SetDirectInputDevice( IDirectInput8* direct_input )
{
	_direct_input = direct_input;
}

bool WindowsGamePadInput::Initialise() 
{
	if ( !_direct_input ) 
	{
		return false;
	}
	
	return true;
}

GamePadInputBase::GamePadState WindowsGamePadInput::GetNextState()
{
	GamePadState gamepad_state;
	memset( &gamepad_state, 0, sizeof(GamePadState) );

	for ( unsigned int i = 0; i < 4; ++i )
	{
		XINPUT_STATE xinput_state;
		memset( &xinput_state, 0, sizeof(XINPUT_STATE) );

		auto res = XInputGetState( i, &xinput_state );

		if ( res == ERROR_DEVICE_NOT_CONNECTED )
		{
			gamepad_state.instances[i].is_connected = false;
			continue;
		}
		
		// Buttons
		gamepad_state.instances[i].buttons[Xbox::Up] = ( xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP ) != 0;
		gamepad_state.instances[i].buttons[Xbox::Down] = ( xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN ) != 0;
		gamepad_state.instances[i].buttons[Xbox::Left] = ( xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT ) != 0;
		gamepad_state.instances[i].buttons[Xbox::Right] = ( xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT ) != 0;
		gamepad_state.instances[i].buttons[Xbox::Start] = ( xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_START ) != 0;
		gamepad_state.instances[i].buttons[Xbox::Back] = ( xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK ) != 0;
		gamepad_state.instances[i].buttons[Xbox::LeftStick] = ( xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB ) != 0;
		gamepad_state.instances[i].buttons[Xbox::RightStick] = ( xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB ) != 0;
		gamepad_state.instances[i].buttons[Xbox::LeftShoulder] = ( xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER ) != 0;
		gamepad_state.instances[i].buttons[Xbox::RightShoulder] = ( xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER ) != 0;
		gamepad_state.instances[i].buttons[Xbox::A] = ( xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_A ) != 0;
		gamepad_state.instances[i].buttons[Xbox::B] = ( xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_B ) != 0;
		gamepad_state.instances[i].buttons[Xbox::X] = ( xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_X ) != 0;
		gamepad_state.instances[i].buttons[Xbox::Y] = ( xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y ) != 0;

		// Triggers
		gamepad_state.instances[i].axes[Xbox::LeftTrigger] = abs( xinput_state.Gamepad.bLeftTrigger ) > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? ( (float)xinput_state.Gamepad.bLeftTrigger ) / 255.0f : 0.0f;
		gamepad_state.instances[i].axes[Xbox::RightTrigger] = abs( xinput_state.Gamepad.bRightTrigger ) > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? ( (float)xinput_state.Gamepad.bRightTrigger ) / 255.0f : 0.0f;

		// Thumb sticks
		gamepad_state.instances[i].axes[Xbox::LeftStickX] = abs( xinput_state.Gamepad.sThumbLX ) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? ( (float)xinput_state.Gamepad.sThumbLX ) / 32767.0f : 0.0f;
		gamepad_state.instances[i].axes[Xbox::LeftStickY] = abs( xinput_state.Gamepad.sThumbLY ) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? ( (float)xinput_state.Gamepad.sThumbLY ) / 32767.0f : 0.0f;
		gamepad_state.instances[i].axes[Xbox::RightStickX] = abs( xinput_state.Gamepad.sThumbRX ) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? ( (float)xinput_state.Gamepad.sThumbRX ) / 32767.0f : 0.0f;
		gamepad_state.instances[i].axes[Xbox::RightStickY] = abs( xinput_state.Gamepad.sThumbRY ) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? ( (float)xinput_state.Gamepad.sThumbRY ) / 32767.0f : 0.0f;
	}
	
	return gamepad_state;
}