#include "../Include/String.hpp"

#include <algorithm>
#include <sstream>
#include <fstream>

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
        if ( !substring.empty() )
        {
            to_return.push_back(substring);
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

bool Fnd::Utility::LoadFileIntoString( const std::string& filename, std::string& str )
{
	std::ifstream filestream( filename, std::ios::beg );

	if ( filestream.is_open() )
	{
		std::stringstream ss;
		ss << filestream.rdbuf();
		str = ss.str();
		filestream.close();
		return true;
	}
	else
	{
		return false;
	}
}