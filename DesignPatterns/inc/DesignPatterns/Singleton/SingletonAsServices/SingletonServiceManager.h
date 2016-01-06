#pragma once

#include "IServiceSingleton.h"
#include <map>
#include <memory>
#include <cassert>

class SingletonServiceManager
{
public:
	typedef unsigned int SingletonServiceId;

	SingletonServiceManager(const SingletonServiceManager&) = delete;
	SingletonServiceManager& operator=(const SingletonServiceManager&) = delete;
	SingletonServiceManager(SingletonServiceManager&&) = delete;

	SingletonServiceManager();
	~SingletonServiceManager();

	template <typename BaseType, typename InstanceType>
	void AddSingletonService();

	template <typename BaseType, typename InstanceType, typename ARG, typename ...ARGS>
	void AddSingletonService(ARG argument, ARGS... arguments);

	template <typename BaseType>
	bool RemoveSingleton();

	template <typename BaseType>
	bool GetDoesSingletonExist() const;

	template <typename BaseType>
	BaseType& Resolve();

	template <typename BaseType>
	const BaseType& Resolve() const;
private:
	
	template <typename BaseType>
	static SingletonServiceId GetSingletonServiceId()
	{
		return typeid(BaseType).hash_code();
	}

	std::map<SingletonServiceId, std::unique_ptr<IServiceSingleton>>	mSingletonServices;
};

template <typename BaseType, typename InstanceType>
inline void SingletonServiceManager::AddSingletonService()
{
	if (GetDoesSingletonExist<BaseType>())
	{
		assert(false);
		// :TODO: handle error
	}
	mSingletonServices[GetSingletonServiceId<BaseType>()].reset(new InstanceType);
}


template <typename BaseType, typename InstanceType, typename ARG, typename ...ARGS>
inline void SingletonServiceManager::AddSingletonService(ARG argument, ARGS... arguments)
{
	if (GetDoesSingletonExist<BaseType>())
	{
		assert(false);
		// :TODO: handle error
	}
	mSingletonServices[GetSingletonServiceId<BaseType>()] = std::unique_ptr<BaseType>(new InstanceType(argument, arguments...));
}

template <typename BaseType>
inline bool SingletonServiceManager::RemoveSingleton()
{
	if (GetDoesSingletonExist<BaseType>() == false)
	{
		return false;
	}
	mSingletonServices.erase(GetSingletonServiceId<BaseType>());
	return true;
}

template <typename BaseType>
bool SingletonServiceManager::GetDoesSingletonExist() const
{
	return mSingletonServices.find(GetSingletonServiceId<BaseType>()) != mSingletonServices.end();
}

template <typename BaseType>
inline BaseType& SingletonServiceManager::Resolve()
{
	if (GetDoesSingletonExist<BaseType>() == false)
	{
		assert(false);
		// :TODO: handle error
	}
	return static_cast<BaseType&>(*mSingletonServices[GetSingletonServiceId<BaseType>()]);
}

template <typename BaseType>
inline const BaseType& SingletonServiceManager::Resolve() const
{
	if (GetDoesSingletonExist<BaseType>() == false)
	{
		assert(false);
		// :TODO: handle error
	}

	return static_cast<const BaseType>(*mSingletonServices.find(GetSingletonServiceId<BaseType>())->second);
}
