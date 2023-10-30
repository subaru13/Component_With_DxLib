#include "Component.h"

void Component::Update()
{

}

const std::weak_ptr<Object>& Component::GetOwner() const
{
	return mOwner;
}

void Component::SetComponentInfo(const std::weak_ptr<Object>& owner)
{
	mOwner = owner;
}
