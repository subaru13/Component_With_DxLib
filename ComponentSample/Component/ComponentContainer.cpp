#include "ComponentContainer.h"
#include <assert.h>

bool ComponentContainer::HasComponent(const std::weak_ptr<const Object>& owner, const Handle& handle) const
{
	assert(!owner.expired());

	if (handle._Ptr != nullptr)
	{
		return owner.lock() == (*handle)->GetOwner().lock();
	}
	return false;
}

void ComponentContainer::RemoveComponent(Handle handle)
{
	mList.erase(handle);
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
