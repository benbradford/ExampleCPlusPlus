#pragma once

class ICommand
{
public:
	virtual ~ICommand(){}
	virtual void Perform() = 0;
	virtual void Undo() = 0;
};