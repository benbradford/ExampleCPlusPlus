#pragma once
#include "IWindow.h"

class MacWindow : public IWindow
{
public:
	void Maximise() override {}
	void Minimise() override {}
};