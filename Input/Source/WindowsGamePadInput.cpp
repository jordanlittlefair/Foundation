#include "../Include/WindowsGamePadInput.hpp"

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
	GamePadState state;
	memset( &state, 0, sizeof(GamePadState) );
	
	return state;
}