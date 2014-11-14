#include "basicstatemachine.h"
#include "IBasicState.h"

void BasicStateMachine::UpdateState()
{
	if (mCurrentState.get())
		mCurrentState->UpdateState();
}