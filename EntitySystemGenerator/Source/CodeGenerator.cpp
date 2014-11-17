#include "..\Include\CodeGenerator.hpp"

#include <fstream>

using namespace Fnd::EntitySystemCodeGeneration;

CodeGenerator::CodeGenerator()
{
}

void CodeGenerator::SetFilename( const std::string& filename )
{
	_filename = filename;
}

void CodeGenerator::AddInclude( const std::string& include_file )
{
	_include_files.push_back(include_file);
}

bool CodeGenerator::WriteToFile()
{
	std::ofstream file( _filename );

	if ( file.is_open() )
	{
		file << _file.str();
		file.close();

		return true;
	}
	else
	{
		return false;
	}
}

std::stringstream& CodeGenerator::File()
{
	return _file;
}

void CodeGenerator::WriteComment()
{
	_file <<
"/*\n\
\tThis file is automatically generated.\
\n\
\tDo not edit this file manually.\n\
*/\n\n";
}

void CodeGenerator::WriteHeaderGuardStart()
{
	std::string def;
	for ( unsigned int i = 0; i < _filename.size(); ++i )
	{
		def.push_back( toupper(_filename[i]) );
		if ( def.back() == '.' )
		{
			def.back() = '_';
		}
		else
		if ( def.back() == '/' )
		{
			def.back() = '\\';
		}
	}
	
	def = "_" + def.substr( def.find_last_of('\\')+1, std::string::npos ) + "_";

	_file << "#ifndef " << def << '\n';
	_file << "#define " << def << "\n\n";
}

void CodeGenerator::WriteIncludeFiles()
{
	for ( unsigned int i = 0; i < _include_files.size(); ++i )
	{
		_file << "#include \"" << _include_files[i] << "\"\n";
	}
	_file << '\n';
}

void CodeGenerator::WriteHeaderGuardEnd()
{
	_file << "#endif\n";
}