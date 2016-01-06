#include "GuiApplication.h"
#include "IWindow.h"
#include "IButton.h"
#include "IAbstractGUIFactory.h"

GuiApplication::GuiApplication(const IAbstractGUIFactory& factory)
: mWindow(factory.CreateWindow())
, mButton1(factory.CreateButton())
, mButton2(factory.CreateButton())
{

}

