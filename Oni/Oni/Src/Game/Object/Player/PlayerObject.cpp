#include "PlayerObject.hpp"
#include "../PlayerAttack/PlayerAttackObject.hpp"
#include "../../GameManager.hpp"


namespace
{
	// �I�u�W�F�N�g�̃T�C�Y
	constexpr Vec3 COLLIDER_SIZE(25, 20, 50);
	// �摜�̃T�C�Y
	constexpr Size TEXTURE_SIZE(60, 60);


	// �����̗�
	constexpr double INIT_HP = 100;
	// ��������
	constexpr double WALK_SPEED = 120;
	// �W�����v�̏����x�̑傫�� (z��������3.5�}�X���炢)
	constexpr double JAMP_SPEED = 200;
	// �d�͉����x
	constexpr double GRAVITY = 560;
	// �����}�E�X�Ƃ̋���
	constexpr double WALK_DISTANCE = 10.0;


	// �U���̑���
	constexpr double LIGHT_SPEED = 300;
	// 1���̃`���[�W�ɕK�v�Ȏ���(s)
	constexpr double ONE_CHARGE_TIME = 1.0;

	// �҂���Ԃ̃A�j���[�V����
	const Oni::Animation WAIT_ANIM
	(
		Oni::PosOrder{ {0,Point(0,0)} },
		false
	);

	// 1��������Ԃ̃A�j���[�V����
	const Oni::Animation ONE_WALK_ANIM
	(
		Oni::PosOrder{ {0.15,Point(2,0)},{0.15,Point(0,0)} },
		false
	);

	// ������Ԃ̃A�j���[�V����
	const Oni::Animation WALK_ANIM
	(
		Oni::PosOrder{ {0.15,Point(2,0)},{0.15,Point(0,0)} },
		true
	);

	// �W�����v�̃A�j���[�V����
	const Oni::Animation JAMP_ANIM
	(
		Oni::PosOrder{ {0,Point(1,1)} },
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
		mSlide.setAnimation(U"Jamp", JAMP_ANIM);

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
			// ����
		}
	}


	void PlayerObject::control()
	{
		// �ړ��ʂ̌���
		const Vec3 groundPos = Vec3(mCollider.centerPos().xy(), GameManager::instance().getStage().height(mCollider));
		Vec2 movement = Cursor::PosF() - GameManager::drawPos(groundPos);
		if (!Scene::Rect().mouseOver())
		{
			movement = Vec2::Zero();
		}
		else if (movement.length() > WALK_DISTANCE)
		{
			movement = WALK_SPEED * movement.normalize();
		}
		else
		{
			movement = Vec2::Zero();
		}

		// XY���ʕ����ł̈ړ����x�̐ݒ�
		mCollider.setVelocity(Collider::X, movement.x);
		mCollider.setVelocity(Collider::Y, movement.y);

		// �W�����v
		if (mCollider.isOnGround() && MouseR.down())
		{
			mCollider.setVelocity(Collider::Z, JAMP_SPEED);
		}

		// �U��
		if (MouseL.pressed())
		{
			mChargeSecond += Scene::DeltaTime();
		}
		if (MouseL.up())
		{
			if (mChargeSecond < ONE_CHARGE_TIME)
			{
				// �ʏ�U��
				GameManager::instance().addObject(std::make_shared<PlayerAttackObject>(mCollider.centerPos(), Vec3::Right(LIGHT_SPEED * mDirection)));
			}
			else
			{
				// ���ߍU��
				tripleAttack();
			}
			mChargeSecond = 0;
		}

		// �A�j���[�V�����̍X�V
		if (mCollider.isOnGround())
		{
			// �n��

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
			// ��
			mSlide.startAnotherAnimation(U"Jamp");
		}

		// �����̍X�V
		if (mDirection * movement.x < 0)
		{
			mDirection *= -1;
			mSlide.mirror();
		}
	}


	void PlayerObject::tripleAttack()
	{
		// �ǉ��̍U���̊p�x
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

	}


	void PlayerObject::chaseAttack()
	{

	}

}
