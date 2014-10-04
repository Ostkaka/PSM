/*
* IAssetHandler Class provides handling and management of IAsset derived classes
*/

#include <assert.h>
#include <core/IAssetHandler.hpp>

namespace psm
{

	IAssetHandler::IAssetHandler(const typeAssetHandlerID assetHandlerID) :
	mAssetHandlerID(assetHandlerID)
	{
	}
	
	IAssetHandler::~IAssetHandler()
	{
	}

	const typeAssetHandlerID IAssetHandler::getID() const
	{
		return mAssetHandlerID;
	}
}