/*
* Test implementation of the application class
*/
#include <string>
#include <core/core_types.hpp>
#include <core/IApp.hpp>

using namespace psm;

class PSMAPP : public IApp
{
	/*
	* Fill with useless methods
	*/

public:
	PSMAPP(const std::string title = "PSS");

	virtual ~PSMAPP();

protected:

	virtual void initCustomAssetHandlers();

	virtual void initCustomGameStates();

	virtual void handleCustomCleanup();

	void processInput(IState& theState);	
};