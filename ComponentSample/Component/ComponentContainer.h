#pragma once
#include "Component.h"
#include <memory>
#include <list>

class ComponentContainer
{
public:

	using ComponentPtr = std::shared_ptr<Component>;
	using List = std::list<ComponentPtr>;
	using Handle = List::iterator;
protected:
	ComponentContainer() = default;

	template<ComponentType T>
	Handle AddComponent(const std::weak_ptr<Object>& owner)
	{
		ComponentPtr component = std::make_shared<T>();
		// 作成したタイミングで所有者と型情報を埋め込む
		component->SetComponentInfo(owner, RuntimeTypeUniqueID::Get<T>());
		return mList.insert(mList.end(), component);
	}

	bool HasComponent(const std::weak_ptr<const Object>& owner, const Handle& handle) const;

	template<ComponentType T>
	std::weak_ptr<T> GetComponent(const std::weak_ptr<const Object>& owner, const Handle& handle) const
	{
		std::weak_ptr<T> view{};
		if (HasComponent(owner, handle))
		{
			view = ComponentDynamicCast<T>(*handle);
		}
		return view;
	}

	template<>
	std::weak_ptr<Component> GetComponent<Component>(const std::weak_ptr<const Object>& owner, const Handle& handle) const
	{
		std::weak_ptr<Component> view{};
		if (HasComponent(owner, handle))
		{
			view = (*handle);
		}
		return view;
	}

public:

	void RemoveComponent(Handle handle);

	void UpdateComponents() const;

	virtual ~ComponentContainer() = default;
private:
	List mList;
};
