#include "ComponentContainer.h"
#include <assert.h>

bool ComponentContainer::HasComponent(const std::string& name) const
{
	return mSearchMap.find(name) != mSearchMap.end();
}

bool ComponentContainer::HasComponent(const Handle& handle) const
{
	auto it = mSearchMap.find((*handle)->GetName());

	if (it != mSearchMap.end())
	{
		return it->second == handle;
	}

	return false;
}

void ComponentContainer::RemoveComponent(const std::string& name)
{
	auto it = mSearchMap.find(name);

	if (it != mSearchMap.end())
	{
		mList.erase(it->second);
		mSearchMap.erase(it);
	}
}

void ComponentContainer::RemoveComponent(Handle handle)
{
	if (HasComponent(handle))
	{
		mSearchMap.erase((*handle)->GetName());
		mList.erase(handle);
	}
}

void ComponentContainer::UpdateComponents() const
{
	// アップデート中にコンポーネントの
	// 追加・削除が起きても問題ないようにコピーを用意する
	List copyList = mList;

	for (auto component : copyList)
	{
		component->Update();
	}
}
