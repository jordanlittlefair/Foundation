#include "../Include/LuaScript.hpp"

#include <fstream>

using namespace Fnd::LuaScripting;

LuaScript::LuaScript( const std::string& script_filename )
{
	std::ifstream file( script_filename, std::ios::in | std::ios::ate );

	if ( file.is_open() )
	{
		auto end = file.tellg();
		file.seekg(std::ios::beg);
		auto start = file.tellg();

		unsigned int file_length = (unsigned int)(end - start);

		_script_str.resize( file_length, '\0' );

		if ( file_length != 0 )
		{
			file.read( &_script_str[0], file_length );
		}
	}
	else
	{
		// Output some error
	}
}