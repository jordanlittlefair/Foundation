#include "../Include/Base64.hpp"

using namespace Fnd::Utility;


const unsigned char Base64::_encode_map[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const unsigned char Base64::_decode_map[128] =
{
	127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
	127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
	127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
	127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
	127, 127, 127,  62, 127, 127, 127,  63,  52,  53,
	54,  55,  56,  57,  58,  59,  60,  61, 127, 127,
	127, 64, 127, 127, 127,   0,   1,   2,   3,   4,
	5,   6,   7,   8,   9,  10,  11,  12,  13,  14,
	15,  16,  17,  18,  19,  20,  21,  22,  23,  24,
	25, 127, 127, 127, 127, 127, 127,  26,  27,  28,
	29,  30,  31,  32,  33,  34,  35,  36,  37,  38,
	39,  40,  41,  42,  43,  44,  45,  46,  47,  48,
	49,  50,  51, 127, 127, 127, 127, 127
};

std::string Base64::Encode( const std::vector<unsigned char>& source )
{
	return source.empty() ? "" : Encode( &source[0], source.size() );
}

std::string Base64::Encode( const unsigned char* source, unsigned int length )
{
		std::string dest;

	size_t i, n;
	int C1, C2, C3;

	if( length == 0 )
		return dest;

	n = ( length << 3 ) / 6;

	switch( ( length << 3 ) - ( n * 6 ) )
	{
		case 2: 
			n += 3; 
			break;
		case 4:
			n += 2; 
			break;
		default: break;
	}

	dest.reserve( n + 1 );

	n = ( length / 3 ) * 3;

	for( i = 0; i < n; i += 3 )
	{
		C1 = source[i+0];
		C2 = source[i+1];
		C3 = source[i+2];

		dest += _encode_map[(C1 >> 2) & 0x3F];
		dest += _encode_map[(((C1 &  3) << 4) + (C2 >> 4)) & 0x3F];
		dest += _encode_map[(((C2 & 15) << 2) + (C3 >> 6)) & 0x3F];
		dest += _encode_map[C3 & 0x3F];
	}

	if( i < length )
	{
		C1 = source[i];
		C2 = ((i + 1) < length) ? source[i+1] : 0;
		dest += _encode_map[(C1 >> 2) & 0x3F];
		dest += _encode_map[(((C1 & 3) << 4) + (C2 >> 4)) & 0x3F];
			
		if( (i + 1) < length )
			dest += _encode_map[((C2 & 15) << 2) & 0x3F];
		else dest +=  '=';
			
		dest += '=';
	}
				
	return dest;
}

std::vector<unsigned char> Base64::Decode( const std::string& source )
{
	return source.empty() ? std::vector<unsigned char>() : Decode( &source[0], source.size() );
}

std::vector<unsigned char> Base64::Decode( const char* source, unsigned int length )
{
	std::vector<unsigned char> dest;

	size_t i, n;
	int j, x;
	
	for( i = n = j = 0; i < length; i++ )
	{
		if( ( length - i ) >= 2 &&
			source[i] == '\r' && source[i + 1] == '\n' )
				continue;
		
		if( source[i] == '\n' )
			continue;
		if( source[i] == '=' && ++j > 2 )
			return std::vector<unsigned char>();
		if( source[i] > 127 || _decode_map[source[i]] == 127 )
			return std::vector<unsigned char>();

		if( _decode_map[source[i]] < 64 && j != 0 )
			return std::vector<unsigned char>();
		n++;
	}
	if( n == 0 )
		return std::vector<unsigned char>();
	
	n = ((n * 6) + 7) >> 3;

	dest.reserve(n);

	int src_iter = 0;
	
	for( j = 3, n = x = 0; i > 0; i--, src_iter++ )
	{
		if( source[src_iter] == '\r' || source[src_iter] == '\n' )
			continue;
		
		j -= ( _decode_map[source[src_iter]] == 64 );
		x  = (x << 6) | ( _decode_map[source[src_iter]] & 0x3F );
		
		if( ++n == 4 )
		{
			n = 0;
			if( j > 0 ) dest.push_back( (unsigned char)( x >> 16 ) );
			if( j > 1 ) dest.push_back( (unsigned char)( x >>  8 ) );
			if( j > 2 ) dest.push_back( (unsigned char)( x       ) );
		}
	}
		
	return dest;
}