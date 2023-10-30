#pragma once
#include "Component.h"
#include <list>
#include <unordered_map>

class ComponentContainer
{
public:
	using TypeUniqueID = RuntimeTypeUniqueID::Value;
	using ComponentPtr = std::shared_ptr<Component>;
	using UpdateList = std::list<ComponentPtr>;
	using SearchMap = std::unordered_map<TypeUniqueID, ComponentPtr>;
protected:
	ComponentContainer() = default;

	template<ComponentType T>
	std::weak_ptr<T> AddComponent(const std::weak_ptr<Object>& owner)
	{
		std::shared_ptr<T> component;
		// 無効なオーナー or すでに所持している
		if (HasComponent<T>() || owner.expired())
		{
			return component;
		}

		TypeUniqueID typeUniqueID = UNIQUE_ID_OF(T);
		component = std::make_shared<T>();
		// 作成したタイミングで所有者と型情報を埋め込む
		component->SetComponentInfo(owner, typeUniqueID);
		// 更新用リストと検索用マップに格納
		mUpdateList.emplace_back(component);
		mSearchMap[typeUniqueID] = component;
		return component;
	}

public:
	template<ComponentType T>
	bool HasComponent() const
	{
		return mSearchMap.contains(UNIQUE_ID_OF(T));
	}

	template<ComponentType T>
	std::weak_ptr<T> GetComponent() const
	{
		std::weak_ptr<T> view{};
		auto it = mSearchMap.find(UNIQUE_ID_OF(T));
		if (it != mSearchMap.end())
		{
			view = std::static_pointer_cast<T>(it->second);
		}
		return view;
	}

	template<ComponentType T>
	void RemoveComponent()
	{
		auto it = mSearchMap.find(UNIQUE_ID_OF(T));
		if (it != mSearchMap.end())
		{
			mUpdateList.remove(it->second);
			mSearchMap.erase(it);
		}
	}

	void UpdateComponents() const;

	virtual ~ComponentContainer() = default;
private:
	UpdateList mUpdateList;
	SearchMap mSearchMap;
};
