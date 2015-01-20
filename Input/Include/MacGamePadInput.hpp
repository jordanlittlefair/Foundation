#pragma once

#ifndef _INPUT_MACGAMEPADINPUT_HPP_
#define _INPUT_MACGAMEPADINPUT_HPP_

#include "GamePadInputBase.hpp"

namespace Fnd
{
namespace Input
{

class MacGamePadInput:
    public GamePadInputBase
{
    public:
        
        MacGamePadInput();
        
        bool Initialise();
    
        ~MacGamePadInput();
        
    protected:
        
        GamePadInputBase::GamePadState GetNextState();
        
    private:
        
        // TODO
};
    
}
}

#endif