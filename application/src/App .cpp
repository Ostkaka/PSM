#include "App.hpp"
#include "SplashState.hpp"
#include <core/IState.hpp>
#include <ctime>

using namespace psm;
/*
* Test implemenation of the application class
*/

PSMAPP::PSMAPP(const std::string title /*= "TestApp"*/) :
IApp(title)
{		
}

PSMAPP::~PSMAPP()
{	
}

void PSMAPP::initCustomAssetHandlers()
{
	//Test custom asset stuff
}

void PSMAPP::initCustomGameStates()
{
	//mStateManager.addActiveState(new(std::nothrow) InitState(*this));
	mStateManager.addInactiveState(new(std::nothrow) SplashState(*this,5));
	//mStateManager.addInactiveState(new(std::nothrow) GameState(*this));
}

void PSMAPP::handleCustomCleanup()
{
}

void PSMAPP::processInput(IState& state)
{
	// Variable for storing the current input event to be processed
	sf::Event tEvent;

	while (mWindow.pollEvent(tEvent))
	{
		// Handle some input events and let the current state handle the rest
		// Switch on Event Type
		switch (tEvent.type)
		{
		case sf::Event::Closed:       // Window closed
			quit(StatusAppOK);
			break;
		case sf::Event::GainedFocus:  // Window gained focus
			state.resume();
			break;
		case sf::Event::LostFocus:    // Window lost focus
			state.pause();
			break;
		case sf::Event::Resized:      // Window resized
			mWindow.setSize(sf::Vector2u(800, 600));
			break;
		default:                      // Current active state will handle
			state.handleEvents(tEvent);
			//std::cout << "Default " << std::endl;
		}
	}
}

