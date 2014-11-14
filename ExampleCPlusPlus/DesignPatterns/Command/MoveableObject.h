#pragma once

class MoveableObject
{
public:
	MoveableObject(int posX, int posY)
		: mPositionX(posX)
		, mPositionY(posY)
	{}

	MoveableObject()
		: mPositionX(0)
		, mPositionY(0)
	{}

	int GetCurrentX() const { return mPositionX; }
	int GetCurrentY() const { return mPositionY; }
	void MoveTo(int destX, int destY) { mPositionX = destX; mPositionY = destY; };
private:

	int mPositionX;
	int mPositionY;
};