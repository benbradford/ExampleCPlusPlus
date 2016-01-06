#pragma once

#include "ManagedSingleton.h"

class AdvancedSoundSingleton : public ManagedSingleton<AdvancedSoundSingleton>
{
public:

	void PlaySound();
	bool IsSoundPlaying() const;
private:

	bool mIsPlaying;

	friend ManagedSingleton<AdvancedSoundSingleton>;
	AdvancedSoundSingleton();

};


// This version of singleton now satisfies our want to have an explicit owner for the memory and lifetime of a singleton
// Memory and lifetime is now dictated by the SingletonManager. Destroying this object also destroys the singleton
// Since the ManagedSingletons only have a weak reference to themselves, they not only have a reference to themselves, but they also know when they have been deleted
// For projects where there could be uncertainty as to whether or not the SingletonManager has ever instantiated, or if it had instantiated and has since been deleted, the ManagedSingletons can be queried to see if they are still alive before attempting to use them
// Another advantage over the basic singleton is that since the singleton is stored as a static member, we can address it through both a regular accessor function or a const version
// 
// Visualising the solution:
//													0.*
//                                 IManagedSingleton--------<> SingletonManager
//										  .
//                                       /_\
//										  |
//										  |
//                                  ManagedSingleton 
//										  .
//										 /_\
//										  |
//										  |
//								 AdvancedSoundSingleton
//
// FAQ
//
// Why do we even need an IManagedSingleton?
//		The answer to this is in the fact that SingletonManager needs to know about the singletons it is managing. 
//		This obviously needs to be an abstract type that is a parent to all Singletons, 
//		so why not just do away with IManagedSingleton and simply have ManagedSingleton as the base class?
//      Well this is because ManagedSingleton is a templated class and you cannot store containers 
//		to templated types because there is no way of knowing the storage size of a templated class
//
// Why is ManagedSingleton a template class?
//      AdvancedSoundsSingleton inherits from ManagedSingleton yet passes itself as a template parameter.
//		At first glance this might seem odd, but it is fairly common practice. It allows the inherited class
//      to know something about the concrete classes underneath it in the hierarchy, without breaking any abstraction
//		In the case of the SingletonManager, notice that it contains a static weak pointer to the T
//		In order for our static accessor functions to be able to return the managed singleton to the exact
//		type of the singleton (rather than an abstract version of it) we need to know something about the
//		concrete singleton to be able to provide a suitable access function to it. Note that the getter 
//		functions at the top of ManagedSingleton all return type T. This is the concrete version of this class
//		and it simply returns its static member variable of sInstance. Without knowing this information about
//		the class, the client would be required to do some casting each time called a getter function.
//
// What is with the friend classes?
//		Friend classes are often looked at as undesirable in c++ since it breaks encapsulation. 
//		However, in this particular instance, we would have to make the singleton constructor public
//		and the singleton initialise function public too, making it accessible to everyone and
//		defeating the point of a singleton. Therefore opening up only the manager to be able to
//		initialise singletons and making the initialise private, prevents this. This is similar
//		to the AdvancedSoundSingleton declaring a private ctor and a friend in the base class,
//		we only ever want the base class to initiate the class since this already guarantees us that
//		only one instance can be created
//
// How can we control singletons so that they are not globally accessible?
//		This is moving closer to a service system, where one designated Service class is the only
//		route to accessing functions. This is described in the SingletonsAsServices section of this project