#include "PlayerAttackObject.hpp"
#include "../../../MyLibrary.hpp"


namespace
{
	// オブジェクトのサイズ
	constexpr Vec3 COLLIDER_SIZE(10, 10, 10);

	// 画像サイズ
	constexpr Size SLICE_SIZE(16, 16);

	// 光の速さ
	constexpr double LIGHT_SPEED = 300.0;
	// 光が影に代わる時間(s)
	constexpr double LIGHT_SECOND = 1.0;
	// 敵を追跡をはじめる時間(s)
	constexpr double CHASE_SECOND = 0.2;
	// 影が消える時間(s)
	constexpr double SHADOW_SECOND = 32.0;
	// 影にかかる重力加速度
	constexpr double GRAVITY = -400;
	// 影の速さ
	constexpr double SHADOW_SPEED = 16;

	// 回転角の変更の比率
	constexpr double ANGLE_RATE = 0.5;

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

	PlayerAttackObject::PlayerAttackObject(const Vec3& pos, const Vec3& velocity, const String& actionName)
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
		mBattleData->setAction(U"Spin"         , [this](double actionSecond){ spinToPlayer(actionSecond); });
		mBattleData->setAction(U"Chase"        , [this](double actionSecond){ chaseEnemy(actionSecond); });
		mBattleData->changeAction(actionName);

		mSlide.setAnimation(U"Light"        , LIGHT_ANIM          );
		mSlide.setAnimation(U"LightToShadow", LIGHT_TO_SHADOW_ANIM);
		mSlide.setAnimation(U"Shadow"       , SHADOW_ANIM         );
		mSlide.start(U"Light");

		mCollider.setVelocity(velocity);

		mEnemyExist     = false;
		mEraseAble      = false;
		mCollisionEnemy = false;
	}


	void PlayerAttackObject::passAnother(GameObject& another) const
	{
		if (mBattleData->getActionName() != U"Shadow" && mBattleData->getActionName() != U"LightToShadow")
		{
			another.checkAnother(ObjectBattleData::CheckInfo(mCollider, ObjectType::PLAYER_ATTACK, 0));
		}

		if (mBattleData->getActionName() == U"Shadow")
		{
			another.checkAnother(ObjectBattleData::CheckInfo(mCollider, ObjectType::PLAYER_ENERGY, 0));
		}
	}


	void PlayerAttackObject::checkAnother(const ObjectBattleData::CheckInfo& checkInfo)
	{
		if (auto pos = checkTypeAndGetPos(checkInfo, ObjectType::PLAYER))
		{
			mPlayerPos = pos.value();
			mShadowMoveDirection += (pos.value().xy() - mCollider.centerPos().xy()).normalized();
		}
		if (checkTypeAndCollision(checkInfo, ObjectType::PLAYER_ENERGY))
		{
			mShadowMoveDirection += (mCollider.centerPos().xy() - checkInfo.collider.centerPos().xy()).normalized();
		}

		if (checkTypeAndCollision(checkInfo, ObjectType::PLAYER) && mBattleData->getActionName() == U"Shadow")
		{
			mEraseAble = true;
		}
		
		if (checkTypeAndCollision(checkInfo, ObjectType::ENEMY))
		{
			mCollisionEnemy = true;
		}
		
		if (auto pos = checkTypeAndGetPos(checkInfo, ObjectType::ENEMY))
		{
			if (!mEnemyExist)
			{
				mEnemyExist = true;
				mNearestEnemyPos = pos.value();
				return;
			}
			mEnemyExist = true;
			if (mNearestEnemyPos.distanceFrom(mCollider.centerPos()) > pos.value().distanceFrom(mCollider.centerPos()))
			{
				mNearestEnemyPos = pos.value();
			}
		}
	}


	bool PlayerAttackObject::eraseAble() const
	{
		return mEraseAble;
	}


	void PlayerAttackObject::updateLight(double actionSecond)
	{
		mEnemyExist = false;

		if (actionSecond > LIGHT_SECOND || mCollider.isOnCollisionStage() || mCollisionEnemy)
		{
			mSlide.start(U"LightToShadow");
			mBattleData->changeAction(U"LightToShadow");
			mCollider.setVelocity(Vec3::Zero());
			mCollider.setAcceleration(Collider::X, 0);
			mCollider.setAcceleration(Collider::Y, 0);
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
		const Vec2 movement = mShadowMoveDirection.isZero() ? Vec2::Zero() : (SHADOW_SPEED * mShadowMoveDirection.normalized());
		mShadowMoveDirection = Vec2::Zero();

		mCollider.setVelocity(Collider::X, movement.x);
		mCollider.setVelocity(Collider::Y, movement.y);

		if (actionSecond > SHADOW_SECOND)
		{
			mEraseAble = true;
		}
	}


	void PlayerAttackObject::spinToPlayer(double actionSecond)
	{
		double angle = atan2(mCollider.velocity().y, mCollider.velocity().x);

		// 目的角度の計算
		Vec2 toGoalVec = mPlayerPos.xy() - mCollider.centerPos().xy(); // プレイヤーへのベクトル
		toGoalVec = Vec2(-toGoalVec.y, toGoalVec.x); // 90度回転
		double goalAngle = atan2(toGoalVec.y, toGoalVec.x);
		goalAngle = goalAngle > angle ? goalAngle : (goalAngle + Math::TwoPi);

		internalDividingPoint(angle, goalAngle, ANGLE_RATE);
		
		mCollider.setVelocity(LIGHT_SPEED * Vec3(Cos(angle), Sin(angle), 0));

		updateLight(actionSecond);
	}


	void PlayerAttackObject::chaseEnemy(double actionSecond)
	{
		if (actionSecond > CHASE_SECOND)
		{
			const Vec3 goal = mEnemyExist ? mNearestEnemyPos : mCollider.centerPos();
			mCollider.setVelocity(LIGHT_SPEED * (goal - mCollider.centerPos()).normalized());
			mBattleData->changeAction(U"Light");
		}

		updateLight(actionSecond);
	}
}
