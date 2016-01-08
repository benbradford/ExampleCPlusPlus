
#include "test/TestCommon.h"
#include "DesignPatterns/AbstractFactory/GuiApplication.h"
#include "DesignPatterns/AbstractFactory/IButton.h"
#include "DesignPatterns/AbstractFactory/IWindow.h"

#include "test/mock/MockGuiFactory.h"

class TestGuiApplication : public Test
{
protected:
	enum class WindowState
	{
		UNSET,
		MAXIMISED,
		MINIMISED
	};

	struct MockButton : public IButton
	{
		MockButton(unsigned int& buttonClick) : mClicks(buttonClick){}
		void Click() override{ ++mClicks;}

	private:
		unsigned int& mClicks;
	};
	
	struct MockWindow : public IWindow
	{
		MockWindow(WindowState& state) : mState(state){}
		void Maximise() override { mState = WindowState::MAXIMISED;}
		void Minimise() override { mState = WindowState::MINIMISED;}
	private:
		WindowState& mState;
	};

    std::unique_ptr<GuiApplication>	mApp;
    std::unique_ptr<MockGUIFactory> mFactory;
    
    unsigned int mButtonClicks = 0;
	WindowState	mWindowState = WindowState::UNSET;

public:

	virtual void SetUp() override
	{
	    mFactory.reset(new MockGUIFactory);
	    EXPECT_CALL(*mFactory, CreateWindow_Proxy()).WillOnce(Return(new MockWindow(mWindowState)));
	    EXPECT_CALL(*mFactory, CreateButton_Proxy()).WillOnce(Return(new MockButton(mButtonClicks))).WillOnce(Return(new MockButton(mButtonClicks)));

	    mApp.reset(new GuiApplication(*mFactory));

	}

protected:

};

TEST_F(TestGuiApplication, CanCreateGuiApplication)
{

}

TEST_F(TestGuiApplication, CanAlterWindowState)
{
	ASSERT_EQ(mWindowState, WindowState::UNSET);
	mApp->GetMainWindow().Maximise();
	ASSERT_EQ(mWindowState, WindowState::MAXIMISED);

	mApp->GetMainWindow().Minimise();
	ASSERT_EQ(mWindowState, WindowState::MINIMISED);
}

TEST_F(TestGuiApplication, CanClickButton1)
{
	ASSERT_EQ(mButtonClicks, 0);
	mApp->GetButton1().Click();
	ASSERT_EQ(mButtonClicks, 1);
}

TEST_F(TestGuiApplication, CanClickButton2)
{
	ASSERT_EQ(mButtonClicks, 0);
	mApp->GetButton2().Click();
	ASSERT_EQ(mButtonClicks, 1);
}

TEST_F(TestGuiApplication, CanClickButton1And2)
{
	ASSERT_EQ(mButtonClicks, 0);
	mApp->GetButton1().Click();
	mApp->GetButton2().Click();
	ASSERT_EQ(mButtonClicks, 2);
}
