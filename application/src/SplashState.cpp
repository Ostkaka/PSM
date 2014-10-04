#include "SplashState.hpp"
#include <core/IApp.hpp>

SplashState::SplashState(psm::IApp& app, float splashDuration) :
psm::IState("Splash", app),
mSplashDuration(splashDuration)
{
}

SplashState::~SplashState()
{
}

void SplashState::init()
{
	IState::init();	
}

void SplashState::reset()
{
	//Nothing
}

void SplashState::handleEvents(sf::Event tEvent)
{

}

void SplashState::update(float elapsedTime)
{	
	if (false == isPaused() && getElapsedTime() > mSplashDuration)
	{
		mApp.mStateManager.removeActiveState();
	}
}

void SplashState::draw()
{
	mApp.mWindow.draw(mSpalshScreenSprite);
}

void SplashState::handleCleanup()
{

}


