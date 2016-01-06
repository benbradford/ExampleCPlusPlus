#include "CommandCoordinator.h"
#include "ICommand.h"

CommandCoordinator::CommandCoordinator()
: mCommandTip(0)
{

}

void CommandCoordinator::Perform(std::unique_ptr<ICommand> command)
{
	RemoveCommandsBeyondCommandTip();

	command->Perform();
	mCommand.push_back(std::move(command));
	mCommandTip = mCommand.size();
}

void CommandCoordinator::Undo()
{
	if (mCommandTip > 0)
	{
		mCommand[mCommandTip - 1]->Undo();
		--mCommandTip;
	}
	
}

void CommandCoordinator::Redo()
{
	if (mCommandTip < mCommand.size())
	{

		mCommand[mCommandTip]->Perform();
		++mCommandTip;
	}
}

void CommandCoordinator::RemoveCommandsBeyondCommandTip()
{
	while (mCommandTip < mCommand.size())
	{
		mCommand.pop_back();
	}
}