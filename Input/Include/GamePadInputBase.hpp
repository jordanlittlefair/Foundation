#pragma once

#ifndef _INPUT_GAMEPADINPUTBASE_HPP_
#define _INPUT_GAMEPADINPUTBASE_HPP_

#include "IGamePadInput.hpp"

namespace Fnd
{
namespace Input
{

class GamePadInputBase:
    public IGamePadInput
{
public:
    
    GamePadInputBase();
    
    bool IsConnected( unsigned int index = 0 ) const;
    
    bool IsDown( Xbox::Button button, unsigned int index = 0 ) const;
    
    bool IsUp( Xbox::Button button, unsigned int index = 0 ) const;
    
    bool IsPressed( Xbox::Button button, unsigned int index = 0 ) const;
    
    bool IsReleased( Xbox::Button button, unsigned int index = 0 ) const;
    
    float GetAxisValue( Xbox::Axis axis, unsigned int index = 0 ) const;
    
    void Update();
    
    virtual ~GamePadInputBase();
    
protected:

    struct GamePadState
    {
        struct GamePadInstanceState
        {
            bool is_connected;
            bool buttons[Xbox::Button::Button_Count];
            float axes[Xbox::Axis::Axis_Count];
        };
        
        GamePadInstanceState instances[4];
    };
    
    virtual GamePadState GetNextState() = 0;
    
private:

    GamePadState _gamepad_state[2];
    
    unsigned int _current_state;
    unsigned int _previous_state;
};

}
}

#endif