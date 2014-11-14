#pragma once

#include "IManagedSingleton.h"
#include <memory>

template <class T>
class ManagedSingleton : public IManagedSingleton
{
public:
	static bool HasInstance() { return sInstance.lock() != nullptr; }
	static T& Instance() { return *sInstance.lock(); }
	static std::weak_ptr<T> WeakInstance() { return sInstance; }
	static const T& ConstInstance() { return *sInstance.lock(); }
	static std::weak_ptr<const T> ConstWeakInstance() { return sInstance; }

private:
	friend class SingletonManager;
	
	static std::shared_ptr<T> Initialise() { const std::shared_ptr<T> ret(new T); sInstance = ret; return ret; }

	static std::weak_ptr<T> sInstance;

};

template <typename T>
std::weak_ptr<T> ManagedSingleton<T>::sInstance;