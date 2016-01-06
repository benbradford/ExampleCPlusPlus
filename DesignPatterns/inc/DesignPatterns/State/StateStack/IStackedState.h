#pragma once

class IStackedState
{
public:
	virtual ~IStackedState(){}
	
	virtual void OnPush() = 0;
	virtual void OnPop() = 0;
	virtual void OnInterrupt() = 0;
	virtual void OnResume() = 0;
	virtual void OnUpdate() = 0;

};