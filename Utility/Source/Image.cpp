#define _CRT_SECURE_NO_WARNINGS	// prevents warnings when compiling in visual studio

#include "../Include/Image.hpp"

#include <fstream>

#include <cstring>

using namespace Fnd::Utility;

Image::Image():
	_width(0),
	_height(0),
	_format(Unknown_Format),
	_num_bytes(0),
	_data(0)
{
}

bool Image::IsValid() const
{
	return _data != 0;
}

Image::Result Image::CreateDefaultImage(	unsigned int width,
											unsigned int height,
											Format format )
{
	if ( width * height * format == 0 )
	{
		return Error_Invalid_Parameters;
	}

	if ( IsValid() )
	{
		return Error_In_Use;
	}

	_width = width;
	_height = height;
	_format = format;

	_num_bytes = width * height * format;

	_data = new unsigned char[_num_bytes];

	return OK_Return;
}

Image::Result Image::CreateImage(	unsigned int width,
									unsigned int height,
									Format format,
									unsigned char r,
									unsigned char g,
									unsigned char b,
									unsigned char a  )
{
	Result result = CreateDefaultImage( width, height, format );

	if ( result != OK_Return )
	{
		return result;
	}

	unsigned char rgba_pixel[4] = { r, g, b, a };

	unsigned int num_pixels = _width * _height;

	for ( int i = 0; i < _format; ++i )
	{
		for ( unsigned int j = 0; j < num_pixels; ++j )
		{
			_data[j*_format+i] = rgba_pixel[i];
		}
	}

	return OK_Return;
}

Image::Result Image::CreateImageFromFile(	const std::string& filename,
											Format desired_format,
											unsigned char r,
											unsigned char g,
											unsigned char b,
											unsigned char a )
{
	if ( IsValid() )
	{
		return Error_In_Use;
	}

	Result result = OK_Return;

	FileType file_type = GetFileType( filename );

	if ( file_type == TGA_FileType )
	{
		result = LoadTGA( filename );
	}
	else
	if ( file_type == BMP_FileType )
	{
		result = LoadBMP( filename );
	}
	else
	{
		result = Error_Unsupported_File_Type;
	}

	if ( result != OK_Return )
	{
		return result;
	}

	if ( _format != desired_format )
	{
		result = ConvertToFormat( desired_format, r, g, b, a );
	}

	return result;
}

Image::Result Image::SaveImageToFile(	const std::string& filename )
{
	Result result = OK_Return;

	FileType file_type = GetFileType( filename );

	if ( file_type == TGA_FileType )
	{
		result = SaveTGA( filename );
	}
	else
	if ( file_type == BMP_FileType )
	{
		result = SaveBMP( filename );
	}
	else
	{
		result = Error_Unsupported_File_Type;
	}

	return result;
}

Image::Result Image::ConvertToFormat(	Format format,
										unsigned char r,
										unsigned char g,
										unsigned char b,
										unsigned char a )
{
	if ( format == Unknown_Format )
	{
		return Error_Invalid_Parameters;
	}

	if ( !IsValid() )
	{
		return Error_Invalid_Image;
	}

	unsigned char rgba_pixel[4] = { r, g, b, a };

	Format old_format = _format;
	unsigned char* old_data = _data;

	_format = format;
	_num_bytes = _width * _height * _format;
	_data = new unsigned char[_num_bytes];

	unsigned int num_pixels = _width * _height;

	for ( int i = 0; i < _format; ++i )
	{
		if ( i < old_format )
		{
			for ( unsigned int j = 0; j < num_pixels; ++j )
			{
				_data[j*_format+i] = old_data[j*old_format+i];
			}
		}
		else
		{
			for ( unsigned int j = 0; j < num_pixels; ++j )
			{
				_data[j*_format+i] = rgba_pixel[i];
			}
		}
	}

	delete[] old_data;

	return OK_Return;
}

unsigned char* Image::GetData()
{
	return _data;
}

unsigned int Image::GetWidth() const
{
	return _width;
}

unsigned int Image::GetHeight() const
{
	return _height;
}

unsigned int Image::GetNumBytes() const
{
	return _num_bytes;
}

Image::Format Image::GetFormat() const
{
	return _format;
}

unsigned char& Image::GetByte( unsigned int i )
{
	return _data[i];
}

const unsigned char& Image::GetByte( unsigned int i ) const
{
	return _data[i];
}

