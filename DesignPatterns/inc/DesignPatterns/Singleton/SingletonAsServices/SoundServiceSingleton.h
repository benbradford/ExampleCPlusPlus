#pragma once

#include "ISoundServiceSingleton.h"

class SoundServiceSingleton : public ISoundServiceSingleton
{
public:
	void PlaySound() override{}
	bool IsSoundPlaying() const override { return mIsSoundPlaying; }
private:
	bool		mIsSoundPlaying;
	
	friend class SingletonServiceManager;
	SoundServiceSingleton();
	
};


// This version highlights how singletons can be both managed in terms of memory and lifetime, and how access to them can be controlled
// The SingletonServiceManager becomes our central point for all singletons, both in terms of their storage and their access
// Note that a possible extension to this service idea is to only generate the service when it is first used, rather than when it is registered, this idea is not implemented here
//
// FAQ
// What are the ... template arguments for?
//		These are variadic template arguments. This allows clients to specify and unspecified number of arguments of an unspecified type
//		This is useful for forwarding on arguments to a templated type that already expects to receive those arguments in one of its functions, in this case the constructor for ExtendedSoundServiceSingleton
//
// Why are unique pointers used?
//		This guarantees that the pointer for each singleton can only exist in one place and that once that has gone, the object is destroyed
//		We return only references to this object, so memory ownership is never transferred
//		The client would be responsible for ensuring that whilst holding on to a reference, that something doesn't happen to make the
//		singleton it references become destroyed (i.e. ensure the singleton isn't removed from the SingletonServiceManager or the SingletonServiceManager is not destroyed)
//
// Why do clients need to specify both a base type and an instantiation type?
//		This allows clients to vary the concrete instance that is instantiated for a particular registered base type
//		When clients resolve to obtain a particular SingletonService, it shouldn't have to case about the particular concrete type of that SingletonService, it just needs
//		to resolve the abstract type to receive the actual concrete type that has been registered with the SingletonServiceManager
//
// Why is there a need for casting in SingletonServiceManager when resolving types?
//		In this particular implementation, The SoundServiceManager holds a map to all singleton objects, since the unique_ptr needs to refer to a particular type
//		We use the simple base class of IServiceSingleton, so the SoundServiceManager has an abstract type to store in its map. As a consequence of this, the manager
//		is required to cast this IServiceSingleton interface to be the type that the client cares about in the Resolve call.