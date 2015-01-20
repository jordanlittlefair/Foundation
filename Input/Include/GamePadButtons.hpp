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
	Up			= Xbox::Button::Up,
	Down		= Xbox::Button::Down,
	Left		= Xbox::Button::Left,
	Right		= Xbox::Button::Right,
	Start		= Xbox::Button::Start,
	Select		= Xbox::Button::Back,
	LeftStick	= Xbox::Button::LeftStick,
	RightStick	= Xbox::Button::RightStick,
	L1			= Xbox::Button::LeftShoulder,
	R1			= Xbox::Button::RightShoulder,
	Cross		= Xbox::Button::A,
	Circle		= Xbox::Button::B,
	Square		= Xbox::Button::X,
	Triangle	= Xbox::Button::Y,
    
    Button_Count = Xbox::Button::Button_Count
};
enum Axis
{
	L2				= Xbox::Axis::LeftTrigger,
	R2				= Xbox::Axis::RightTrigger,
	LeftStickX		= Xbox::Axis::LeftStickX,
	LeftStickY		= Xbox::Axis::LeftStickY,
	RightStickX		= Xbox::Axis::RightStickX,
	RightStickY		= Xbox::Axis::RightStickY,
    
    Axis_Count		= Xbox::Axis::Axis_Count
};
}    

}
}


#endif