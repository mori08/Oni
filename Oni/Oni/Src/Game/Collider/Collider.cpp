#include "Collider.hpp"
#include "../GameManager.hpp"


namespace Oni
{

	Collider::Collider(const Vec3 pos, Vec3 size)
		: mPos(pos)
		, mSize(size)
		, mVelocity(Vec3::Zero())
		, mAcceleration(Vec3::Zero())
	{
		mIsOnGround = false;
		if (minPos().z < GameManager::instance().getStage().height(*this))
		{
			mIsOnGround = true;
			mPos.z = GameManager::instance().getStage().height(*this) + mSize.z / 2;
		}
	}


	void Oni::Collider::update()
	{
		mVelocity += Scene::DeltaTime() * mAcceleration;
		Vec3 v = Scene::DeltaTime() * mVelocity; // ���x(pixel/second)

		mIsOnCollisionStage = false;

		// -------------
		// Z�������̓���
		// -------------
		if (mIsOnGround)
		{
			// �n��
			if (v.z > 0)
			{
				// �󒆂�
				mPos.z += v.z;
				mIsOnGround = false;
			}
			else
			{
				mVelocity.z = 0;
			}
		}
		else
		{
			// ��
			mPos.z += v.z;
			const double terrainHeight = GameManager::instance().getStage().height(*this);

			if (minPos().z < terrainHeight) // �n��ɗ������Ƃ�
			{
				mIsOnGround = true;
				mVelocity.z = 0;
				mPos.z = terrainHeight + mSize.z / 2;
			}
		}

		// -------------
		// X�������̓���
		// -------------
		if (mIsOnGround)
		{
			// �n��
			const double terrainHeight // �ړ���̒n�`�̍���
				= GameManager::instance().getStage().height(movedBy(Vec3(v.x, 0, 0)));

			if (terrainHeight - minPos().z > GameManager::SQUARE_Z - 1)
			{
				// �ǂɏՓ�
				mVelocity.x = 0;
				mIsOnCollisionStage = true;
			}
			else if (terrainHeight - minPos().z < -GameManager::SQUARE_Z + 1)
			{
				// �����ċ󒆂�
				mIsOnGround = false;
				mPos.x += v.x;
			}
			else
			{
				// �n������������
				mPos.x += v.x;
				mPos.z =  terrainHeight + mSize.z / 2;
			}

		}
		else
		{
			// ��
			const double terrainHeight // �ړ���̒n�`�̍���
				= GameManager::instance().getStage().height(movedBy(Vec3(v.x, 0, 0)));

			if (terrainHeight - minPos().z > 0)
			{
				// �ǂɂԂ���
				mVelocity.x = 0;
				mIsOnCollisionStage = true;
			}
			else
			{
				// �󒆂��ړ�
				mPos.x += v.x;
			}

		}

		// -------------
		// Y�������̓���
		// -------------
		if (mIsOnGround)
		{
			// �n��
			const double terrainHeight // �ړ���̒n�`�̍���
				= GameManager::instance().getStage().height(movedBy(Vec3(0, v.y, 0)));

			if (terrainHeight - minPos().z > 1)
			{
				// �ǂɏՓ�
				mVelocity.y = 0;
				mIsOnCollisionStage = true;
			}
			else if (terrainHeight - minPos().z < -1)
			{
				// �����ċ󒆂�
				mIsOnGround = false;
				mPos.y += v.y;
			}
			else
			{
				// �n�ʂ����������
				mPos.y += v.y;
				mPos.z =  terrainHeight + mSize.z / 2;
			}
		}
		else
		{
			// ��
			const double terrainHeight // �ړ���̒n�`�̍���
				= GameManager::instance().getStage().height(movedBy(Vec3(0, v.y, 0)));

			if (terrainHeight - minPos().z > 0)
			{
				// �ǂɂԂ���
				mVelocity.y = 0;
				mIsOnCollisionStage = true;
			}
			else
			{
				// �󒆂��ړ�
				mPos.y += v.y;
			}
		}
	}


	void Collider::setVelocity(size_t index, double speed)
	{
		switch (index)
		{
		case X: mVelocity.x = speed; break;
		case Y: mVelocity.y = speed; break;
		case Z: mVelocity.z = speed; break;
		}
	}


	void Collider::setAcceleration(size_t index, double value)
	{
		switch (index)
		{
		case X: mAcceleration.x = value; break;
		case Y: mAcceleration.y = value; break;
		case Z: mAcceleration.z = value; break;
		}
	}


	bool Collider::isOnCollisionStage() const
	{
		return mIsOnGround || mIsOnCollisionStage;
	}

}