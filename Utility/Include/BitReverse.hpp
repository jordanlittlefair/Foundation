#pragma once

#ifndef _UTILITY_BITREVERSE_HPP_
#define _UTILITY_BITREVERSE_HPP_

namespace Fnd
{
namespace Utility
{

template <typename T>
inline T GetBitReverse( const T& t );

}
}

namespace Fnd
{
namespace Utility
{

template <>
unsigned char GetBitReverse<unsigned char>( const unsigned char& t )
{
	// 01234567 ->
	unsigned char ret = t;

	// swap blocks of 4
	ret = (ret & 0xF0) >> 4 | (ret & 0x0F) << 4;
	// -> 45670123

	// swap blocks of 2
	ret = (ret & 0xCC) >> 2 | (ret & 0x33) << 2;
	// -> 67452301

	// swap single bytes
	ret = (ret & 0xAA) >> 1 | (ret & 0x55) << 1;
	// -> 76543210

	return ret;
}

template <typename T>
T GetBitReverse( const T& t )
{
	T ret;

	for ( unsigned int i = 0; i < sizeof(T); ++i )
	{
		((unsigned char*)&ret)[i] = GetBitReverse<unsigned char>( ((unsigned char*)&t)[sizeof(T)-(1+i)] );
	}

	return ret;
}

}
}

#endif
