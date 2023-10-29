#pragma once
#include "../Component/ComponentContainer.h"
#include <memory>

template<class T>
concept ObjectType = std::is_same_v<Object, T> || (std::is_base_of_v<Object, T> && std::constructible_from<T>);

class Object
	: public std::enable_shared_from_this<Object>,
	public ComponentContainer
{
private:
	using TypeUniqueID = RuntimeTypeUniqueID::Value;
	using Container = ComponentContainer;
public:
	using ComponentPtr = Container::ComponentPtr;
	using Handle = Container::Handle;
public:
	Object() = default;

	template<ComponentType T>
	Handle AddComponent(const std::string& name)
	{
		return Container::AddComponent<T>(weak_from_this(), name);
	}

	virtual bool CheckUniqueID(TypeUniqueID typeUniqueID) const;

	TypeUniqueID GetTypeUniqueID() const;

	virtual ~Object() = default;
private:
	TypeUniqueID mTypeUniqueID{ (TypeUniqueID)-1 };
public:
	template<ObjectType T>
	static std::shared_ptr<T> Create()
	{
		std::shared_ptr<T> object = std::make_shared<T>();
		object->mTypeUniqueID = UNIQUE_ID_OF(T);
		return object;
	}
};

template<ObjectType T>
static std::shared_ptr<T> ObjectDynamicCast(const std::shared_ptr<Object>& object)
{
	if ((object == nullptr) ||
		!object->CheckUniqueID(UNIQUE_ID_OF(T)))
	{
		return std::shared_ptr<T>{nullptr};
	}
	return std::static_pointer_cast<T>(object);
}