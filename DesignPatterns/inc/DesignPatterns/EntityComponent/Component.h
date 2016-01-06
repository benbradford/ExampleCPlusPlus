#pragma once

class Entity;

class Component
{
public:

protected:
	template <typename... RequiredComponents>
	Component(Entity& entity)
		: mEntity(entity)
	{

	}

	Entity& GetEntity() const { return mEntity; }

private:
	Entity& mEntity;
};

