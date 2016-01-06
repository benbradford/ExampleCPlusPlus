#pragma once
#include "IStackedState.h"
#include <stack>
#include <memory>

class StateStack
{
public:

	template <typename T, typename ... ARGS>
	void PushState(ARGS... args);
	void PopState();
	void UpdateState();
	void ClearStack();
	bool IsEmpty() const { return mStack.empty(); }
private:

	std::stack<std::unique_ptr<IStackedState>> mStack;
};

template <typename T, typename ... ARGS>
void StateStack::PushState(ARGS... args)
{
	if (mStack.empty() == false)
	{
		mStack.top()->OnInterrupt();
	}
	mStack.push(std::unique_ptr<IStackedState>(new T(args...)));
	mStack.top()->OnPush();
}