#include "Component.h"
#include"Object.h"

bool Component::isUseable()
{
	return isActive && object->isActive;
}
