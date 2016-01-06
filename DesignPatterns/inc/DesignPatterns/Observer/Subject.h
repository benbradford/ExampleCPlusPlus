#pragma once
#include <vector>
#include <memory>

class IObserver;

class Subject
{
public:
	Subject();
	~Subject();
	void AddObserver(const std::shared_ptr<IObserver>& observer);
	bool HasObserver(const std::shared_ptr<IObserver>& observer) const;
	void RemoveObserver(const std::shared_ptr<IObserver>& observer);
	void Notify();
private:
	std::vector<std::shared_ptr<IObserver>> mObservers;

	bool mIsNotifying = false;

};


//////////////////////////////////////////////////////////////////////////
// Simple subject / observer
//
// Note that this solution might be restrictive for two reasons:
// 1. They required that you add a shared_ptr, this means that it is hard for objects to add and remove themselves as an observer
// 2. The code will crash if someone attempts to Add or Remove Observers during a Notify() since we are already iterating on the vector during this time
//    In debug, this will be captured by an assert, but there is nothing stopping this happening in release