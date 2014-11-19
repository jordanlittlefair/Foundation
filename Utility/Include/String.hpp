#pragma once

#ifndef _UTILITY_STRING_HPP_
#define _UTILITY_STRING_HPP_

#include <string>
#include <vector>

namespace Fnd
{
namespace Utility
{

/*
	Utility functions used for manipulating strings.
*/

/**
	Removes all whitespace from a string.
	@param str A reference to a string to remove whitespace from.
*/
void RemoveWhitespace( std::string& str );

/**
	Splits a string into a vector of strings.
	@param str The string to be split.
	@param c The delimiting character.
	@return Returns a vector of strings, including any empty strings.
*/
std::vector<std::string> SplitString( const std::string& str, char c );

/**
	Remove any empty strings from a vector of strings.
	@param strs A reference to a vector of strings to remove empty strings from.
*/
void RemoveEmptyStrings( std::vector<std::string>& strs );

}
}

#endif