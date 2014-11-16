#pragma once

#ifndef _XMLMANAGER_HPP_
#define _XMLMANAGER_HPP_

#include "rapidxml/rapidxml.hpp"

#include <string>

// The maximum size of the buffer- currently set to 32MB
#define XML_BUFFER_SIZE (1024*1024*32)

namespace Fnd
{
namespace Utility
{

/**
	A wrapper class for rapidxml.

	A wrapper class for rapidxml which handles the loading and
	saving of .xml files.
*/
class XmlManager
{
	public:

		/**
			Default Constructor.
		*/
		XmlManager();

		/**
			Load a file into the internal buffer and create the rapidxml document.
			@param filename The name of the .xml file to load.
			@return Returns true if the rapidxml document was created successfully.
		*/
		bool CreateFromFile( const std::string& filename );

		/**
			Copy a string into the internal buffer and create the rapidxml document.
			@param buffer A null terminated string containing xml data.
			@return Returns true if the rapidxml document was created successfully.
		*/
		bool CreateFromBuffer( const char* buffer );

		/**
			Write the rapidxml document to an xml file.
			@param filename The name of the file to write to.
			@return Returns true if the rapidxml document was written to the file successfully.
		*/
		bool WriteToFile( const std::string& filename );

		/**
			Get the rapidxml document.
			@return Returns a const reference to the rapidxml document.
		*/
		const rapidxml::xml_document<>& Xml() const;

		/**
			Get the rapidxml document.
			@return Returns a reference to the rapidxml document.
		*/
		rapidxml::xml_document<>& Xml();

		/**
			Get whether or not a rapidxml document has been created.
			@return Returns true if a rapidxml document has been successfully created.
		*/
		bool Exists() const;

		/**
			Release the rapidxml document.
			Does nothing if the rapidxml document has not been created.
		*/
		void Release();

		/**
			Destructor.
		*/
		~XmlManager();

	private:

		/**
			Create the rapidxml document from the internal buffer.
			@return Returns true if the rapidxml document is created successfully.
		*/
		bool Create();

		char* _buffer;

		bool _exists;

		rapidxml::xml_document<> _xml;
};

}
}

#endif
