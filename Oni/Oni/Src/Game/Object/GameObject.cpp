#include "GameObject.hpp"
#include "../GameManager.hpp"


namespace Oni
{

	GameObject::GameObject(const Vec3& pos, const Vec3 size, const ObjectType& type)
		: mCollider(pos, size)
		, mType(type)
	{

	}

}
