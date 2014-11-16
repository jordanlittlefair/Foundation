#pragma once

#ifndef _ASSET_HPP_
#define _ASSET_HPP_

#include <string>

namespace Fnd
{
namespace AssetManager
{

/**
	Base class for all asset types.
*/
class Asset
{
	public:

		/**
			Default Constructor.
		*/
		Asset();

		/**
			Set the name of the content.
			Should be the file name, or another appropriate identifier.
			@param name The name used to identify the content.
		*/
		void SetName( const std::string& name );

		/**
			Get the name of the content.
			@return Returns the name used to identify the content.
		*/
		std::string GetName() const;

		/**
			Get a pointer to the resource stored in this content.
			The pointer must be cast to the appropriate resource type.
			@return Returns a void pointer to the resource.
		*/
		virtual void* GetResource() = 0;

		/**
			Virtual destructor.
		*/
		virtual ~Asset();

	private:

		std::string _name;
};

}
}

#endif