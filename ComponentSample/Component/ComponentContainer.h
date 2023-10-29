#pragma once
#include "Component.h"
#include <list>
#include <unordered_map>

class ComponentContainer
{
public:
	using ComponentPtr = std::shared_ptr<Component>;
	using List = std::list<ComponentPtr>;
	using Handle = List::iterator;
	using SearchMap = std::unordered_map<std::string, Handle>;
protected:
	ComponentContainer() = default;

	template<ComponentType T>
	Handle AddComponent(const std::weak_ptr<Object>& owner,
		const std::string& name)
	{
		// 名前被り or 無効なオーナー
		if (HasComponent(name) || owner.expired())
		{
			return mList.end();
		}

		ComponentPtr component = std::make_shared<T>();
		// 作成したタイミングで所有者と型情報を埋め込む
		component->SetComponentInfo(owner, UNIQUE_ID_OF(T), name);
		return mSearchMap[name] = mList.insert(mList.end(), component);
	}

public:

	bool HasComponent(const std::string& name) const;
	bool HasComponent(const Handle& handle) const;

	template<ComponentType T>
	std::weak_ptr<T> GetComponent(const std::string& name) const
	{
		auto it = mSearchMap.find(name);
		if (it != mSearchMap.end())
		{
			return ComponentDynamicCast<T>(*it->second);
		}
		return std::weak_ptr<T>{};
	}

	template<>
	std::weak_ptr<Component> GetComponent<Component>(const std::string& name) const
	{
		auto it = mSearchMap.find(name);
		if (it != mSearchMap.end())
		{
			return (*it->second);
		}
		return std::weak_ptr<Component>{};
	}

	template<ComponentType T>
	std::weak_ptr<T> GetComponent(const Handle& handle) const
	{
		std::weak_ptr<T> view{};
		if (HasComponent(handle))
		{
			view = ComponentDynamicCast<T>(*handle);
		}
		return view;
	}

	template<>
	std::weak_ptr<Component> GetComponent<Component>(const Handle& handle) const
	{
		std::weak_ptr<Component> view{};
		if (HasComponent(handle))
		{
			view = (*handle);
		}
		return view;
	}

	void RemoveComponent(const std::string& name);
	void RemoveComponent(Handle handle);

	void UpdateComponents() const;

	virtual ~ComponentContainer() = default;
private:
	List mList;
	SearchMap mSearchMap;
};
