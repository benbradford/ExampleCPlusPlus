#pragma once

#include "ManagedSingleton.h"
#include <map>
#include <memory>
#include <cassert>

class SingletonManager
{
public:

	typedef unsigned int SingletonNameHash;

	template <typename T>
	void AddSingleton()
	{
		const auto hash = GetHash<T>();
		const auto entry = mSingletons.find(hash);
		assert(entry == mSingletons.end());
		if (entry != mSingletons.end())
		{
			// :TODO: handle error
			return;
		}
		mSingletons.insert(std::make_pair(hash, ManagedSingleton<T>::Initialise()));
	}

private:

	template <typename T>
	static SingletonNameHash GetHash()
	{
		return typeid(T).hash_code();
	}

	std::map<SingletonNameHash, std::shared_ptr<IManagedSingleton>> mSingletons;
};