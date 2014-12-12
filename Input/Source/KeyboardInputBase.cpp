#include "../Include/KeyboardInputBase.hpp"

KeyboardInput::KeyboardInput():
    _current_state(0),
    _previous_state(1)
{
    memset( _keyboard_state, 0, sizeof(KeyboardState) * 2 );
}

bool KeyboardInput::IsDown( unsigned int key ) const
{
    return _keyboard_state[_current_state][key];
}

bool KeyboardInput::IsUp( unsigned int key ) const
{
    return !_keyboard_state[_current_state][key];
}

bool KeyboardInput::IsPressed( unsigned int key ) const
{
    return _keyboard_state[_current_state]key && !_keyboard_state[_previous_state][key];
}

bool KeyboardInput::IsReleased( unsigned int key ) const
{
    return !_keyboard_state[_current_state]key && _keyboard_state[_previous_state][key];
}

void KeyboardInput::Update()
{
    {
        const unsigned int temp = _current_state;
        _current_state = _previous_state;
        _previous_state = temp;
    }
    
    _keyboard_state[_current_state] = GetNextState();
}