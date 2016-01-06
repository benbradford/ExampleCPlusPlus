#pragma once
#include <memory>

class IButton;
class IWindow;

class IAbstractGUIFactory
{
public:
	virtual ~IAbstractGUIFactory(){}

	virtual std::unique_ptr<IButton> CreateButton() const = 0;
	virtual std::unique_ptr<IWindow> CreateWindow() const = 0;
};