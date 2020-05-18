#include "PlayerAttackObject.hpp"


namespace
{
	// オブジェクトのサイズ
	constexpr Vec3 COLLIDER_SIZE(10, 10, 10);

	// 画像サイズ
	constexpr Size SLICE_SIZE(16, 16);

	// 光が影に代わる時間(s)
	constexpr double LIGHT_SECOND = 1.0;
	// 影が消える時間(s)
	constexpr double SHADOW_SECOND = 32.0;
	// 影にかかる重力加速度
	constexpr double GRAVITY = -400;
	// 影の速さ
	constexpr double SHADOW_SPEED = 16;

	// 光のアニメーション
	const Oni::Animation LIGHT_ANIM
	(
		Oni::PosOrder{ {0,Point(0,0)} },
		false
	);

	// 光->影のアニメーション
	const Oni::Animation LIGHT_TO_SHADOW_ANIM
	(
		Oni::PosOrder{ {0.1,Point(0,0)},{0.1,Point(1,0)},{0.1,Point(2,0)},{0.1,Point(3,0)},{0.1,Point(0,1)},{0.1,Point(1,1)} },
		false
	);

	// 影のアニメーション
	const Oni::Animation SHADOW_ANIM
	(
		Oni::PosOrder{ {0,Point(2,1)} },
		false
	);
}


namespace Oni
{

	uint32 PlayerAttackObject::sShareId = 0;

	PlayerAttackObject::PlayerAttackObject(const Vec3& pos, const Vec3& velocity)
		: GameObject
		(
			U"PlayerAttack" + ToString(sShareId++),
			Collider(pos, COLLIDER_SIZE),
			ObjectType::PLAYER_ATTACK,
			SliceTexture(U"PlayerAttack", SLICE_SIZE)
		)
	{
		mBattleData = ObjectBattleData(0);
		mBattleData->setAction(U"Light"        , [this](double actionSecond){ updateLight(actionSecond); });
		mBattleData->setAction(U"LightToShadow", [this](double){ lightToShadow(); });
		mBattleData->setAction(U"Shadow"       , [this](double actionSecond){ updateShadow(actionSecond); });
		mBattleData->changeAction(U"Light");

		mSlide.setAnimation(U"Light"        , LIGHT_ANIM          );
		mSlide.setAnimation(U"LightToShadow", LIGHT_TO_SHADOW_ANIM);
		mSlide.setAnimation(U"Shadow"       , SHADOW_ANIM         );

		mCollider.setVelocity(velocity);

		mEraseAble = false;
	}


	void PlayerAttackObject::checkAnother(const ObjectBattleData::CheckInfo& checkInfo)
	{
		if (auto pos = checkTypeAndGetPos(checkInfo, ObjectType::PLAYER))
		{
			mPlayerPos = pos.value().xy();
		}

		if (checkTypeAndCollision(checkInfo, ObjectType::PLAYER) && mBattleData->getActionName() == U"Shadow")
		{
			mEraseAble = true;
		}
	}


	bool PlayerAttackObject::eraseAble() const
	{
		return mEraseAble;
	}


	void PlayerAttackObject::updateLight(double actionSecond)
	{
		if (actionSecond > LIGHT_SECOND)
		{
			mSlide.start(U"LightToShadow");
			mBattleData->changeAction(U"LightToShadow");
			mCollider.setVelocity(Vec3::Zero());
			mCollider.setAcceleration(Collider::Z, GRAVITY);
		}
	}


	void PlayerAttackObject::lightToShadow()
	{
		if (mCollider.isOnGround())
		{
			mSlide.start(U"Shadow");
			mBattleData->changeAction(U"Shadow");
		}
	}


	void PlayerAttackObject::updateShadow(double actionSecond)
	{
		const Vec2 movement = SHADOW_SPEED * (mPlayerPos - mCollider.centerPos().xy()).normalized();

		mCollider.setVelocity(Collider::X, movement.x);
		mCollider.setVelocity(Collider::Y, movement.y);

		if (actionSecond > SHADOW_SECOND)
		{
			mEraseAble = true;
		}
	}

}
