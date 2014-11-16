#include "../Include/ComponentDataConversion.hpp"

#include "../../Utility/Include/String.hpp"

#include "../Include/Components.hpp"

#include <cstring>

using namespace Fnd::Utility;

namespace Fnd
{
namespace EntitySystem
{

template <>
void ConvertFromString<bool>( const std::string& as_string, bool& t )
{
	t = ( as_string == "true" );
}

template <>
void ConvertFromString<uint8>( const std::string& as_string, uint8& t )
{
	t = (uint8)atol(as_string.c_str());
}

template <>
void ConvertFromString<sint8>( const std::string& as_string, sint8& t )
{
	t = (sint8)atol(as_string.c_str());
}

template <>
void ConvertFromString<uint16>( const std::string& as_string, uint16& t )
{
	t = (uint16)atol(as_string.c_str());
}

template <>
void ConvertFromString<sint16>( const std::string& as_string, sint16& t )
{
	t = (sint16)atol(as_string.c_str());
}

template <>
void ConvertFromString<uint32>( const std::string& as_string, uint32& t )
{
	t = (uint32)atol(as_string.c_str());

	// TODO: a temp fix for 32 bit uints.
	// atol uses a signed int, but invalid ids use the uin32 max value.
	// This just converts the signed max value to the unsigned max.
	if ( t == 2147483647 )
		t = 4294967295;
}

template <>
void ConvertFromString<sint32>( const std::string& as_string, sint32& t )
{
	t = (sint32)atol(as_string.c_str());
}

template <>
void ConvertFromString<uint64>( const std::string& as_string, uint64& t )
{
	t = (uint64)atol(as_string.c_str());
}

template <>
void ConvertFromString<sint64>( const std::string& as_string, sint64& t )
{
	t = (sint64)atol(as_string.c_str());
}

template <>
void ConvertFromString<float32>( const std::string& as_string, float32& t )
{
	t = (float32)atof(as_string.c_str());
}

template <>
void ConvertFromString<float64>( const std::string& as_string, float64& t )
{
	t = (float64)atof(as_string.c_str());
}

template <>
void ConvertFromString<string64>( const std::string& as_string, string64& t )
{
	memset( &t, 0, sizeof(string64) );
#ifdef _MSC_VER
	strcpy_s( t, as_string.c_str() );
#else
	strcpy( t, as_string.c_str() );
#endif
}

template <>
void ConvertFromString<string512>( const std::string& as_string, string512& t )
{
	memset( &t, 0, sizeof(string512) );
#ifdef _MSC_VER
	strcpy_s( t, as_string.c_str() );
#else
	strcpy( t, as_string.c_str() );
#endif
}

template <>
void ConvertFromString<string1024>( const std::string& as_string, string1024& t )
{
	memset( &t, 0, sizeof(string1024) );
#ifdef _MSC_VER
	strcpy_s( t, as_string.c_str() );
#else
	strcpy( t, as_string.c_str() );
#endif
}

template <>
void ConvertFromString<Fnd::Math::Vector2>( const std::string&as_string, Fnd::Math::Vector2& t )
{
	auto vec = SplitString( as_string.substr(1,as_string.length()-2), ',' );

	vec.resize( 2, "0" );

	ConvertFromString<float>(vec[0],t.x);
	ConvertFromString<float>(vec[1],t.y);
}

template <>
void ConvertFromString<Fnd::Math::Vector3>( const std::string&as_string, Fnd::Math::Vector3& t )
{
	auto vec = SplitString( as_string.substr(1,as_string.length()-2), ',' );

	vec.resize( 3, "0" );

	ConvertFromString<float>(vec[0],t.x);
	ConvertFromString<float>(vec[1],t.y);
	ConvertFromString<float>(vec[2],t.z);
}

template <>
void ConvertFromString<Fnd::Math::Vector4>( const std::string&as_string, Fnd::Math::Vector4& t )
{
	auto vec = SplitString( as_string.substr(1,as_string.length()-2), ',' );

	vec.resize( 4, "0" );

	ConvertFromString<float>(vec[0],t.x);
	ConvertFromString<float>(vec[1],t.y);
	ConvertFromString<float>(vec[2],t.z);
	ConvertFromString<float>(vec[3],t.w);

}

template <>
void ConvertFromString<Fnd::Math::Quaternion>( const std::string&as_string, Fnd::Math::Quaternion& t )
{
	auto vec = SplitString( as_string.substr(1,as_string.length()-2), ',' );

	vec.resize( 4, "0" );

	ConvertFromString<float>(vec[0],t.x);
	ConvertFromString<float>(vec[1],t.y);
	ConvertFromString<float>(vec[2],t.z);
	ConvertFromString<float>(vec[3],t.w);

	t.Normalise();
}

template <>
void ConvertFromString<Fnd::Math::Matrix3>( const std::string&as_string, Fnd::Math::Matrix3& t )
{
	auto vec = SplitString( as_string.substr(1,as_string.length()-2), ',' );

	vec.resize( 9, "0" );

	for (	unsigned int i = 0; i < 9; ++i )
	{
		ConvertFromString<float>(vec[i], ((float*)&t)[i]);
	}
}

template <>
void ConvertFromString<Fnd::Math::Matrix4>( const std::string&as_string, Fnd::Math::Matrix4& t )
{
	auto vec = SplitString( as_string.substr(1,as_string.length()-2), ',' );

	vec.resize( 16, "0" );

	for (	unsigned int i = 0; i < 16; ++i )
	{
		ConvertFromString<float>(vec[i], ((float*)&t)[i]);
	}
}

}
}
