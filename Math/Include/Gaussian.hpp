#pragma once

#ifndef _MATH_GAUSSIAN_
#define _MATH_GAUSSIAN_

namespace Fnd
{
namespace Math
{

/**
	Get the point on a 1D gaussian curve.
	@param x The distance from the mean.
	@param sigma The standard deviation.
	@return Returns the weight on the curve at point x.
*/
inline float GaussianWeight1D( float x, float sigma );

/**
	Get a normalised array of points on a 1D gaussian curve.
	@param w The number of points in the array.
	@param sigma The standard deviation.
	@param weights An array of 'w' floats in which to write the results.
*/
inline void GaussianWeightsArray1D( unsigned int w, float sigma, float* weights );

/**
	Get a normalised 1D kernel of weights.
	@param w The number of points in the array.
	@param sigma The standard deviation.
	@param weights An array of 'w' floats in which to write the results.
*/
inline void GaussianWeightsKernel1D( unsigned int w, float sigma, float* weights );

/**
	Get the point on a 3D gaussian curve.
	@param x The x distance from the mean.
	@param y The y distance from the mean.
	@param sigma The standard deviation.
	@return Returns the weight on the curve at point x.
*/
inline float GaussianWeight2D( float x, float y, float sigma );

/**
	Get a normalised array of points on a 2D gaussian curve.
	@param w The number of points in the array in the x direction.
	@param h The number of points in the array in the y direction.
	@param sigma The standard deviation.
	@param weights An array of 'w*h' floats in which to write the results.
*/
inline void GaussianWeightsArray2D( unsigned int w, unsigned int h, float sigma, float* weights );

/**
	Get a normalised 1D kernel of weights.
	@param w The number of points in the array in the x direction.
	@param h The number of points in the array in the y direction.
	@param sigma The standard deviation.
	@param weights An array of 'w*h' floats in which to write the results.
*/
inline void GaussianWeightsKernel2D( unsigned int w, unsigned int h, float sigma, float* weights );


/*
	--------------------------------
	Implementation.
*/

#include "MathUtility.hpp"

inline float GaussianWeight1D( float x, float sigma )
{	
	return ( 1 / sqrt( 2 * Pi<float>() * sigma * sigma ) ) * exp( -( x * x ) / ( 2 * sigma * sigma ) );
}

inline void GaussianWeightsArray1D( unsigned int w, float sigma, float* weights )
{
	float sum = 0;
	
	for ( unsigned int x = 0; x < w; ++x )
	{
		sum += ( weights[x] = GaussianWeight1D( (float)x, sigma ) );
	}
	
	for ( unsigned int x = 0; x < w; ++x )
	{
		weights[x] /= sum;
	}
}

inline void GaussianWeightsKernel1D( unsigned int w, float sigma, float* weights )
{
	float sum = 0;
	
	float offset = ((float)(w - 1)) / 2.0f;
	
	for ( unsigned int x = 0; x < w; ++x )
	{
		sum += ( weights[x] = GaussianWeight1D( x - offset, sigma ) );
	}
	
	for ( unsigned int x = 0; x < w; ++x )
	{
		weights[x] /= sum;
	}
}

inline float GaussianWeight2D( float x, float y, float sigma )
{	
	return ( 1 / sqrt( 2 * Pi<float>() * sigma * sigma ) ) * exp( -( ( x * x ) + ( y * y ) ) / ( 2 * sigma * sigma ) );
}

inline void GaussianWeightsArray2D( unsigned int w, unsigned int h, float sigma, float* weights )
{
	float sum = 0;
	
	for ( unsigned int x = 0; x < w; ++x )
	{
		for ( unsigned int y = 0; y < h; ++y )
		{
			sum += ( weights[x+y*w] = GaussianWeight2D( (float)x, (float)y, sigma ) );
		}
	}
	
	for ( unsigned int x = 0; x < w; ++x )
	{
		for ( unsigned int y = 0; y < h; ++y )
		{
			weights[x+y*w] /= sum;
		}
	}
}

inline void GaussianWeightsKernel2D( unsigned int w, unsigned int h, float sigma, float* weights )
{
	float sum = 0;
	
	float x_offset = ((float)(w - 1)) / 2.0f;
	float y_offset = ((float)(h - 1)) / 2.0f;
	
	for ( unsigned int x = 0; x < w; ++x )
	{
		for ( unsigned int y = 0; y < h; ++y )
		{
			sum += ( weights[x+y*w] = GaussianWeight2D( x - x_offset, y - y_offset, sigma ) );
		}
	}
	
	for ( unsigned int x = 0; x < w; ++x )
	{
		for ( unsigned int y = 0; y < h; ++y )
		{
			weights[x+y*w] /= sum;
		}
	}
}

}
}

#endif