#pragma once
#include <map>

class IFlexibleObserver;

class FlexibleSubject
{
public:
	class ObserverHandle
	{
	public:
		ObserverHandle(int nextHandle);
		ObserverHandle(const ObserverHandle& other);
		bool operator==(const ObserverHandle& other) const;
		bool operator<(const ObserverHandle& other) const;
	private:
		ObserverHandle();
		const int handle;
	};

	FlexibleSubject();
	~FlexibleSubject();

	ObserverHandle  GenerateNewHandle();
	void			AddObserver(ObserverHandle handle, IFlexibleObserver& observer);
	bool			HasObserver(ObserverHandle handle) const;
	void			RemoveObserver(ObserverHandle handle);
	void			Notify();
private:
	std::map<ObserverHandle, IFlexibleObserver*> mObservers;
	int mNextHandle;

	bool			HasObserver(IFlexibleObserver& observer) const;

};


//////////////////////////////////////////////////////////////////////////
// This new version of the subject will allow users to unregister themselves mid use
// It also uses handles to store information on who is registered with it, this makes it more flexible since callers only need to have this handle, rather than the object itself
// We store the observers as raw pointers rather than shared pointers, meaning that clients are responsible for memory management and for ensuring that deleted objects are removed from this list
// See how the ConcreteFlexibleObserver guarantees that it is always an observer of a subject only for the duration of the observer's lifetime