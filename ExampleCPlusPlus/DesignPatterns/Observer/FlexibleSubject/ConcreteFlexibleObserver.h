#pragma once

#include "IFlexibleObserver.h"
#include "FlexibleSubject.h"

class ConcreteFlexibleObserver : public IFlexibleObserver
{
public:
	static ConcreteFlexibleObserver* Create(FlexibleSubject& subject);
	~ConcreteFlexibleObserver(); 
	
	void Notify(const FlexibleSubject&);
	
private:
	FlexibleSubject&						mSubject;
	const FlexibleSubject::ObserverHandle	mHandle;

	ConcreteFlexibleObserver(FlexibleSubject& subject, const FlexibleSubject::ObserverHandle& myHandle);
};


//////////////////////////////////////////////////////////////////////////
// A flexible observer will add and remove itself from the subject automatically