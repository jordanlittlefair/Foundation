#include "../Include/KeyboardInput.hpp"

using namespace Fnd::Input;

KeyboardInput::KeyboardInput():
	_window(nullptr),
	_direct_input(nullptr),
	_keyboard(nullptr),
	_current_state(nullptr),
	_previous_state(nullptr)
{
	ZeroMemory( &_keyboard_states[0], sizeof(unsigned char) * 512 );
}

void KeyboardInput::SetWindow( HWND window )
{
	_window = window;
}

void KeyboardInput::SetDirectInputDevice( IDirectInput8* direct_input )
{
	_direct_input = direct_input;
}

bool KeyboardInput::Initialise()
{
	if ( !_window ) 
	{
		return false;
	}

	if ( !_direct_input ) 
	{
		return false;
	}

	if ( FAILED( _direct_input->CreateDevice(	GUID_SysKeyboard, 
												&_keyboard,
												0 ) ) )
	{
		return false;
	}

	// set keyboard format and stuff
	if ( FAILED( _keyboard->SetDataFormat( &c_dfDIKeyboard ) ) ) 
	{
		return false;
	}
	if ( FAILED( _keyboard->SetCooperativeLevel( _window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) )
	{
		return false;
	}

	// first update is here to avoid errors with zero data
	_current_state = &_keyboard_states[0];
	_previous_state = &_keyboard_states[256];

	_keyboard->Acquire();
	_keyboard->GetDeviceState( 256 , _current_state );

	return true;
}

void KeyboardInput::Update()
{

	{	// swap current and previous state pointers
		unsigned char* temp = _current_state;
		_current_state = _previous_state;
		_previous_state = temp;
	}

	_keyboard->Acquire();
	_keyboard->GetDeviceState( sizeof(unsigned char) * 256, _current_state );
}

bool KeyboardInput::IsDown( DWORD key ) const
{
	return (_current_state[key] & 0x80) != 0;
}

bool KeyboardInput::IsUp( DWORD key ) const
{
	return (_current_state[key] & 0x80) == 0;
}

bool KeyboardInput::IsPressed( DWORD key ) const
{
	return (_current_state[key] & 0x80) != 0 && (_previous_state[key] & 0x80) == 0;
}

bool KeyboardInput::IsReleased( DWORD key ) const
{
	return (_current_state[key] & 0x80) == 0 && (_previous_state[key] & 0x80) != 0;
}

KeyboardInput::~KeyboardInput()
{
	if ( _keyboard )
	{ 
		_keyboard->Unacquire();
		_keyboard->Release();
	}
}