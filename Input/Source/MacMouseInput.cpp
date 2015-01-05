#include "../Include/MacMouseInput.hpp"

#include <cstring>

using namespace Fnd::Input;

MacMouseInput::MacMouseInput()
{
}

bool MacMouseInput::Initialise()
{
    return true;
}

MouseInputBase::MouseState MacMouseInput::GetNextState()
{
    MouseInputBase::MouseState state;
    memset( &state, 0, sizeof(state) );
    
    return state;
}

MacMouseInput::~MacMouseInput()
{
}
