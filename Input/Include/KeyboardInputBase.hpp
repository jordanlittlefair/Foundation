#pragma once

#ifndef _INPUT_KEYBOARDINPUTBASE_HPP_
#define _INPUT_KEYBOARDINPUTBASE_HPP_

#include "IKeyboardInput.hpp"

namespace Fnd
{
namespace Input
{

/*
 A class to handle the input from the keyboard.
 */
class KeyboardInputBase:
    public IKeyboardInput
{
public:
    
    KeyboardInputBase();
    
    bool IsDown( eKey key ) const;
    
    bool IsUp( eKey key ) const;
    
    bool IsPressed( eKey key ) const;
    
    bool IsReleased( eKey key ) const;
    
    void Update();
    
    virtual ~KeyboardInputBase();
    
protected:

    struct KeyboardState
    {
        bool keys[Key_Count];
    };
    
    virtual KeyboardState GetNextState() = 0;
    
private:
    
    KeyboardState _keyboard_state[2];
    
    unsigned int _current_state;
    unsigned int _previous_state;
};

}
}

#endif