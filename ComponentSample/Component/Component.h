#pragma once
#include <type_traits>
#include <concepts>
#include <memory>
#include "../RuntimeTypeUniqueID.h"

class Object;
class ComponentContainer;

class Component
{
public:
	using TypeUniqueID = RuntimeTypeUniqueID::Value;

public:
	Component() = default;

	virtual void Update();

	virtual ~Component() = default;
protected:
	const std::weak_ptr<Object>& GetOwner() const;
private:
	std::weak_ptr<Object> mOwner;
private:
	friend ComponentContainer;
	void SetComponentInfo(const std::weak_ptr<Object>& owner);
};

template<class T>
concept ComponentType = std::is_same_v<Component, T> || (std::is_base_of_v<Component, T> && std::constructible_from<T>);
