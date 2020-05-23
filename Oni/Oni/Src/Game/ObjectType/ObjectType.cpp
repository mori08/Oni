#include "ObjectType.hpp"


namespace Oni
{
	const ObjectType ObjectType::PLAYER       (1 << 0);

	const ObjectType ObjectType::ENEMY        (1 << 1);

	const ObjectType ObjectType::PLAYER_ATTACK(1 << 2);

	const ObjectType ObjectType::PLAYER_ENERGY(1 << 3);
}