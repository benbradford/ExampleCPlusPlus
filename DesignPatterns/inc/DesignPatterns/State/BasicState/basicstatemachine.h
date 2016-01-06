#pragma once
#include <memory>
#include "IBasicState.h"

class BasicStateMachine
{
public:
	BasicStateMachine(){}

	template <typename T, typename... ARGS>
	void SetState(ARGS... args);

	void UpdateState();

private:
	std::unique_ptr<IBasicState> mCurrentState;
};


template <typename T, typename... ARGS>
inline void BasicStateMachine::SetState(ARGS... args)
{
	if (mCurrentState.get())
		mCurrentState->ExitState();
	mCurrentState.reset(new T(args...));
	mCurrentState->EnterState();
}


//////////////////////////////////////////////////////////////////////////
// This is a simple solution to the State Machine pattern
// In this implementation, A simple state machine class can be updated with a current state
// Calling update will then update the new state
// The BasicStateMachine class is responsible for ownership of the state objects
//
// A slightly more practical use for states is games is to implement a state stack system, wherby clients can 
// either commence to a new state or go back to the previous state, this current state machine implementation has
// no memory of previous states. See StateStack for this implementation