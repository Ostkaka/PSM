/**
* StateManager class 
**/

#include <assert.h>
#include <stddef.h>
#include <core/StateManager.hpp>
#include <core/IApp.hpp>
#include <core/IState.hpp>

namespace psm
{
	StateManager::StateManager() :
	mApp(nullptr)
	{		
	}

	StateManager::~StateManager()
	{		
		// Drop all active states
		while(!mStack.empty())
		{
			// Retrieve the currently active state
			IState* anState = mStack.back();

			// Pop the currently active state off the stack
			mStack.pop_back();

			// Pause the currently active state
			anState->pause();

			// De-initialize the state
			anState->deInit();

			// Handle the cleanup before we pop it off the stack
			anState->cleanup();

			// Just delete the state now
			delete anState;

			// Clear pointer
			anState = nullptr;
		}

		// Delete all our dropped states
		while(!mDead.empty())
		{
			// Retrieve the currently active state
			IState* anState = mDead.back();

			// Pop the currently active state off the stack
			mDead.pop_back();

			// Pause the currently active state
			anState->pause();

			// De-initialize the state
			anState->deInit();

			// Handle the cleanup before we pop it off the stack
			anState->cleanup();

			// Just delete the state now
			delete anState;

			// Clear pointer
			anState = nullptr;
		}

		// Clear pointers 
		mApp = nullptr;
	}

	void StateManager::registerApp(IApp* app)
	{
		// Check that our pointer is good
		assert(nullptr != app && "StateManager::registerApp() theApp pointer is bad");

		// Make a note of the pointer
		assert(nullptr == mApp && "StateManager::registerApp() theApp pointer already registered");
		mApp = app;
	}

	bool StateManager::isEmpty()
	{
		return mStack.empty();
	}

	void StateManager::addActiveState(IState* state)
	{
		// Check that they didn't provide a bad pointer
		assert(nullptr != state && "StateManager::addActiveState() received a bad pointer");
		
		// Is there a state currently running? then Pause it
		if(!mStack.empty())
		{
			// Pause the currently running state since we are changing the
			// currently active state to the one provided
			mStack.back()->pause();
		}

		// Add the active state
		mStack.push_back(state);

		// Initialize the new active state
		mStack.back()->init();
	}

	void StateManager::addInactiveState(IState* state)
	{
		// Check that they didn't provide a bad pointer
		assert(nullptr != state && "StateManager::addInactiveState() received bad pointer");
		
		// Add the inactive state to the bottom of the stack
		mStack.insert(mStack.begin(), state);
	}

	IState& StateManager::getActiveState()
	{
		return *mStack.back();
	}

	void StateManager::inactivateActivateState()
	{
		// Is there no currently active state to drop?
		if(!mStack.empty())
		{
			// Retrieve the currently active state
			IState* state = mStack.back();
			
			// Pause the currently active state
			state->pause();

			// Pop the currently active state off the stack
			mStack.pop_back();

			// Move this now inactive state to the absolute back of our stack
			mStack.insert(mStack.begin(), state);

			// Don't keep pointers around we don't need anymore
			state = nullptr;
		}
		else
		{
			// Quit the application with an error status response
			if(nullptr != mApp)
			{
				mApp->quit(StatusAppStackEmpty);
			}
			return;
		}

		// Is there another state to activate? then call Resume to activate it
		if(!mStack.empty())
		{
			// Has this state ever been initialized?
			if(mStack.back()->isInitComplete())
			{
				// Resume the new active state
				mStack.back()->resume();
			}
			else
			{
				// Initialize the new active state
				mStack.back()->init();
			}
		}
		else
		{
			// There are no states on the stack, exit the program
			if(nullptr != mApp)
			{
				mApp->quit(StatusAppOK);
			}
		}
	}

	void StateManager::dropActiveState(void)
	{
		// Is there no currently active state to drop?
		if(!mStack.empty())
		{
			// Retrieve the currently active state
			IState* state = mStack.back();
	
			// Pause the currently active state
			state->pause();

			// Deinit currently active state before we pop it off the stack
			// (HandleCleanup() will be called by IState::DoInit() method if this
			// state is ever set active again)
			state->deInit();

			// Pop the currently active state off the stack
			mStack.pop_back();

			// Move this now inactive state to the absolute back of our stack
			mStack.insert(mStack.begin(), state);

			// Don't keep pointers around we don't need anymore
			state = nullptr;
		}
		else
		{
			// Quit the application with an error status response
			if(nullptr != mApp)
			{
				mApp->quit(StatusAppStackEmpty);
			}
			return;
		}

		// Is there another state to activate? then call Resume to activate it
		if(!mStack.empty())
		{
			// Has this state ever been initialized?
			if(mStack.back()->isInitComplete())
			{
				// Resume the new active state
				mStack.back()->resume();
			}
			else
			{
				// Initialize the new active state
				mStack.back()->init();
			}
		}
		else
		{
			// There are no states on the stack, exit the program
			if(nullptr != mApp)
			{
				mApp->quit(StatusAppOK);
			}
		}
	}

