#include "../Include/MouseInputBase.hpp"

MouseInputState::MouseInputBase():
    _current_state(0),
    _previous_state(1)
{
    memset( _mouse_state, 0, sizeof(MouseState) * 2 );
}

bool MouseInputState::IsDownLeft() const
{
    return _mouse_state[_current_state].left_button;
}

bool MouseInputState::IsDownRight() const
{
    return _mouse_state[_current_state].right_button;
}

bool MouseInputState::IsDownMiddle() const
{
    return _mouse_state[_current_state].middle_button;
}

bool MouseInputState::IsUpLeft() const
{
    return !_mouse_state[_current_state].left_button;
}

bool MouseInputState::IsUpRight() const
{
    return !_mouse_state[_current_state].right_button;
}

bool MouseInputState::IsUpMiddle() const
{
    return !_mouse_state[_current_state].middle_button;
}

bool MouseInputState::IsPressedLeft() const
{
    return _mouse_state[_current_state].left_button && !_mouse_state[_previous_state].left_button;
}

bool MouseInputState::IsPressedRight() const
{
    return _mouse_state[_current_state].right_button && !_mouse_state[_previous_state].right_button;
}

bool MouseInputState::IsPressedMiddle() const
{
    return _mouse_state[_current_state].middle_button && !_mouse_state[_previous_state].middle_button;
}

bool MouseInputState::IsReleasedLeft() const
{
    return !_mouse_state[_current_state].left_button && _mouse_state[_previous_state].left_button;
}

bool MouseInputState::IsReleasedRight() const
{
    return !_mouse_state[_current_state].right_button && _mouse_state[_previous_state].right_button;
}

bool MouseInputState::IsReleasedMiddle() const
{
    return !_mouse_state[_current_state].middle_button && _mouse_state[_previous_state].middle_button;
}

int MouseInputState::GetMouseDeltaX() const
{
    return _mouse_state[_current_state].delta_x;
}

int MouseInputState::GetMouseDeltaY() const
{
    return _mouse_state[_current_state].delta_y;
}

int MouseInputState::GetMouseDeltaWheel() const
{
    return _mouse_state[_current_state].delta_wheel;
}

void MouseInputState::Update()
{
    {
        const int temp = _current_state;
        _current_state = _previous_state;
        _previous_state = temp;
    }
    
    _mouse_state[_current_state] = GetNextState();
}





















