#include "../Include/XWindowsGamePadInput.hpp"

#include <cstring>

using namespace Fnd::Input;

XWindowsGamePadInput::XWindowsGamePadInput()
{
}

bool XWindowsGamePadInput::Initialise()
{
    return true;
}

GamePadInputBase::GamePadState XWindowsGamePadInput::GetNextState()
{
    GamePadState state;
    memset( &state, 0, sizeof(GamePadState) );
    
    return state;
}

XWindowsGamePadInput::~XWindowsGamePadInput()
{
}
