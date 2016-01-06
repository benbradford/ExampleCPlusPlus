#pragma once

#include <map>
#include <memory>
#include <typeinfo>
#include <cassert>

class Component;

class Entity
{
public:
	Entity();
	~Entity();

	template <typename ComponentType, typename... ARGS>
	static ComponentType& CreateAndAddComponent(Entity& entity, ARGS... args);

	template <typename ComponentType>
	bool HasComponent() const;

	template <typename ComponentType>
	ComponentType& GetComponent() const;

	bool HasComponent(unsigned int componentType) const;
private:
	std::map < unsigned int, std::unique_ptr<Component>> mComponents;

	template <typename ComponentType>
	static unsigned int GetComponentType();
};

template <typename ComponentType>
inline unsigned int Entity::GetComponentType()
{
	return typeid(ComponentType).hash_code();
}

template <typename ComponentType>
inline bool Entity::HasComponent() const
{
	return mComponents.find(GetComponentType<ComponentType>()) != mComponents.end();
}

inline bool Entity::HasComponent(unsigned int componentType) const
{
	return mComponents.find(componentType) != mComponents.end();
}

template <typename ComponentType, typename... ARGS>
ComponentType& Entity::CreateAndAddComponent(Entity& entity, ARGS... args)
{
	ComponentType* component = new ComponentType(entity, args...);
	entity.mComponents[GetComponentType<ComponentType>()].reset(component);
	return static_cast<ComponentType&>(*component);
}

template <typename ComponentType>
inline ComponentType& Entity::GetComponent() const
{
	const unsigned int componentHandle = GetComponentType<ComponentType>();
	assert(HasComponent(componentHandle));
	auto result = mComponents.find(componentHandle);
	return static_cast<ComponentType&>(*result->second);
}
