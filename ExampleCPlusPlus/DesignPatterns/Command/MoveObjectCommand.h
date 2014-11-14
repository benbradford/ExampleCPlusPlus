#pragma once
#include "ICommand.h"
#include "MoveableObject.h"

class MoveObjectCommand : public ICommand
{
public:
	MoveObjectCommand(MoveableObject& object, int destX, int destY)
		: mObject(object)
		, mStartX(object.GetCurrentX())
		, mStartY(object.GetCurrentY())
		, mDestX(destX)
		, mDestY(destY)
	{}

	void Perform() override
	{
		mObject.MoveTo(mDestX, mDestY);
	}
	void Undo() override
	{
		mObject.MoveTo(mStartX, mStartY);
	}

private:
	MoveableObject& mObject;
	const int		mStartX;
	const int		mStartY;
	const int		mDestX;
	const int		mDestY;
};