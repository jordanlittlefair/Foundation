#pragma once

#ifndef _SCRIPT_HPP_
#define _SCRIPT_HPP_

#include "../../CommonResources/Include/FrameData.hpp"

#include <string>
#include <vector>

namespace Fnd
{
namespace Scripting
{
class ScriptManager;

class Script
{
	public:

		Script( Fnd::Scripting::ScriptManager* script_manager );	// TODO: must be the ScriptManagerInterface

		void SetOwningEntity( unsigned int entity_id );

		virtual void OnCreate() = 0;

		virtual void OnUpdate( const Fnd::CommonResources::FrameData& frame_data ) = 0;

		virtual void OnDestroy() = 0;
		/*
		struct RetVal
		{
			void* ptr;
			unsigned int size;
		};
		struct Param
		{
			void* ptr;
			unsigned int size;
		};

		virtual bool Call(	const std::string& function,
							RetVal& retval,
							const std::vector<Param>& params ) = 0;
*/
		virtual ~Script();

	protected:

		unsigned int GetOwningEntity() const;

		Fnd::Scripting::ScriptManager* GetScriptManager();

	private:

		unsigned int _owning_entity_id;

		Fnd::Scripting::ScriptManager* _script_manager;
};

}
}

#endif