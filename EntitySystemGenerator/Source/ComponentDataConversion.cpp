#include "..\Include\ComponentDataConversion.hpp"

using namespace Fnd::EntitySystemCodeGeneration;

bool ComponentDataConversion::IsValidType( const std::string& type )
{
	bool found = false;

	for ( unsigned int i = 0; i < sizeof(valid_types)/sizeof(ValidType); ++i )
	{
		if ( valid_types[i].type == type )
		{
			found = true;
			break;
		}
	}

	return found;
}

std::string ComponentDataConversion::GetConversionCode( const std::string& type )
{
	std::string ret;

	if ( IsAutoConverted(type) )
	{
		ret += "ConvertFromString<" + type + ">(as_string);";
	}

	return ret;
}

bool ComponentDataConversion::IsAutoConverted( const std::string& type )
{
	bool auto_converted = false;

	for ( unsigned int i = 0; i < sizeof(valid_types)/sizeof(ValidType); ++i )
	{
		if ( valid_types[i].type == type )
		{
			auto_converted = valid_types[i].is_auto_converted;
			break;
		}
	}

	return auto_converted;
}

ComponentDataConversion::ValidType ComponentDataConversion::valid_types[] =
{
	{ "bool", true },
	{ "uint8", true },
	{ "sint8", true },
	{ "uint16", true },
	{ "sint16", true },
	{ "uint32", true },
	{ "sint32", true },
	{ "uint64", true },
	{ "sint64", true },
	{ "float32", true },
	{ "float64", true },
	{ "string64", true },
	{ "string512", true },
	{ "string1024", true },
	{ "Fnd::Math::Vector2", true },
	{ "Fnd::Math::Vector3", true },
	{ "Fnd::Math::Vector4", true },
	{ "Fnd::Math::Quaternion", true },
	{ "Fnd::Math::Matrix3", true },
	{ "Fnd::Math::Matrix4", true }
};