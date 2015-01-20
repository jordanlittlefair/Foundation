#include "../Include/XWindowsMouseInput.hpp"

#include <cstring>

using namespace Fnd::Input;

XWindowsMouseInput::XWindowsMouseInput()
{
}

bool XWindowsMouseInput::Initialise()
{
    return true;
}

MouseInputBase::MouseState XWindowsMouseInput::GetNextState()
{
    MouseState state;
    memset( &state, 0, sizeof(MouseState) );
    
    return state;
}

XWindowsMouseInput::~XWindowsMouseInput()
{
}
