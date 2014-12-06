#include "../Include/FileSystem.hpp"
#include "../Include/String.hpp"

using namespace Fnd::Utility;

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#endif
#include <algorithm>

bool FileSystem::CreateNewDirectory( const std::string& directory_name )
{
#ifdef _WIN32
	if ( !CreateDirectory( directory_name.c_str(), nullptr ) )
	{
		if ( GetLastError() != ERROR_ALREADY_EXISTS )
		{
			return false;
		}
	}

	return true;
#else
    return !mkdir( directory_name.c_str(), 0777 );
#endif
}


std::string FileSystem::CanonicaliseFile( const std::string& filename )
{
	std::string ret = CanonicaliseDirectory(filename);

	if ( !ret.empty() && ret.back() == '/' )
	{
		ret.pop_back();
	}

	return ret;
}

std::string FileSystem::CanonicaliseDirectory( const std::string& directory )
{
	std::string ret;

	std::string directory_local = directory;

	std::transform( directory_local.begin(), directory_local.end(), directory_local.begin(), [](char c) { return ( c == '\\' ? '/' : c ); } );

	auto path_vec = SplitString( directory_local, '/' );

	int parent_count = 0;

	for ( auto iter = path_vec.rbegin(); iter != path_vec.rend(); ++iter )
	{
		if ( *iter != ".." )
		{
			if ( parent_count == 0 )
			{
				ret = *iter + '/' + ret;
			}
			else
			{
				--parent_count;
			}
		}
		else
		{
			++parent_count;
		}
	}

	for ( int i = 0; i < parent_count; ++i )
	{
		ret = "../" + ret;
	}

	return ret;
}

void FileSystem::GetPathAndName( const std::string& full_path, std::string& path, std::string& name )
{
	unsigned int last_slash = (unsigned int)full_path.find_last_of( '/' );

	if ( last_slash == (unsigned int)std::string::npos )
	{
		path = "";
		name = full_path;
	}
	else
	{
		path = full_path.substr( 0, last_slash + 1 );
		name = full_path.substr( last_slash + 1 );
	}
}

std::string FileSystem::GetWorkingDirectory()
{
#ifdef _WIN32
	char buffer[MAX_PATH] = {0};

	GetCurrentDirectory( MAX_PATH, buffer );

	return buffer;
#else
    char buffer[PATH_MAX] = {0};
    
    getcwd( buffer, 0777 );
    
    return buffer;
#endif
}

std::vector<std::string> FileSystem::ParseCommandLine( const std::string& command_line )
{
	std::vector<std::string> ret;

	unsigned int start = 0;

	bool in_quotes = false;

	for ( unsigned int i = 0; i < command_line.size(); ++i )
	{
		if ( !in_quotes && command_line[i] == ' ' )
		{
			ret.push_back( command_line.substr( start, i - start ) );

			start = i + 1;
		}

		if ( command_line[i] == '\"' )
		{
			in_quotes = !in_quotes;
		}
	}

	ret.push_back( command_line.substr( start ) );

	// Remove quotes
	for ( unsigned int i = 0; i < ret.size(); ++i )
	{
		if ( ret[i].size() > 1 && ret[i].front() == '\"' && ret[i].back() == '\"' )
		{
			ret[i] = ret[i].substr( 1, ret[i].size() - 2 );
		}
	}

	return ret;
}

std::vector<std::string> FileSystem::GetDirectories( const std::string& directory )
{
	return Fnd::Utility::SplitString( CanonicaliseFile( directory ), '/' );
}
#include <cassert>
bool FileSystem::CopyFile_( const std::string& source, const std::string& destination )
{
#ifdef WINDOWS
	return CopyFile( source.c_str(), destination.c_str(), false ) != 0;
#else
    // TODO
    assert(!"Not Yet Implemented");
    return  false;
#endif
}