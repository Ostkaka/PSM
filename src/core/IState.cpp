/*
* This is the abstract IState class in MGE used as an interface
*/

#include <assert.h>
#include <core/IState.hpp>
#include <core/IApp.hpp>

namespace psm
{
	IState::IState(const typeStateID stateID, IApp& theApp) :
		mApp(theApp),
		mStateID(stateID),
		mInit(false),
		mPaused(false),
		mCleanup(false),
		mElapsedTime(0.0f),
		mPausedTime(0.0f)
	{
	}

	IState::~IState()
	{
	}

	const typeStateID IState::getID(void) const
	{
		return mStateID;
	}

	void IState::init(void)
	{
		// If Cleanup hasn't been called yet, call it now!
		if(true == mCleanup)
		{
			handleCleanup();
		}

		// Initialize if necessary
		if(false == mInit)
		{
			mInit = true;
			mPaused = false;
			mElapsedTime = 0.0f;
			mElapsedClock.restart();
			mPausedTime = 0.0f;
			mPausedClock.restart();
		}
	}

	void IState::deInit()
	{

		if(true == mInit)
		{
			mCleanup = true;
			mInit = false;
			mElapsedTime += mElapsedClock.getElapsedTime().asSeconds();
			if(true == mPaused)
			{
				mPausedTime += mPausedClock.getElapsedTime().asSeconds();
			}
		}
	}

	bool IState::isInitComplete()
	{
		return mInit;
	}

	bool IState::isPaused()
	{
		return mPaused;
	}

	void IState::pause()
	{
		if(false == mPaused)
		{
			mPaused = true;
			mPausedClock.restart();
		}
	}

	void IState::resume()
	{
		if(true == mPaused)
		{
			mPaused = false;
			mPausedTime += mPausedClock.getElapsedTime().asSeconds();
		}
	}

	void IState::handleEvents(sf::Event theEvent)
	{
		// Exit program if Escape key is pressed
		if((theEvent.type == sf::Event::KeyReleased) && (theEvent.key.code == sf::Keyboard::Escape))
		{
			// Signal the application to exit
			mApp.quit(StatusAppOK);
		}
	}

	float IState::getElapsedTime() const
	{
			float result = mElapsedClock.getElapsedTime().asSeconds();

			if(false == mInit)
			{
				result = mElapsedTime;
			}

			return result;
	}
	
	void IState::cleanup()
	{
		// This will be true if this IState is about to be deleted soon
		if(true == mCleanup)
		{
			// Call our handle cleanup virtual method
			handleCleanup();

			// Clear our cleanup flag
			mCleanup = false;
		}
	}
} 
