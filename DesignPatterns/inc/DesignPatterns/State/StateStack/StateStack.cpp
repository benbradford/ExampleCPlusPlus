#include "StateStack.h"

void StateStack::PopState()
{
	if (mStack.empty())
		return;
	mStack.top()->OnPop();
	mStack.pop();
	if (mStack.empty() == false)
		mStack.top()->OnResume();
}

void StateStack::UpdateState()
{
	if (mStack.empty() == false)
		mStack.top()->OnUpdate();

}

void StateStack::ClearStack()
{
	while (mStack.empty() == false)
	{
		mStack.top()->OnPop();
		mStack.pop();
	}
}