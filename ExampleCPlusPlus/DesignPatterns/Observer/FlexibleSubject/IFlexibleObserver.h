#pragma once

class FlexibleSubject;

class IFlexibleObserver
{
public:
	virtual ~IFlexibleObserver(){}
	virtual void Notify(const FlexibleSubject& flexibleSubject) = 0;
};