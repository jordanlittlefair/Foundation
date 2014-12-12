#pragma once

#ifndef _INPUT_GAMEPADBUTTONS_HPP_
#define _INPUT_GAMEPADBUTTONS_HPP_

namespace Fnd
{
namespace Input
{

namespace Xbox
{
enum Button
{
	Up,
	Down,
	Left,
	Right,
	Start,
	Back,
	LeftStick,
	RightStick,
	LeftShoulder,
	RightShoulder,
	A,
	B,
	X,
	Y,
    
    Button_Count
};
enum Axis
{
	LeftTrigger,
	RightTrigger,
	LeftStickX,
	LeftStickY,
	RightStickX,
	RightStickY,
    
    Axis_Count
};
}

namespace PS
{
enum Button
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
	Triangle	= Xbox::Buttons::Y,
    
    Button_Count = xbox::Buttons::Button_Count
};
enum Axis
{
	L2				= Xbox::Axes::LeftTrigger,
	R2				= Xbox::Axes::RightTrigger,
	LeftStickX		= Xbox::Axes::LeftStickX,
	LeftStickY		= Xbox::Axes::LeftStickY,
	RightStickX		= Xbox::Axes::RightStickX,
	RightStickY		= Xbox::Axes::RightStickY,
    
    Xbox::Axis::Axis_Count
};
}

union GamePadButton
{
    Xbox::Button xbox;
    PS::Button ps;
};

union GamePadAxis
{
    Xbox::Axis xbox;
    PS::Axis ps;
};
    

}
}


#endif