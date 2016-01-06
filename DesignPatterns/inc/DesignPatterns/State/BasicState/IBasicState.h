#pragma once

class IBasicState
{
public:
	virtual ~IBasicState(){}

	virtual void EnterState() = 0;
	virtual void UpdateState() = 0;
	virtual void ExitState() = 0;
};