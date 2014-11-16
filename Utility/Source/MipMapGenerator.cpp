#include "../Include/MipMapGenerator.hpp"

#include "../Include/Utility.hpp"

using namespace Fnd::Utility;

unsigned int MipMapGenerator::GetNumMipLevels( const Image& image )
{
	return GetNumMipLevels( image.GetWidth(), image.GetHeight() );
}

unsigned int MipMapGenerator::GetNumMipLevels( unsigned int width, unsigned int height )
{
	unsigned int to_return = 1;

	while ( ( width > 1 ) || ( height > 1 ) )
	{
		width = Max( width / 2, 1u );
		height = Max( height / 2, 1u );
		++to_return;
	}
	return to_return;
}

std::vector<Image> MipMapGenerator::GenerateMipMaps( const Image& image, unsigned int max_mip_level )
{
	std::vector<Image> ret;

	// Level 0 is the original image
	ret.push_back(image);

	max_mip_level = Min( GetNumMipLevels(image), max_mip_level );

	for ( unsigned int level = 1; level < max_mip_level; ++level )
	{
		Image this_mip;
		unsigned int this_mip_width = Max( ret.back().GetWidth() / 2, 1u );
		unsigned int this_mip_height = Max( ret.back().GetHeight() / 2, 1u );
		
		this_mip.CreateImage( this_mip_width, this_mip_height, image.GetFormat() );
		
		auto& prev_mip = ret.back();
		unsigned int prev_width = prev_mip.GetWidth();
		unsigned int prev_height = prev_mip.GetHeight();

		for ( unsigned int y = 0; y < this_mip.GetHeight(); ++y )
		{
			for ( unsigned int x = 0; x < this_mip.GetWidth(); ++x )
			{
				for ( int c = 0; c < this_mip.GetFormat(); ++c )
				{
					unsigned int sum = 0;
					unsigned int samples = 4;

					// Warning: only works with n^2 x n^2 textures!

					sum += prev_mip.GetByteAt( Min( x * 2, prev_width ),		Min( y * 2, prev_height ),		c );
					sum += prev_mip.GetByteAt( Min( x * 2, prev_width ),		Min( y * 2 + 1, prev_height ),	c );
					sum += prev_mip.GetByteAt( Min( x * 2 + 1, prev_width ),	Min( y * 2, prev_height ),		c );
					sum += prev_mip.GetByteAt( Min( x * 2 + 1, prev_width ),	Min( y * 2 + 1, prev_height ),	c );

					this_mip.GetByteAt( x, y, c ) = sum / samples;

					// TODO: needs fixing
					/*float x_scale = ((float)ret.back().GetWidth()) / ((float)this_mip.GetWidth());
					float y_scale = ((float)ret.back().GetHeight()) / ((float)this_mip.GetHeight());

					float x_f = x_scale * x;
					float y_f = y_scale * y;

					this_mip.GetByteAt(x,y,c) = Sample( ret.back(), x_f, y_f, c );*/
				}
			}
		}

		ret.push_back(this_mip);
	}

	Sample( image, 0.5f, 0.5f, 0 );

	return ret;
}

char MipMapGenerator::Sample( const Image& image, float x, float y, char channel )
{
	unsigned int xmin = (unsigned int)floor(x);
	unsigned int xmax = (unsigned int)ceil(x);
	unsigned int ymin = (unsigned int)floor(y);
	unsigned int ymax = (unsigned int)ceil(y);

	float x_range = Max( 1.0f, ((float)xmax)-((float)xmin) );
	float y_range = Max( 1.0f, ((float)ymax)-((float)ymin) );

	float xminscale = x_range == 0 ? 1 : ( x - xmin ) / x_range;
	float xmaxscale = 1 - xminscale;

	float yminscale = y_range == 0 ? 1 : ( y - ymin ) / y_range;
	float ymaxscale = 1 - yminscale;

	float xmin_ymin_scale = xminscale * yminscale;
	float xmin_ymax_scale = xminscale * ymaxscale;
	float xmax_ymin_scale = xmaxscale * yminscale;
	float xmax_ymax_scale = xmaxscale * ymaxscale;

	float xmin_ymin_value = image.GetByteAt( xmin, ymin, channel );
	float xmin_ymax_value = image.GetByteAt( xmin, ymax, channel );
	float xmax_ymin_value = image.GetByteAt( xmax, ymin, channel );
	float xmax_ymax_value = image.GetByteAt( xmax, ymax, channel );

	float result =
		xmin_ymin_value * xmin_ymin_scale +
		xmin_ymax_value * xmin_ymax_scale +
		xmax_ymin_value * xmax_ymin_scale +
		xmax_ymax_value * xmax_ymax_scale;

	return (char)result;
}