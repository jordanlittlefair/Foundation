#pragma once

#ifndef _MOCKSCRIPTINGMOCKSCRIPT_HPP_
#define _MOCKSCRIPTINGMOCKSCRIPT_HPP_

#include "../../Scripting/Include/Script.hpp"
#include "../../EntitySystem/Include/EntitySystem.hpp"
#include "../../Input/Include/IInput.hpp"

namespace Fnd
{
namespace MockScripting
{

class MockScript:
	public Fnd::Scripting::Script
{
	public:

		MockScript( Fnd::Scripting::ScriptManager* script_manager ):
			Script(script_manager)
		{
		}
	/*
	public:

		virtual void OnCreate() = 0;

		virtual void OnUpdate() = 0;

		virtual void OnDestroy() = 0;
	*/
};

}
}

#endif