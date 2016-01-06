#pragma once

class BasicSoundSingleton
{
public:

	static BasicSoundSingleton& GetInstance();

	void PlaySound();
	bool IsSoundPlaying() const;
private:
	BasicSoundSingleton();
	~BasicSoundSingleton();

	bool mIsSoundPlaying;
};


// Notes
// This is a very simple implementation of a singleton. It makes use of c++s ability to have static local variables to return a single instance to the class
// The problem with this solution is that the singleton has no owner as such, and no controller way to decide when to allocate and deallocate its memory and no option but to store the class in static storage, which may not be desirable
// Another problem is that this creates a readily available global variable, which should not be desirable in any software project!