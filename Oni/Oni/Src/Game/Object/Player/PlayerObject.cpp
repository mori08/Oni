#include "PlayerObject.hpp"
#include "../PlayerAttack/PlayerAttackObject.hpp"
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


	// 攻撃の速さ
	constexpr double LIGHT_SPEED = 300;
	// 1つ分のチャージに必要な時間(s)
	constexpr double ONE_CHARGE_TIME = 1.0;

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
		mBattleData = ObjectBattleData(INIT_HP);
		mBattleData->setAction(U"Control", [this](double) { control(); });
		mBattleData->changeAction(U"Control");

		mEventData = ObjectEventData(mSlide);

		mCollider.setAcceleration(Collider::Z, -GRAVITY);

		mSlide.setAnimation(U"Wait", WAIT_ANIM);
		mSlide.setAnimation(U"Walk", WALK_ANIM);
		mSlide.setAnimation(U"OneWalk", ONE_WALK_ANIM);
		mSlide.setAnimation(U"Fall", FALL_ANIM);

		mDirection = -1;

		mChargeSecond = 0;
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


	void PlayerObject::checkAnother(const ObjectBattleData::CheckInfo& checkInfo)
	{
		if (checkTypeAndCollision(checkInfo, ObjectType::ENEMY))
		{
			// 判定
		}
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

		// 攻撃
		if (MouseL.pressed())
		{
			mChargeSecond += Scene::DeltaTime();
		}
		if (MouseL.up())
		{
			if (mChargeSecond < ONE_CHARGE_TIME)
			{
				// 通常攻撃
				GameManager::instance().addObject(std::make_shared<PlayerAttackObject>(mCollider.centerPos(), Vec3::Right(LIGHT_SPEED * mDirection)));
			}
			else
			{
				// 溜め攻撃
				chaseAttack();
			}
			mChargeSecond = 0;
		}

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


	void PlayerObject::tripleAttack()
	{
		// 追加の攻撃の角度
		constexpr double attackAngle = 0.1;

		GameManager::instance().addObject
		(
			std::make_shared<PlayerAttackObject>(mCollider.centerPos(), Vec3::Right(LIGHT_SPEED * mDirection))
		);
		GameManager::instance().addObject
		(
			std::make_shared<PlayerAttackObject>(mCollider.centerPos(), LIGHT_SPEED * Vec3(mDirection * Cos(attackAngle), +Sin(attackAngle), 0))
		);
		GameManager::instance().addObject
		(
			std::make_shared<PlayerAttackObject>(mCollider.centerPos(), LIGHT_SPEED * Vec3(mDirection * Cos(attackAngle), -Sin(attackAngle), 0))
		);
	}


	void PlayerObject::spinAttack()
	{
		GameManager::instance().addObject
		(
			std::make_shared<PlayerAttackObject>(mCollider.centerPos(), Vec3::Right(LIGHT_SPEED), U"Spin")
		);
		GameManager::instance().addObject
		(
			std::make_shared<PlayerAttackObject>(mCollider.centerPos(), Vec3::Up(LIGHT_SPEED), U"Spin")
		);
		GameManager::instance().addObject
		(
			std::make_shared<PlayerAttackObject>(mCollider.centerPos(), Vec3::Left(LIGHT_SPEED), U"Spin")
		);
		GameManager::instance().addObject
		(
			std::make_shared<PlayerAttackObject>(mCollider.centerPos(), Vec3::Down(LIGHT_SPEED), U"Spin")
		);
	}


	void PlayerObject::chaseAttack()
	{
		// 光の数
		constexpr int32 LIGHT_NUM = 5;

		for (int32 i = 0; i < LIGHT_NUM; ++i)
		{
			const double angle    = Math::TwoPi * i / LIGHT_NUM;
			const Vec3   velocity = LIGHT_SPEED*Vec3(mDirection * Cos(angle), Sin(angle), 0);
			
			GameManager::instance().addObject
			(
				std::make_shared<PlayerAttackObject>(mCollider.centerPos(), velocity, U"Chase")
			);
		}
	}

}
