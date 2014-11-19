#pragma once

#ifndef _ENTITYSYSTEMGENERATOR_CODEGENERATOR_HPP_
#define _EntITYSYSTEMGENERATOR_CODEGENERATOR_HPP_

#include <sstream>
#include <vector>

namespace Fnd
{
namespace EntitySystemCodeGeneration
{

/**
	Base class for code generator classes.

	Provides methods to write the file and access the string stream.
*/
class CodeGenerator
{
	public:

		CodeGenerator();

	protected:

		void SetFilename( const std::string& filename );

		void AddInclude( const std::string& include_file );

		std::stringstream& File();

		void WriteComment();

		void WriteHeaderGuardStart();

		void WriteIncludeFiles();

		void WriteHeaderGuardEnd();

		bool WriteToFile();

	private:

		std::vector<std::string> _include_files;
		
		std::string _filename;

		std::stringstream _file;
};

}
}

#endif