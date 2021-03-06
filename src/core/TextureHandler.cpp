/*
* Derived class from IAssetHandler for managing sf:Textures
*/

#include <core/TextureHandler.hpp>
#include <iostream>

namespace psm
{
	TextureHandler::TextureHandler():
		TAssetHandler<sf::Texture>()
	{
	}

	TextureHandler::~TextureHandler()
	{
	}

	bool TextureHandler::loadFromFile(const typeAssetID assetID, sf::Texture& asset)
	{
		// Start with a return result of false
		bool succLoad = false;

		// Retrieve the filename for this asset
		std::string filename = assetID;

		// Was a valid filename found? then attempt to load the asset from anFilename
		if(filename.length() > 0)
		{
			// Load the asset from a file
			succLoad = asset.loadFromFile(filename);
		}
		else
		{
			;
			///ELOG() << "TextureHandler::LoadFromFile(" << assetID
				//<< ") No filename provided!" << std::endl;
		}

		// Return anResult of true if successful, false otherwise
		return succLoad;
	}
}
