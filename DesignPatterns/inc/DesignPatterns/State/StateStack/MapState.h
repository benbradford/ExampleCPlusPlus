#pragma once

#include "IStackedState.h"

class MapState : public IStackedState
{
public:
	void OnPush() override {}
	void OnPop() override {}
	void OnInterrupt() override {}
	void OnResume() override {}
	void OnUpdate() override {}

};