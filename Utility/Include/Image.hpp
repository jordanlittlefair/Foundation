#pragma once

#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#include <string>

namespace Fnd
{
namespace Utility
{

/**
	A class to handle image loading and saving.

	Currently supports uncompressed bmp and tga files.
*/
class Image
{
	public:
	
		/**
			An enum to describe the number of components per pixel.
		*/
		enum Format
		{
			Unknown_Format = 0,
			R_Format = 1,
			RG_Format = 2,
			RGB_Format = 3,
			RGBA_Format = 4
		};
		
		/**
			An enum to describe an error when performing operations on the image.
		*/
		enum Result
		{
			OK_Return = 0,
			Error_Invalid_Parameters = 1 << 0,
			Error_In_Use = 1 << 1,
			Error_Invalid_Image = 1 << 2,
			Error_Unsupported_File_Type = 1 << 3,
			Error_Failed_To_Open_File = 1 << 4,
			Error_Unsupported_Format = 1 << 5			
		};
	
	public:
		
		/**
			Default constructor.
			Creates an image with no data.
		*/
		Image();
		
		/**
			Get whether or not the image has data.
			@return Returns true if the image has been loaded/created.
		*/
		bool IsValid() const;
		
		/**
			Create an image with undefined default values.
			@note The data will not be set to a default value.
			@param width The width of the image to create.
			@param height The height of the image to create.
			@param format The number of components per pixel.
			@return Returns an error if the creation was unsuccessful.
		*/
		Result CreateDefaultImage(	unsigned int width,
									unsigned int height,
									Format format );
		
		/**
			Create an image with user defined default values.
			@param width The width of the image to create.
			@param height The height of the image to create.
			@param format The number of components per pixel.
			@param r The default value of the 'r' component.
			@param g The default value of the 'g' component.
			@param b The default value of the 'b' component.
			@param a The default value of the 'a' component.
			@return Returns an error if the creation was unsuccessful.
		*/
		Result CreateImage(	unsigned int width,
							unsigned int height,
							Format format,
							unsigned char r = 0,
							unsigned char g = 0,
							unsigned char b = 0,
							unsigned char a = 0 );
							
		/**
			Load an uncompressed BMP or TGA image.
			@note The desired format may be different to the loaded image's format.\n
			-A desired format with more components than the loaded image will use the r,g,b,a parameters as default values.\n
			-A desired format with fewer components than the loaded image will ignore the additional components.
			@note 'filename' should end in '.bmp' or '.tga'.
			@param filename The name of the image to load.
			@param desired_format The desired number of components per pixel.
			@param r The default value of the 'r' component.
			@param g The default value of the 'g' component.
			@param b The default value of the 'b' component.
			@param a The default value of the 'a' component.
			@return Returns an error if the creation was unsuccessful.
		*/
		Result CreateImageFromFile(	const std::string& filename,
									Format desired_format,
									unsigned char r = 0,
									unsigned char g = 0,
									unsigned char b = 0,
									unsigned char a = 0 );
		
		/**
			Save an uncompressed BMP or TGA image.
			@note 'filename' should end in '.bmp' or '.tga'.
			@param filename The name of the file to save to.
			@return Returns an error if the creation was unsuccessful.
		*/
		Result SaveImageToFile(	const std::string& filename );
		
		/**
			Convert the image to a different format.
			@param format The desired number of components per pixel.
			@param r The default value of the 'r' component.
			@param g The default value of the 'g' component.
			@param b The default value of the 'b' component.
			@param a The default value of the 'a' component.
			@return Returns an error if the creation was unsuccessful.
		*/
		Result ConvertToFormat(	Format format,
								unsigned char r = 0,
								unsigned char g = 0,
								unsigned char b = 0,
								unsigned char a = 0 );
		
		/**
			Get a pointer to the data.
			@return Returns a pointer to the first byte of the image data.
		*/
		unsigned char* GetData();
	
		/**
			Get the width of the image.
			@return Returns the width of the image.
		*/
		unsigned int GetWidth() const;
		
		/**
			Get the height of the image.
			@return Returns the height of the image.
		*/
		unsigned int GetHeight() const;
		
		/**
			Get the size of the image.
			@return Returns the size of the image in bytes.
		*/
		unsigned int GetNumBytes() const;
		
		/**
			Get the format of the image.
			@return Returns the format of the image.
		*/
		Format GetFormat() const;
		
		// Get a byte from the image as a 1D array.
		unsigned char& GetByte( unsigned int i );
		
		// Get a byte from the image as a 1D array.
		const unsigned char& GetByte( unsigned int i ) const;
		
		// Get a byte from the image using the pixel and channel.
		unsigned char& GetByteAt( unsigned int x, unsigned int y, unsigned int c );
		
		// Get a byte from the image using the pixel and channel.
		const unsigned char& GetByteAt( unsigned int x, unsigned int y, unsigned int c ) const;
		
		void Destroy();
		
		~Image();
		
		Image( const Image& to_copy );
		
	private:
	
		enum FileType
		{
			Unknown_FileType,
			TGA_FileType,
			BMP_FileType
		};
		
		
		
		Image& operator =( Image& rhs );
	
		FileType GetFileType( const std::string& file_name );
	
		Result LoadTGA( const std::string& filename );
		
		Result LoadBMP( const std::string& filename );
		
		Result SaveTGA( const std::string& filename );
		
		Result SaveBMP( const std::string& filename );
		
	private:

		unsigned int _width;
		unsigned int _height;
		
		Format _format;
		
		unsigned int _num_bytes;
		
		unsigned char* _data;
};

}
}

#endif