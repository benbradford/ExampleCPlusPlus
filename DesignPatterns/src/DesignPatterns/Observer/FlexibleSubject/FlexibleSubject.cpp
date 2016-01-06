#include "DesignPatterns/Observer/FlexibleSubject/FlexibleSubject.h"
#include "DesignPatterns/Observer/IObserver.h"
#include <assert.h>
#include "DesignPatterns/Observer/FlexibleSubject/IFlexibleObserver.h"



FlexibleSubject::ObserverHandle::ObserverHandle(int nextHandle)
: handle(nextHandle)
{

}

FlexibleSubject::ObserverHandle::ObserverHandle(const ObserverHandle& other)
: handle(other.handle)
{

}

bool FlexibleSubject::ObserverHandle::operator==(const ObserverHandle& other) const
{
	return handle == other.handle;
}

bool FlexibleSubject::ObserverHandle::operator<(const ObserverHandle& other) const
{
	return handle < other.handle;
}


FlexibleSubject::FlexibleSubject()
: mNextHandle(0)
{

}

FlexibleSubject::~FlexibleSubject()
{

}

FlexibleSubject::ObserverHandle  FlexibleSubject::GenerateNewHandle()
{
	ObserverHandle handle(mNextHandle++);
	mObservers[handle] = nullptr;
	return handle;
}

void FlexibleSubject::AddObserver(ObserverHandle handle, IFlexibleObserver& observer)
{
	assert(HasObserver(observer) == false);
	assert(HasObserver(handle) == true);
	assert(mObservers[handle] == nullptr);
	
	mObservers[handle] = &observer;
	
}

bool FlexibleSubject::HasObserver(ObserverHandle handle) const
{
	return mObservers.find(handle) != mObservers.end();
}

bool FlexibleSubject::HasObserver(IFlexibleObserver& observer) const
{
	const auto end = mObservers.end();
	for (auto it = mObservers.begin(); it != end; ++it)
	{
		if (it->second == &observer)
			return true;
	}
	return false;
}

void FlexibleSubject::RemoveObserver(ObserverHandle handle)
{
	assert(HasObserver(handle));
	mObservers.erase(handle);
}

void FlexibleSubject::Notify()
{
	auto copyOfMap = mObservers;
	const auto end = copyOfMap.end();
	for (auto it = copyOfMap.begin(); it != end; ++it)
	{
		assert(it->second);
		it->second->Notify(*this);
	}
}