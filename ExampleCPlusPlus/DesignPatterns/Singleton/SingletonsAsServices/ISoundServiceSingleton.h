#pragma once
#include "IServiceSingleton.h"

class ISoundServiceSingleton : public IServiceSingleton
{
public:
	virtual ~ISoundServiceSingleton(){}

	virtual void PlaySound() = 0;
	virtual bool IsSoundPlaying() const = 0;
};