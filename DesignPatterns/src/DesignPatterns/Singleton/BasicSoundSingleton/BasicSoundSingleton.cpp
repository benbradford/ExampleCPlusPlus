#include "DesignPatterns/Singleton/BasicSoundSingleton/BasicSoundSingleton.h"

BasicSoundSingleton::BasicSoundSingleton()
: mIsSoundPlaying(false)
{

}

BasicSoundSingleton::~BasicSoundSingleton()
{

}

BasicSoundSingleton& BasicSoundSingleton::GetInstance()
{
	static BasicSoundSingleton singleton;
	return singleton;
}

void BasicSoundSingleton::PlaySound()
{
	// ...
}

bool BasicSoundSingleton::IsSoundPlaying() const
{
	return mIsSoundPlaying;
}