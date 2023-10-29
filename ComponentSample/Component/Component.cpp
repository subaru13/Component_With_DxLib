#include "Component.h"

bool Component::CheckUniqueID(TypeUniqueID typeUniqueID) const
{
	return (mTypeUniqueID == typeUniqueID) ||
		(mTypeUniqueID == UNIQUE_ID_OF(Component));
}

void Component::Update()
{

}

const std::string& Component::GetName() const
{
	return mName;
}

const std::weak_ptr<Object>& Component::GetOwner() const
{
	return mOwner;
}

const Component::TypeUniqueID& Component::GetTypeUniqueID() const
{
	return mTypeUniqueID;
}

void Component::SetComponentInfo(
	const std::weak_ptr<Object>& owner,
	TypeUniqueID typeUniqueID,
	const std::string& name)
{
	mOwner = owner;
	mTypeUniqueID = typeUniqueID;
	mName = name;
}
