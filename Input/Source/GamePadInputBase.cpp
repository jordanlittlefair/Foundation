#include "../Include/GamePadInputBase.hpp"

GamePadInputBase::GamePadInputBase():
    _current_state(0),
    _previous_state(1)
{
    memset( _gamepad_state, 0, sizeof(GamePadState) * 2 );
}

bool GamePadInputBase::IsConnected( unsigned int index = 0 ) const
{
    return _gamepad_state[_current_state].instances[index].is_connected;
}

bool GamePadInputBase::IsDown( GamePadButton button, unsigned int index = 0 ) const
{
    return _gamepad_state[_current_state].instances[index].buttons[button];
}

bool GamePadInputBase::IsUp( GamePadButton button, unsigned int index = 0 ) const
{
    return !_gamepad_state[_current_state].instances[index].buttons[button];
}

bool GamePadInputBase::IsPressed( GamePadButton button, unsigned int index = 0 ) const
{
    return _gamepad_state[_current_state].instances[index].buttons[button] && !_gamepad_state[_previous_state].instances[index].buttons[button];
}

bool GamePadInputBase::IsReleased( GamePadButton button, unsigned int index = 0 ) const
{
    return !_gamepad_state[_current_state].instances[index].buttons[button] && _gamepad_state[_current_state].instances[index].buttons[button];
}

float GamePadInputBase::GetAxisValue( GamePadAxis axis, unsigned int index = 0 ) const
{
    return _gamepad_state[_current_state].instances[index].axes[axis];
}

void GamePadInputBase::Update()
{
    {
        const unsigned int temp = _current_state;
        _current_state = _previous_state;
        _previous_state = temp;
    }
    
    _gamepad_state[_current_state] = GetNextState();
}
