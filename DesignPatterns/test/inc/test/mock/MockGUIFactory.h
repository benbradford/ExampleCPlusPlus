#pragma once

#include "test/TestCommon.h"
#include "DesignPatterns/AbstractFactory/IAbstractGUIFactory.h"
#include "DesignPatterns/AbstractFactory/IButton.h"
#include "DesignPatterns/AbstractFactory/IWindow.h"

class MockGUIFactory : public IAbstractGUIFactory
{
public:
	MOCK_CONST_METHOD0(CreateButton_Proxy, IButton* ());
	MOCK_CONST_METHOD0(CreateWindow_Proxy, IWindow* ());

	std::unique_ptr<IButton> CreateButton() const override { return std::unique_ptr<IButton>(CreateButton_Proxy()); };
	std::unique_ptr<IWindow> CreateWindow() const override { return std::unique_ptr<IWindow>(CreateWindow_Proxy()); };	
};
