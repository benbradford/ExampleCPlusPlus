#include "DesignPatterns/AbstractFactory/GuiApplication.h"
#include "DesignPatterns/AbstractFactory/IWindow.h"
#include "DesignPatterns/AbstractFactory/IButton.h"
#include "DesignPatterns/AbstractFactory/IAbstractGUIFactory.h"

GuiApplication::GuiApplication(const IAbstractGUIFactory& factory)
: mWindow(factory.CreateWindow())
, mButton1(factory.CreateButton())
, mButton2(factory.CreateButton())
{

}

