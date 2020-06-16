#include "PlayerObject.hpp"
#include "../../GameManager.hpp"


namespace
{
	// オブジェクトのサイズ
	constexpr Vec3 COLLIDER_SIZE(25, 20, 50);
	// 画像のサイズ
	constexpr Size TEXTURE_SIZE(60, 60);


	// 初期体力
	constexpr double INIT_HP = 100;
	// 歩く速さ
	constexpr double WALK_SPEED = 60;
	// 走る速さ
	constexpr double RUN_SPEED = 120;
	// ジャンプの初速度の大きさ (z軸方向で3.5マスくらい)
	constexpr double JAMP_SPEED = 200;
	// 重力加速度
	constexpr double GRAVITY = 560;
	// 歩くマウスとの距離
	constexpr double WALK_DISTANCE = 10.0;


	// 待ち状態のアニメーション
	const Oni::Animation WAIT_ANIM
	(
		Oni::PosOrder{ {0,Point(0,1)} },
		false
	);

	// 1歩歩き状態のアニメーション
	const Oni::Animation ONE_WALK_ANIM
	(
		Oni::PosOrder{ {0.15,Point(1,1)},{0.15,Point(0,1)} },
		false
	);

	// 歩き状態のアニメーション
	const Oni::Animation WALK_ANIM
	(
		Oni::PosOrder{ {0.15,Point(1,1)},{0.15,Point(0,1)} },
		true
	);

	// 落ちるときのアニメーション
	const Oni::Animation FALL_ANIM
	(
		Oni::PosOrder{ {0,Point(2,1)} },
		false
	);

	// 眠り状態のアニメーション
	const Oni::Animation SLEEP_ANIM
	(
		Oni::PosOrder{ {0,Point(0,2)} },
		false
	);

	// 起きあがるときのアニメーション
	const Oni::Animation WAKE_ANIM
	(
		Oni::PosOrder{ {0.5,Point(1,2)},{0.5,Point(0,1)} },
		false
	);
}


namespace Oni
{

	PlayerObject::PlayerObject(const Vec3& pos)
		: GameObject
		(
			U"Player",
			Collider(pos, COLLIDER_SIZE), 
			ObjectType::PLAYER, 
			SliceTexture(U"Player", TEXTURE_SIZE)
		)
	{
		mEventData = ObjectEventData(mSlide);

		mCollider.setAcceleration(Collider::Z, -GRAVITY);

		setAnim(U"Wait", WAIT_ANIM);
		setAnim(U"Walk", WALK_ANIM);
		setAnim(U"OneWalk", ONE_WALK_ANIM);
		setAnim(U"Fall", FALL_ANIM);

		mDirection = -1;

		mChargeSecond = 0;
	}


	void PlayerObject::draw() const
	{
		mSlide.getTexture().draw(getDrawTexturePoint());
	}


	void PlayerObject::control()
	{
		// 向きの固定について
		bool isFixedDirection = MouseR.pressed();

		// 移動量の決定
		const Vec3 groundPos = Vec3(mCollider.centerPos().xy(), GameManager::instance().getStage().height(mCollider));
		Vec2 movement = Cursor::PosF() - GameManager::drawPos(groundPos);
		if (!Scene::Rect().mouseOver())
		{
			movement = Vec2::Zero();
		}
		else if (movement.length() > WALK_DISTANCE)
		{
			movement = (isFixedDirection ? WALK_SPEED : RUN_SPEED) * movement.normalize();
		}
		else
		{
			movement = Vec2::Zero();
		}

		// XY平面方向での移動速度の設定
		mCollider.setVelocity(Collider::X, movement.x);
		mCollider.setVelocity(Collider::Y, movement.y);

		// アニメーションの更新
		if (mCollider.isOnGround())
		{
			// 地上

			if (mSlide.isFinished())
			{
				if (movement.isZero())
				{
					mSlide.startAnotherAnimation(U"Wait");
				}
				else
				{
					mSlide.start(U"OneWalk");
				}
			}
		}
		else
		{
			// 空中
			mSlide.startAnotherAnimation(U"Fall");
		}

		// 向きの更新
		if (mDirection * movement.x < 0 && !isFixedDirection)
		{
			mDirection *= -1;
			mSlide.mirror();
		}
	}

}