unsigned char& Image::GetByteAt( unsigned int x, unsigned int y, unsigned int c )
{
	return _data[	x * _format +
					y * _format * _width +
					c ];
}

const unsigned char& Image::GetByteAt( unsigned int x, unsigned int y, unsigned int c ) const
{
	return _data[	x * _format +
					y * _format * _width +
					c ];
}

void Image::Destroy()
{
	_width = 0;
	_height = 0;
	_format = Unknown_Format;

	if ( _data )
	{
		delete[] _data;
		_data = 0;
	}
}

Image::~Image()
{
	Destroy();
}

Image::Image( const Image& to_copy ):
	_width(to_copy._width),
	_height(to_copy._height),
	_format(to_copy._format),
	_num_bytes(to_copy._num_bytes),
	_data( new unsigned char[to_copy._num_bytes] )
{
	memcpy( _data, to_copy._data, _num_bytes );
}

Image& Image::operator =( Image& rhs )
{
	return rhs;
}

Image::FileType Image::GetFileType( const std::string& file_name )
{
	// get file extension as string
	const std::string file_extension = file_name.substr( file_name.rfind('.') + 1 );

	if ( file_extension == "tga" )
	{
		return TGA_FileType;
	}
	else
	if ( file_extension == "bmp" )
	{
		return BMP_FileType;
	}

	return Unknown_FileType;
}

Image::Result Image::LoadTGA( const std::string& filename )
{
	FILE* file = 0;
	file = fopen( filename.c_str(), "rb" );

	if ( !file )
	{
		return Error_Failed_To_Open_File;
	}

	unsigned char header[18];

	// Read header data.
	fread( &header, sizeof(unsigned char), 18, file );

	unsigned int channels_per_pixel = header[16] / 8;

	// Check if colour format is compatible with the channels per pixel.
	// Only supports uncompressed true colour data (2),
	// and uncompressed greyscale (3) if there is only 1 channel per pixel.
	if (	channels_per_pixel == 3 ||
			channels_per_pixel == 4 )
	{
		if ( header[2] != 2 )
		{
			fclose(file);
			return Error_Unsupported_Format;
		}
	}
	else
	if ( channels_per_pixel == 1 )
	{
		if ( header[2] != 3 )
		{
			fclose(file);
			return Error_Unsupported_Format;
		}
	}
	else
	{
		fclose(file);
		return Error_Unsupported_Format;
	}

	_format = (Format)channels_per_pixel;

	// Get width and height.
	_width = header[12] + header[13] * 256;
	_height = header[14] + header[15] * 256;

	_num_bytes = _width * _height * _format;

	// copy image data to data_as_bytes
	_data = new unsigned char[_width * _height * _format];
	fread( _data, sizeof(unsigned char), _width * _height * _format, file );

	fclose(file);

	// Swap from BGR to RGB
	if ( _format == RGB_Format )
	{
		for ( unsigned int i = 0; i < _width * _height; ++i )
		{
			unsigned char bgr[3] = { _data[ _format * i + 0 ],
                                    _data[ _format * i + 1 ],
                                    _data[ _format * i + 2 ] };

			_data[ _format * i + 0 ] = bgr[2];
			_data[ _format * i + 1 ] = bgr[1];
			_data[ _format * i + 2 ] = bgr[0];
		}
	}
	else
	// Swap from BGRA to RGBA
	if ( _format == RGBA_Format )
	{
		for ( unsigned int i = 0; i < _width * _height; ++i )
		{
			unsigned char bgra[4] = { 	_data[ _format * i + 0 ],
                                    _data[ _format * i + 1 ],
                                        _data[ _format * i + 2 ],
                                        _data[ _format * i + 3 ] };

			_data[ _format * i + 0 ] = bgra[2];
			_data[ _format * i + 1 ] = bgra[1];
			_data[ _format * i + 2 ] = bgra[0];
			_data[ _format * i + 2 ] = bgra[3];
		}
	}


	return OK_Return;
}

