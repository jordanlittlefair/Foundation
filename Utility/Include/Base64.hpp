#pragma once

#ifndef _UTILITY_BASE64_HPP_
#define _UTILITY_BASE64_HPP_

#include <vector>
#include <string>

namespace Fnd
{
namespace Utility
{

class Base64
{
	public:

		static std::string Encode( const std::vector<unsigned char>& source );

		static std::string Encode( const unsigned char* source, unsigned int length );

		static std::vector<unsigned char> Decode( const std::string& source );

		static std::vector<unsigned char> Decode( const char* source, unsigned int length );

	private:

		static const unsigned char _encode_map[65];
		static const unsigned char _decode_map[128];
};


}
}

#endif