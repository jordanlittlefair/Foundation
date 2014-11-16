#pragma once

#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_

namespace Fnd
{
namespace Utility
{

template <typename T>
inline T Min( const T& a, const T& b )
{
	return a < b ? a : b;
}

template <typename T>
inline T Max( const T& a, const T& b )
{
	return a > b ? a : b;
}

}
}

#endif