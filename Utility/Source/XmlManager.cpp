#include "../Include/XmlManager.hpp"

#include <fstream>
#include <ostream>
#include <cstring>

#include "../Include/rapidxml/rapidxml_print.hpp"

using namespace Fnd::Utility;

XmlManager::XmlManager():
	_buffer(new char[XML_BUFFER_SIZE]),
	_exists(false),
	_xml()
{
	memset(_buffer,0,XML_BUFFER_SIZE);
}

bool XmlManager::CreateFromFile( const std::string& filename )
{
	if ( Exists() )
	{
		return false;
	}

	std::ifstream file( filename.c_str(), std::ios::in );

	if ( file.is_open() )
	{
		file.seekg( 0, std::ios::end );

		unsigned int file_length = (unsigned int)file.tellg();

		memset(_buffer,0,XML_BUFFER_SIZE);

		file.seekg( 0, std::ios::beg );
		file.read( _buffer, file_length );
		file.close();

	}
	else
	{
		return false;
	}

	return Create();
}

bool XmlManager::CreateFromBuffer( const char* buffer )
{
	if ( Exists() )
	{
		return false;
	}

	size_t buffer_length = strlen( buffer );

	memset(_buffer,'\0',XML_BUFFER_SIZE);
	memcpy( _buffer, buffer, buffer_length );

	return Create();
}

bool XmlManager::Create()
{
	try
	{
		_xml.clear();
		_xml.parse<0>(_buffer);
	}
	catch (rapidxml::parse_error e)
	{
		_xml.clear();

		return false;
	}

	_exists = true;

	return true;
}

bool XmlManager::WriteToFile( const std::string& filename )
{
	std::ofstream file;

	file.open( filename.c_str() );

	if ( file.is_open() )
	{
		file << _xml;

		file.close();
	}
	else
	{
		return false;
	}

	return true;
}

const rapidxml::xml_document<>& XmlManager::Xml() const
{
	return _xml;
}

rapidxml::xml_document<>& XmlManager::Xml()
{
	return _xml;
}

void XmlManager::Release()
{
	_xml.clear();

	_exists = false;
}

bool XmlManager::Exists() const
{
	return _exists;
}

XmlManager::~XmlManager()
{
	Release();

	if ( _buffer )
	{
		delete[] _buffer;
	}
}
