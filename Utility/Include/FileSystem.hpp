#pragma once

#ifndef _UTILITY_FILESYSTEM_HPP_
#define _UTILITY_FILESYSTEM_HPP_

#include <string>
#include <vector>

namespace Fnd
{
namespace Utility
{
namespace FileSystem
{

bool CreateNewDirectory( const std::string& directory_name );

std::string CanonicaliseFile( const std::string& filename );

std::string CanonicaliseDirectory( const std::string& directory );

void GetPathAndName( const std::string& full_path, std::string& path, std::string& name );

std::string GetWorkingDirectory();

// Does not handle nested "s
std::vector<std::string> ParseCommandLine( const std::string& command_line );

// Get a vector of parent directories.
std::vector<std::string> GetDirectories( const std::string& directory );

bool CopyFile_( const std::string& source, const std::string& destination );

}
}
}

#endif