Image::Result Image::LoadBMP( const std::string& file_name )
{
	FILE* file = 0;
	file = fopen( file_name.c_str(), "rb" );

	if ( !file )
	{
		return Error_Failed_To_Open_File;
	}

	unsigned char header[54];

	// Read header data.
	fread( &header, sizeof(char), 54, file );

	const unsigned int bytes_per_pixel = header[28] + header[29] * 256;

	// Check data is compatible with specified format
	// rgb or rgba
	if ( !(	bytes_per_pixel == 3 ||
			bytes_per_pixel == 4 ))
	{
		fclose(file);
		return Error_Unsupported_Format;
	}

	_format = (Format)bytes_per_pixel;

	_width = header[18] + header[19] * 256 + header[20] * 65536 + header[21] * 16777216;
	_height = header[22] + header[23] * 256 + header[24] * 65536 + header[25] * 16777216;

	_num_bytes = _width * _height * _format;

	unsigned int bytes_per_line_with_padding =  ( _format * _width ) + ( ( _width * _format ) % 4 );

	const unsigned int bytes_per_line = _format * _width;

	// Array to store a line of pixel data as it is read; contains padding
	unsigned char* pixels_and_padding = new unsigned char[ bytes_per_line_with_padding ];

	_data = new unsigned char[_width * _height * _format];

	// read each line into pixels_and_padding, then copy each byte (minus padding) to data_as_bytes
	for ( unsigned int y = 0; y < _height; ++y )
	{
		fread( (void*)pixels_and_padding, sizeof(unsigned char), bytes_per_line_with_padding, file );

		for ( unsigned int byte = 0; byte < bytes_per_line; ++byte )
		{
			(_data)[ y * bytes_per_line + byte ] = pixels_and_padding[ byte ];
		}
	}

	delete[] pixels_and_padding;

	fclose(file);

	return OK_Return;
}

Image::Result Image::SaveTGA( const std::string& filename )
{
	if ( !IsValid() )
	{
		return Error_Invalid_Image;
	}

	std::ofstream file;

	file.open( filename.c_str(), std::ios::binary );

	if ( !file.is_open() )
	{
		return Error_Failed_To_Open_File;
	}

	// Write header.
	unsigned char header[ 18 ] = { 0 };
	header[  2 ] = (unsigned char)( _format == R_Format ) ? 3 : 2;	// Set greyscale or true colour.
	header[ 12 ] = (unsigned char)_width;
	header[ 13 ] = (unsigned char)(_width >> 8);
	header[ 14 ] = (unsigned char)_height;
	header[ 15 ] = (unsigned char)(_height >> 8);
	header[ 16 ] = (unsigned char)(unsigned short int ) ( _format * 8);  // bits per pixel

	file.write( (char*)header, 18 );

	// Write data.
	for ( unsigned int i = 0; i < _num_bytes; ++i )
	{
		file << _data[i];
	}

	file.close();

	return OK_Return;
}

Image::Result Image::SaveBMP( const std::string& filename )
{
	if ( !IsValid() )
	{
		return Error_Invalid_Image;
	}

	if ( _format == 1 )
	{
		return Error_Unsupported_Format;
	}

	std::ofstream file;

	file.open( filename.c_str(), std::ios::binary );

	if ( !file.is_open() )
	{
		return Error_Failed_To_Open_File;
	}

	// write header
	const unsigned int pad_size = ( _width * _format ) % 4;

	// size of bmp data
	const unsigned int bmp_size = ( _width + pad_size ) * _height * _format;

	// size of file
	const unsigned int file_size = 54u + bmp_size;
	unsigned char header[54] = { 0 };
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	header[2] = (unsigned char)( file_size );
	header[3] = (unsigned char)( file_size >> 8 );
	header[4] = (unsigned char)( file_size >> 16 );
	header[5] = (unsigned char)( file_size >> 24 );
	header[14] = (unsigned char)40;
	header[18] = (unsigned char)( _width );
	header[19] = (unsigned char)( _width >> 8 );
	header[20] = (unsigned char)( _width >> 16 );
	header[21] = (unsigned char)( _width >> 24 );
	header[22] = (unsigned char)( _height );
	header[23] = (unsigned char)( _height >> 8 );
	header[24] = (unsigned char)( _height >> 16 );
	header[25] = (unsigned char)( _height >> 24 );
	header[26] = (unsigned char)1;
	header[28] = (unsigned char)( _format * 8 );

	file.write( (char*)header, 54 );

	for ( unsigned int y = 0; y < _height; ++y )
	{
		for ( unsigned int x = 0; x < _width; ++x )
		{
			for ( int byte = 0; byte < _format; ++byte )
			{
				file << _data[ y * _width * _format + x * _format + byte ];
			}
		}
		// add padding: lines must be a multiple of 4 bytes long
		for ( unsigned int i = 0; i < pad_size; ++i )
		{
			file << (unsigned char)0;
		}
	}

	file.close();

	return OK_Return;
}



















