#include "AdvancedSoundSingleton.h"

AdvancedSoundSingleton::AdvancedSoundSingleton()
: mIsPlaying(false)
{

}

void AdvancedSoundSingleton::PlaySound()
{
	// ...
}

bool AdvancedSoundSingleton::IsSoundPlaying() const
{
	return mIsPlaying;
}