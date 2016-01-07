#pragma once

#include <memory>

class IAbstractGUIFactory;
class IWindow;
class IButton;

class GuiApplication
{
public:
	GuiApplication(const IAbstractGUIFactory& factory);

	IWindow& GetMainWindow() const { return *mWindow; }
	IButton& GetButton1() const { return *mButton1; }
	IButton& GetButton2() const { return *mButton2; }
private:
	const std::unique_ptr<IWindow> mWindow;
	const std::unique_ptr<IButton> mButton1;
	const std::unique_ptr<IButton> mButton2;
};


// In order to allow clients to decide what objects should be created, an abstract factory is passed to this gui application in order to create objects that make sense for the platform being run
// Our abstract factory returns unique_ptrs to widgets and thus the assumption is that whoever calls the create functions will become that object's owner
// The class diagram for this can be visualised thus:
//
//				     IWindow---------------------<>GuiApplication<>----------------------------IButton
//					    /\								|										  /\
//						||							  <uses>									  ||
//			---------------------------				IGuiFactory						-------------------------------
//          |						  |					/\							|							  |
//     WindowsWindow			 MacWindow				||						WindowsButton				 MacButton
//													    ||
//													    ||
//											-------------------------
//											|						|
//											|						|
//									WindowsGuiFactory		  MacGuiFactory
//
