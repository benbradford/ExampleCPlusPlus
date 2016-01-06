#pragma once
#include "IWindow.h"

class WindowsWindow : public IWindow
{
public:
	void Maximise() override {}
	void Minimise() override {}
};