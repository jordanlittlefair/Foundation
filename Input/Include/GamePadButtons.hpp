#pragma once

#ifndef _INPUT_GAMEPADBUTTONS_HPP_
#define _INPUT_GAMEPADBUTTONS_HPP_

#ifdef _WIN32

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

#include <dinput.h>
#include <XInput.h>


// Buttons
#define XBOX_UP				XINPUT_GAMEPAD_DPAD_UP
#define XBOX_DOWN			XINPUT_GAMEPAD_DPAD_DOWN
#define XBOX_LEFT			XINPUT_GAMEPAD_DPAD_LEFT
#define XBOX_RIGHT			XINPUT_GAMEPAD_DPAD_RIGHT
#define XBOX_START			XINPUT_GAMEPAD_START
#define XBOX_BACK			XINPUT_GAMEPAD_BACK
#define XBOX_LEFT_STICK		XINPUT_GAMEPAD_LEFT_THUMB
#define XBOX_RIGHT_STICK	XINPUT_GAMEPAD_RIGHT_THUMB
#define XBOX_LB				XINPUT_GAMEPAD_LEFT_SHOULDER
#define XBOX_RB				XINPUT_GAMEPAD_RIGHT_SHOULDER
#define XBOX_A				XINPUT_GAMEPAD_A
#define XBOX_B				XINPUT_GAMEPAD_B
#define XBOX_X				XINPUT_GAMEPAD_X
#define XBOX_Y				XINPUT_GAMEPAD_Y

#else

// Buttons - complete bollocks on Mac but this'll fix the build until Input is abstracted properly
#define XBOX_UP				0
#define XBOX_DOWN			1
#define XBOX_LEFT			2
#define XBOX_RIGHT			3
#define XBOX_START			4
#define XBOX_BACK			5
#define XBOX_LEFT_STICK		6
#define XBOX_RIGHT_STICK	7
#define XBOX_LB				8
#define XBOX_RB				9
#define XBOX_A				10
#define XBOX_B				11
#define XBOX_X				12
#define XBOX_Y				13

#endif

// Axes
#define XBOX_LT			0
#define XBOX_RT			1
#define XBOX_LEFT_X		2
#define XBOX_LEFT_Y		3
#define XBOX_RIGHT_X	4
#define XBOX_RIGHT_Y	5

namespace Fnd
{
namespace Input
{

namespace Xbox
{
enum Buttons
{
	Up				= XBOX_UP,
	Down			= XBOX_DOWN,
	Left			= XBOX_LEFT,
	Right			= XBOX_RIGHT,
	Start			= XBOX_START,
	Back			= XBOX_BACK,
	LeftStick		= XBOX_LEFT_STICK,
	RightStick		= XBOX_RIGHT_STICK,
	LeftShoulder	= XBOX_LB,
	RightShoulder	= XBOX_RB,
	A				= XBOX_A,
	B				= XBOX_B,
	X				= XBOX_X,
	Y				= XBOX_Y
};
enum Axes
{
	LeftTrigger		= 0,
	RightTrigger	= 1,
	LeftStickX		= 2,
	LeftStickY		= 3,
	RightStickX		= 4,
	RightStickY		= 5
};
}

namespace PS
{
enum Buttons
{
	Up			= Xbox::Buttons::Up,
	Down		= Xbox::Buttons::Down,
	Left		= Xbox::Buttons::Left,
	Right		= Xbox::Buttons::Right,
	Start		= Xbox::Buttons::Start,
	Select		= Xbox::Buttons::Back,
	LeftStick	= Xbox::Buttons::LeftStick,
	RightStick	= Xbox::Buttons::RightStick,
	L1			= Xbox::Buttons::LeftShoulder,
	R1			= Xbox::Buttons::RightShoulder,
	Cross		= Xbox::Buttons::A,
	Circle		= Xbox::Buttons::B,
	Square		= Xbox::Buttons::X,
	Triangle	= Xbox::Buttons::Y
};
enum Axes
{
	L2				= Xbox::Axes::LeftTrigger,
	R2				= Xbox::Axes::RightTrigger,
	LeftStickX		= Xbox::Axes::LeftStickX,
	LeftStickY		= Xbox::Axes::LeftStickY,
	RightStickX		= Xbox::Axes::RightStickX,
	RightStickY		= Xbox::Axes::RightStickY
};
}

}
}


#endif