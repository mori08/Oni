#include "PlayerObject.hpp"
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
	constexpr double WALK_SPEED = 60;
	// ���鑬��
	constexpr double RUN_SPEED = 120;
	// �W�����v�̏����x�̑傫�� (z��������3.5�}�X���炢)
	constexpr double JAMP_SPEED = 200;
	// �d�͉����x
	constexpr double GRAVITY = 560;
	// �����}�E�X�Ƃ̋���
	constexpr double WALK_DISTANCE = 10.0;


	// �҂���Ԃ̃A�j���[�V����
	const Oni::Animation WAIT_ANIM
	(
		Oni::PosOrder{ {0,Point(0,1)} },
		false
	);

	// 1��������Ԃ̃A�j���[�V����
	const Oni::Animation ONE_WALK_ANIM
	(
		Oni::PosOrder{ {0.15,Point(1,1)},{0.15,Point(0,1)} },
		false
	);

	// ������Ԃ̃A�j���[�V����
	const Oni::Animation WALK_ANIM
	(
		Oni::PosOrder{ {0.15,Point(1,1)},{0.15,Point(0,1)} },
		true
	);

	// ������Ƃ��̃A�j���[�V����
	const Oni::Animation FALL_ANIM
	(
		Oni::PosOrder{ {0,Point(2,1)} },
		false
	);

	// �����Ԃ̃A�j���[�V����
	const Oni::Animation SLEEP_ANIM
	(
		Oni::PosOrder{ {0,Point(0,2)} },
		false
	);

	// �N��������Ƃ��̃A�j���[�V����
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
		// �����̌Œ�ɂ���
		bool isFixedDirection = MouseR.pressed();

		// �ړ��ʂ̌���
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

		// XY���ʕ����ł̈ړ����x�̐ݒ�
		mCollider.setVelocity(Collider::X, movement.x);
		mCollider.setVelocity(Collider::Y, movement.y);

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
			mSlide.startAnotherAnimation(U"Fall");
		}

		// �����̍X�V
		if (mDirection * movement.x < 0 && !isFixedDirection)
		{
			mDirection *= -1;
			mSlide.mirror();
		}
	}

}
