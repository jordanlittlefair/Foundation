#pragma once

#ifndef _MOCKSCRIPTINGMOCKSCRIPTMANAGER_HPP_
#define _MOCKSCRIPTINGMOCKSCRIPTMANAGER_HPP_

#include "../../Scripting/Include/ScriptManager.hpp"

namespace Fnd
{
namespace MockScripting
{

class MockScriptManager:
	public Fnd::Scripting::ScriptManager
{
	public:

		MockScriptManager();

		void AddScript( unsigned int entity_id, std::string& script_name );
};

}
}

#endif