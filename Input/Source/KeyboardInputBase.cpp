#include "../Include/KeyboardInputBase.hpp"

#include <cstring>

using namespace Fnd::Input;

KeyboardInputBase::KeyboardInputBase():
    _current_state(0),
    _previous_state(1)
{
    memset( _keyboard_state, 0, sizeof(KeyboardState) * 2 );
}

bool KeyboardInputBase::IsDown( eKey key ) const
{
    return _keyboard_state[_current_state].keys[key];
}

bool KeyboardInputBase::IsUp( eKey key ) const
{
    return !_keyboard_state[_current_state].keys[key];
}

bool KeyboardInputBase::IsPressed( eKey key ) const
{
    return _keyboard_state[_current_state].keys[key] && !_keyboard_state[_previous_state].keys[key];
}

bool KeyboardInputBase::IsReleased( eKey key ) const
{
    return !_keyboard_state[_current_state].keys[key] && _keyboard_state[_previous_state].keys[key];
}

void KeyboardInputBase::Update()
{
    {
        const unsigned int temp = _current_state;
        _current_state = _previous_state;
        _previous_state = temp;
    }
    
    _keyboard_state[_current_state] = GetNextState();
}

KeyboardInputBase::~KeyboardInputBase()
{
}
