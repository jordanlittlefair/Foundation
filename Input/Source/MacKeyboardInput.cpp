#include "../Include/MacKeyboardInput.hpp"

#include <cstring>

using namespace Fnd::Input;

MacKeyboardInput::MacKeyboardInput()
{
}

bool MacKeyboardInput::Initialise()
{
    return true;
}

KeyboardInputBase::KeyboardState MacKeyboardInput::GetNextState()
{
    KeyboardInputBase::KeyboardState state;
    memset( &state, 0, sizeof(state) );
    
    return state;
}

MacKeyboardInput::~MacKeyboardInput()
{
}
