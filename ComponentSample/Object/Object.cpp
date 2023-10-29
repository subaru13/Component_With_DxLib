#include "Object.h"

bool Object::CheckUniqueID(TypeUniqueID typeUniqueID) const
{
	return (mTypeUniqueID == typeUniqueID) ||
		(mTypeUniqueID == UNIQUE_ID_OF(Object));
}

Object::TypeUniqueID Object::GetTypeUniqueID() const
{
	return mTypeUniqueID;
}
