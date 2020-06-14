#include "GhostGirlObject.hpp"


namespace
{
	// �I�u�W�F�N�g�̃T�C�Y
	constexpr Vec3 COLLIDER_SIZE(25, 20, 50);

	// �摜�̐؂蕪���T�C�Y
	constexpr Size TEXTURE_SIZE(60, 60);

	// �����̗�
	constexpr double INIT_HP = 100;
}


namespace Oni
{

	GhostGirlObject::GhostGirlObject(const Vec3& pos)
		: GameObject
		(
			U"GhostGirl",
			Collider(pos, COLLIDER_SIZE), 
			ObjectType::ENEMY, 
			SliceTexture(U"GhostGirl", TEXTURE_SIZE)
		)
	{
		
	}

}
