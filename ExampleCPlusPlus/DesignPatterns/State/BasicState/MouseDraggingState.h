#pragma once
#include "IBasicState.h"

class MouseDraggingState : public IBasicState
{
public:
	MouseDraggingState(){}

	void EnterState() override {}
	void UpdateState() override {}
	void ExitState() override {}
};