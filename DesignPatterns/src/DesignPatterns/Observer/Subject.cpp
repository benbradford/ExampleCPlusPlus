#include "Subject.h"
#include "IObserver.h"
#include <assert.h>

Subject::Subject()
{

}

Subject::~Subject()
{

}

void Subject::AddObserver(const std::shared_ptr<IObserver>& observer)
{
	assert(mIsNotifying == false);
	assert(HasObserver(observer) == false);
	
	mObservers.push_back(observer);
	
	assert(HasObserver(observer) == true);
}

bool Subject::HasObserver(const std::shared_ptr<IObserver>& observer) const
{
	for (const std::shared_ptr<IObserver>& containedObserver : mObservers)
	{
		if (containedObserver.get() == observer.get())
			return true;
	}
	return false;
}

void Subject::RemoveObserver(const std::shared_ptr<IObserver>& observer)
{
	assert(mIsNotifying == false);
	assert(HasObserver(observer));
	
	const auto end = mObservers.end();
	for (auto it = mObservers.begin(); it != end; ++it)
	{
		if ((*it).get() == observer.get())
		{
			mObservers.erase(it);
			return;
		}
	}
	
	assert(false);
}

void Subject::Notify()
{

#ifdef _DEBUG
	mIsNotifying = true;
#endif

	for (const std::shared_ptr<IObserver>& containedObserver : mObservers)
	{
		containedObserver->Notify(*this);
	}

#ifdef _DEBUG
	mIsNotifying = false;
#endif

}