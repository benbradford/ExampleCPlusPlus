#include "DesignPatterns/Observer/FlexibleSubject/ConcreteFlexibleObserver.h"

ConcreteFlexibleObserver*ConcreteFlexibleObserver::Create(FlexibleSubject& subject)
{
	FlexibleSubject::ObserverHandle handle = subject.GenerateNewHandle();
	ConcreteFlexibleObserver* observer = new ConcreteFlexibleObserver(subject, handle);
	subject.AddObserver(handle, *observer);
	return observer;
}

void ConcreteFlexibleObserver::Notify(const FlexibleSubject&)
{

}

ConcreteFlexibleObserver::~ConcreteFlexibleObserver()
{
	mSubject.RemoveObserver(mHandle);
}

ConcreteFlexibleObserver::ConcreteFlexibleObserver(FlexibleSubject& subject, const FlexibleSubject::ObserverHandle& myHandle)
: mSubject(subject)
, mHandle(myHandle)
{

}