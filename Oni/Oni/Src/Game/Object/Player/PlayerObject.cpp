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
	constexpr double WALK_SPEED = 90;
	// �W�����v�̏����x�̑傫�� (z��������3.5�}�X���炢)
	constexpr double JAMP_SPEED = 280;
	// �d�͉����x
	constexpr double GRAVITY = 560;

	// �U���̑���
	constexpr double LIGHT_SPEED = 300;

	// �҂���Ԃ̃A�j���[�V����
	const Oni::Animation WAIT_ANIM
	(
		Oni::PosOrder{ {0,Point(0,0)} },
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


	void PlayerObject::checkAnother(const ObjectBattleData::CheckInfo& checkInfo)
	{
		if (checkTypeAndCollision(checkInfo, ObjectType::ENEMY))
		{
			// ����
		}
	}


	void PlayerObject::control()
	{
		// �ړ������̌���
		Vec2 movement = Vec2::Zero();
		movement.x += KeyRight.pressed() - KeyLeft.pressed();
		movement.y += KeyDown .pressed() - KeyUp  .pressed();
		movement = movement.isZero() ? Vec2::Zero() : movement.normalized();
		movement *= WALK_SPEED;

		// XY���ʕ����ł̈ړ����x�̐ݒ�
		mCollider.setVelocity(Collider::X, movement.x);
		mCollider.setVelocity(Collider::Y, movement.y);

		// �W�����v
		if (mCollider.isOnGround() && KeyX.down())
		{
			mCollider.setVelocity(Collider::Z, JAMP_SPEED);
		}

		// �U��
		if (KeyZ.up())
		{
			GameManager::instance().addObject(std::make_shared<PlayerAttackObject>(mCollider.centerPos(), Vec3::Right(LIGHT_SPEED * mDirection)));
		}

		// �A�j���[�V�����̍X�V
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

		// �����̍X�V
		if (mDirection * movement.x < 0)
		{
			mDirection *= -1;
			mSlide.mirror();
		}
	}

}
