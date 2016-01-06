#include "DesignPatterns/State/BasicState/BasicStateMachine.h"
#include "DesignPatterns/State/BasicState/IBasicState.h"

void BasicStateMachine::UpdateState()
{
	if (mCurrentState.get())
		mCurrentState->UpdateState();
}