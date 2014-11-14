#pragma once

#include "MacButton.h"
#include "MacWindow.h"
#include "IAbstractGUIFactory.h"

class MacGUIFactory : public IAbstractGUIFactory
{
public:
	std::unique_ptr<IButton> CreateButton() const override { return std::unique_ptr<IButton>(new MacButton); }
	std::unique_ptr<IWindow> CreateWindow() const override { return std::unique_ptr<IWindow>(new MacWindow); }
};