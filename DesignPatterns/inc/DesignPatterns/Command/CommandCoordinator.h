#pragma once
#include <vector>
#include <memory>

class ICommand;

class CommandCoordinator
{
public:
	CommandCoordinator();
	void Perform(std::unique_ptr<ICommand> command);
	void Undo();
	void Redo();

private:
	std::vector<std::unique_ptr<ICommand>>	mCommand;
	unsigned int							mCommandTip;

	void RemoveCommandsBeyondCommandTip();
};
