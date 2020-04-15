#include "GhostGirlObject.hpp"


namespace
{
	// オブジェクトのサイズ
	constexpr Vec3 COLLIDER_SIZE(25, 50, 20);

	// 画像の切り分けサイズ
	constexpr Size TEXTURE_SIZE(60, 60);

	// 初期体力
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
		mBattleData = ObjectBattleData(INIT_HP);
	}

}
