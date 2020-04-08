#include "PlayerObject.hpp"


namespace
{
	// オブジェクトのサイズ
	constexpr Vec3 COLLIDER_SIZE(25, 60, 20);

	// 画像のサイズ
	constexpr Size TEXTURE_SIZE(60, 60);

	// 初期体力
	constexpr double INIT_HP = 100;
	// 歩く速さ
	constexpr double WALK_SPEED = 90;
	// ジャンプの初速度の大きさ (z軸方向で3.5マスくらい)
	constexpr double JAMP_SPEED = 280;
	// 重力加速度
	constexpr double GRAVITY = 560;

	// 待ち状態のアニメーション
	const Oni::Animation WAIT_ANIM
	(
		Oni::PosOrder{ {0,Point(0,0)} },
		false
	);

	// 歩き状態のアニメーション
	const Oni::Animation WALK_ANIM
	(
		Oni::PosOrder{ {0.15,Point(2,0)},{0.15,Point(0,0)} },
		true
	);

	// ジャンプのアニメーション
	const Oni::Animation JAMP_ANIM
	(
		Oni::PosOrder{ {0,Point(1,1)} },
		false
	);
}


namespace Oni
{

	PlayerObject::PlayerObject(const Vec3& pos)
		: GameObject(Collider(pos, COLLIDER_SIZE), ObjectType::PLAYER, SliceTexture(U"Player", TEXTURE_SIZE))
	{
		mBattleData = ObjectBattleData(INIT_HP);
		mBattleData->setAction(U"Control", [this](double) { control(); });
		mBattleData->changeAction(U"Control");

		mCollider.setAcceleration(Collider::Z, -GRAVITY);

		mSlide.setAnimation(U"Wait", WAIT_ANIM);
		mSlide.setAnimation(U"Walk", WALK_ANIM);
		mSlide.setAnimation(U"Jamp", JAMP_ANIM);

		mDirection = -1;
	}


	void PlayerObject::updateBattle()
	{
		mCollider.update();
		mBattleData->update();
		mSlide.update();
	}


	void PlayerObject::draw() const
	{
		mSlide.getTexture().draw(getDrawTexturePoint());
	}


	void PlayerObject::control()
	{
		// 移動方向の決定
		Vec2 movement = Vec2::Zero();
		movement.x += KeyRight.pressed() - KeyLeft.pressed();
		movement.y += KeyDown .pressed() - KeyUp  .pressed();
		movement = movement.isZero() ? Vec2::Zero() : movement.normalized();
		movement *= WALK_SPEED;

		// XY平面方向での移動速度の設定
		mCollider.setVelocity(Collider::X, movement.x);
		mCollider.setVelocity(Collider::Y, movement.y);

		// ジャンプ
		if (mCollider.isOnGround() && KeyC.down())
		{
			mCollider.setVelocity(Collider::Z, JAMP_SPEED);
		}

		// アニメーションの更新
		if (mCollider.isOnGround())
		{
			if (movement.isZero()) 
			{
				mSlide.startAnotherAnimation(U"Wait"); 
			}
			else 
			{ 
				mSlide.startAnotherAnimation(U"Walk"); 
			}
		}
		else
		{
			mSlide.startAnotherAnimation(U"Jamp");
		}

		// 向きの更新
		if (mDirection * movement.x < 0)
		{
			mDirection *= -1;
			mSlide.mirror();
		}
	}

}
