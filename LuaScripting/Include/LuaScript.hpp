#pragma once

#ifndef _LUASCRIPTING_LUASCRIPT_HPP_
#define _LUASCRIPTING_LUASCRIPT_HPP_

#include <string>

namespace Fnd
{
namespace LuaScripting
{

//https://gist.github.com/kizzx2/1594905	-> but find the 5.2 version

class LuaScript
{
	public:

		LuaScript( const std::string& script_filename );

		void OnCreate();
		void OnUpdate();
		void OnDestroy();

	private:

		std::string _script_str;
};

}
}

#endif