	void StateManager::resetActiveState()
	{
		// Is there no currently active state to reset?
		if(!mStack.empty())
		{
			// Retrieve the currently active state
			IState* anState = mStack.back();

			// Pause the currently active state
			anState->pause();

			// Call the ReInit method to Reset the currently active state
			anState->reset();

			// Resume the currently active state
			anState->resume();

			// Don't keep pointers around we don't need anymore
			anState = nullptr;
		}
		else
		{
			// Quit the application with an error status response
			if(nullptr != mApp)
			{
				mApp->quit(StatusAppStackEmpty);
			}
			return;
		}
	}

	void StateManager::removeActiveState(void)
	{
		// Is there no currently active state to drop?
		if(!mStack.empty())
		{
			// Retrieve the currently active state
			IState* anState = mStack.back();
	
			// Pause the currently active state
			anState->pause();

			// Deinitialize the currently active state before we pop it off the stack
			anState->deInit();

			// Pop the currently active state off the stack
			mStack.pop_back();

			// Move this state to our dropped stack
			mDead.push_back(anState);

			// Don't keep pointers around we don't need anymore
			anState = nullptr;
		}
		else
		{
			// Quit the application with an error status response
			if(nullptr != mApp)
			{
				mApp->quit(StatusAppStackEmpty);
			}
			return;
		}

		// Is there another state to activate? then call Resume to activate it
		if(!mStack.empty())
		{
			// Has this state ever been initialized?
			if(mStack.back()->isInitComplete())
			{
				// Resume the new active state
				mStack.back()->resume();
			}
			else
			{
				// Initialize the new active state
				mStack.back()->init();
			}
		}
		else
		{
			// There are no states on the stack, exit the program
			if(nullptr != mApp)
			{
				mApp->quit(StatusAppOK);
			}
		}
	}

	void StateManager::setActiveState(typeStateID theStateID)
	{
		std::vector<IState*>::iterator it;

		// Find the state that matches theStateID
		for(it=mStack.begin(); it < mStack.end(); it++)
		{
			// Does this state match theStateID? then activate it as the new
			// currently active state
			if((*it)->getID() == theStateID)
			{
				// Get a pointer to soon to be currently active state
				IState* anState = *it;
	
				// Erase it from the list of previously active states
				mStack.erase(it);

				// Is there a state currently running? then Pause it
				if(!mStack.empty())
				{
					// Pause the currently running state since we are changing the
					// currently active state to the one specified by theStateID
					mStack.back()->pause();
				}

				// Add the new active state
				mStack.push_back(anState);

				// Don't keep pointers we don't need around
				anState = nullptr;

				// Has this state ever been initialized?
				if(mStack.back()->isInitComplete())
				{
					// Resume the new active state
					mStack.back()->resume();
				}
				else
				{
					// Initialize the new active state
					mStack.back()->init();
				}

				// Exit our find loop
				break;
			}
		} 
	}

	void StateManager::cleanup()
	{
		// Always call our cleanup events with our pointer when this method is called
		//mCleanupEvents.DoEvents();

		// Remove one of our dead states
		if(!mDead.empty())
		{
			// Retrieve the dead state
			IState* anState = mDead.back();
			assert(nullptr != anState && "StateManager::HandleCleanup() invalid dropped state pointer");

			// Pop the dead state off the stack
			mDead.pop_back();

			// Call the DeInit if it hasn't been called yet
			if(anState->isInitComplete())
			{
				anState->deInit();
			}

			// Handle the cleanup before we delete anState
			anState->cleanup();

			// Just delete the state now
			delete anState;

			// Don't keep pointers around we don't need
			anState = nullptr;
		}

		// Make sure we still have an active state
		if(nullptr == mStack.back())
		{
			// There are no states on the stack, exit the program
			if(nullptr != mApp)
			{
				mApp->quit(StatusAppOK);
			}
		}
	}
}