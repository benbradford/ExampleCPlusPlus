#pragma once
#include "IAbstractGUIFactory.h"
#include "WindowsButton.h"
#include "WindowsWindow.h"

class PcGUIFactory : public IAbstractGUIFactory
{
public:

	virtual std::unique_ptr<IButton> CreateButton() const override { return std::unique_ptr<IButton>(new WindowsButton); }
	virtual std::unique_ptr<IWindow> CreateWindow() const override { return std::unique_ptr<IWindow>(new WindowsWindow); }
};