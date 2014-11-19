#pragma once

#ifndef _ENTITYSYSTEMGENERATOR_COMPONENTDATACONVERSION_HPP_
#define _ENTITYSYSTEMGENERATOR_COMPONENTDATACONVERSION_HPP_

#include <string>

namespace Fnd
{
namespace EntitySystemCodeGeneration
{

class ComponentDataConversion
{
	public:

		static bool IsValidType( const std::string& type );

		static std::string GetConversionCode( const std::string& type );
		
		static bool IsAutoConverted( const std::string& type );

	private:

		struct ValidType
		{
			std::string type;
			bool is_auto_converted;
		};

		static ValidType valid_types[22];
};

}
}

#endif