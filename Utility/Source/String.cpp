#include "../Include/String.hpp"

#include <algorithm>
#include <sstream>

void Fnd::Utility::RemoveWhitespace( std::string& str )
{
	str.erase( std::remove_if( str.begin(), str.end(), isspace ), str.end() );
}

std::vector<std::string> Fnd::Utility::SplitString( const std::string& str, char c )
{
	std::vector<std::string> to_return;
	std::stringstream ss(str);
	std::string substring;

	while( std::getline( ss, substring, c ) )
	{
		to_return.push_back(substring);
	}

	for ( unsigned int i = 0; i < to_return.size(); ++i )
	{
		if ( to_return[i].empty() )
		{
			to_return[i] = to_return.back();
			to_return.pop_back();
			--i;
		}
	}

	return to_return;
}

void Fnd::Utility::RemoveEmptyStrings( std::vector<std::string>& strs )
{
	strs.erase(	std::remove_if(	strs.begin(),
								strs.end(),
								[] (const std::string& str) -> bool { return str.empty(); }
							),
							strs.end() );
}
