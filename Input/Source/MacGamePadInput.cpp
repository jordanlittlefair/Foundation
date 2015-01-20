#include "../Include/MacGamePadInput.hpp"

#include <cstring>

using namespace Fnd::Input;

MacGamePadInput::MacGamePadInput()
{
}

bool MacGamePadInput::Initialise()
{
    return true;
}

GamePadInputBase::GamePadState MacGamePadInput::GetNextState()
{
    GamePadState state;
    memset( &state, 0, sizeof(GamePadState) );
    
    return state;
}

MacGamePadInput::~MacGamePadInput()
{
}
