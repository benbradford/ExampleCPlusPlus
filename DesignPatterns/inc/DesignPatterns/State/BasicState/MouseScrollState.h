#pragma  once
#include "IBasicState.h"

class MouseScrollState : public IBasicState
{
public:
	MouseScrollState(){}

	void EnterState() override {}
	void UpdateState() override {}
	void ExitState() override {}
};