#pragma once

#ifndef _SCRIPTING_SCRIPTINGINTERFACE_HPP_
#define _SCRIPTING_SCRIPTINGINTERFACE_HPP_

namespace Fnd
{
namespace Scripting
{

/*
	This must describe a 'proper c++' interface. 
	The data returned from these methods will then be translated fpr the scripting language.

	Each XxxScriptingInterface should be defined in the appropriate component.

	EntitySystemScriptingInterface should be auto generated (basically just a thin wrapper around what's already there)
*/
class ScriptingInterface
{
	public:

		class IGraphicsScriptingInterface
		{
			public:

				void GetResolution( unsigned int* width, unsigned int* height );

		};

		void* /*needs to be a typed pointer*/ GetEntitySystemScriptingInterface();

		IGraphicsScriptingInterface* GetGraphicsScriptingInterface();

		void* GetPhysicsScriptingInterface();

	private:
};

}
}

#endif