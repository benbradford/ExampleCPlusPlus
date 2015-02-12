#pragma once

class Subject;

class IObserver
{
public:
	virtual ~IObserver(){}

	virtual void Notify(const Subject& subject) = 0;
};