/*
* This class wraps the sf::Texture class for use in the game application
*/

#include <assert.h>
#include <stddef.h>
#include <core/TextureAsset.hpp>

namespace psm
{

	psm::TextureAsset::TextureAsset() :
	TAsset<sf::Texture>()
	{
	}

	psm::TextureAsset::TextureAsset(const typeAssetID assetID) :
		TAsset<sf::Texture>(assetID)
	{
	}

	psm::TextureAsset::~TextureAsset()
	{
	}

}
