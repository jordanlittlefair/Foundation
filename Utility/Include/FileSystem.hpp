#pragma once

#ifndef _FILESYSTEM_HPP_
#define _FILESYSTEM_HPP_

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

}
}
}

#endif