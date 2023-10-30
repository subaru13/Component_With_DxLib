#include "ComponentContainer.h"

void ComponentContainer::UpdateComponents() const
{
	// 更新中のAdd/Remove回避ように更新用リストをコピーし
	// コピー側から更新をかける
	UpdateList copyList = mUpdateList;

	for (ComponentPtr& component : copyList)
	{
		component->Update();
	}
}
