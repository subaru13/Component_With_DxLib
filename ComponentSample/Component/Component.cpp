#include "Component.h"

bool Component::CheckUniqueID(TypeUniqueID typeUniqueID) const
{
	return (mTypeUniqueID == typeUniqueID);
}

void Component::Update()
{

}

const std::weak_ptr<Object>& Component::GetOwner() const
{
	return mOwner;
}

const Component::TypeUniqueID& Component::GetTypeUniqueID() const
{
	return mTypeUniqueID;
}

void Component::SetComponentInfo(const std::weak_ptr<Object>& owner, TypeUniqueID typeUniqueID)
{
	mOwner = owner;
	mTypeUniqueID = typeUniqueID;
}
