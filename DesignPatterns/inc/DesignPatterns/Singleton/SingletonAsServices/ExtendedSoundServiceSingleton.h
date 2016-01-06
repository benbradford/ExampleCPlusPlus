#pragma once

#include "ISoundServiceSingleton.h"

class ExtendedSoundServiceSingleton : public ISoundServiceSingleton
{
public:

	void PlaySound() override {}
	bool IsSoundPlaying() const override { return false; }
private:
	friend class SingletonServiceManager;

	ExtendedSoundServiceSingleton(const char* path)
		: mPath(path)
	{

	}
	const char* mPath;

};