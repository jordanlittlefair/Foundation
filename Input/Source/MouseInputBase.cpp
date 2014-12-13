#include "../Include/MouseInputBase.hpp"

#include <cstring>

using namespace Fnd::Input;

MouseInputBase::MouseInputBase():
    _current_state(0),
    _previous_state(1)
{
    memset( _mouse_state, 0, sizeof(MouseState) * 2 );
}

bool MouseInputBase::IsDownLeft() const
{
    return _mouse_state[_current_state].left_button;
}

bool MouseInputBase::IsDownRight() const
{
    return _mouse_state[_current_state].right_button;
}

bool MouseInputBase::IsDownMiddle() const
{
    return _mouse_state[_current_state].middle_button;
}

bool MouseInputBase::IsUpLeft() const
{
    return !_mouse_state[_current_state].left_button;
}

bool MouseInputBase::IsUpRight() const
{
    return !_mouse_state[_current_state].right_button;
}

bool MouseInputBase::IsUpMiddle() const
{
    return !_mouse_state[_current_state].middle_button;
}

bool MouseInputBase::IsPressedLeft() const
{
    return _mouse_state[_current_state].left_button && !_mouse_state[_previous_state].left_button;
}

bool MouseInputBase::IsPressedRight() const
{
    return _mouse_state[_current_state].right_button && !_mouse_state[_previous_state].right_button;
}

bool MouseInputBase::IsPressedMiddle() const
{
    return _mouse_state[_current_state].middle_button && !_mouse_state[_previous_state].middle_button;
}

bool MouseInputBase::IsReleasedLeft() const
{
    return !_mouse_state[_current_state].left_button && _mouse_state[_previous_state].left_button;
}

bool MouseInputBase::IsReleasedRight() const
{
    return !_mouse_state[_current_state].right_button && _mouse_state[_previous_state].right_button;
}

bool MouseInputBase::IsReleasedMiddle() const
{
    return !_mouse_state[_current_state].middle_button && _mouse_state[_previous_state].middle_button;
}

int MouseInputBase::GetMouseDeltaX() const
{
    return _mouse_state[_current_state].delta_x;
}

int MouseInputBase::GetMouseDeltaY() const
{
    return _mouse_state[_current_state].delta_y;
}

int MouseInputBase::GetMouseDeltaWheel() const
{
    return _mouse_state[_current_state].delta_wheel;
}

void MouseInputBase::Update()
{
    {
        const int temp = _current_state;
        _current_state = _previous_state;
        _previous_state = temp;
    }
    
    _mouse_state[_current_state] = GetNextState();
}





















