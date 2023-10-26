#pragma once
#include "../Component/ComponentContainer.h"
#include <memory>

class Object
	: public std::enable_shared_from_this<Object>,
	public ComponentContainer
{
private:
	using Container = ComponentContainer;
public:
	using ComponentPtr = Container::ComponentPtr;
	using Handle = Container::Handle;
public:
	Object() = default;

	template<ComponentType T>
	Handle AddComponent()
	{
		return Container::AddComponent<T>(weak_from_this());
	}

	bool HasComponent(const Handle& handle) const
	{
		return Container::HasComponent(weak_from_this(), handle);
	}

	template<ComponentType T>
	std::weak_ptr<T> GetComponent(const Handle& handle) const
	{
		return Container::GetComponent<T>(weak_from_this(), handle);
	}

	virtual ~Object() = default;
};
