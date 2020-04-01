#include "GameObject.hpp"
#include "../GameManager.hpp"


namespace Oni
{

	void GameObject::moveObject()
	{
		mVelocity += Scene::DeltaTime() * mAcceleration;
		Vec3 deltaVelocity = Scene::DeltaTime() * mVelocity;

		// X�������̓���
		if (mIsOnGround) // �n�ʂɐڂ��Ă���Ƃ� //
		{
			const double preHeight = mCollider.minPos().z;
			const double newHeight = GameManager::instance().getTerrainHeight(mCollider.movedBy(Vec3(deltaVelocity.x, 0, 0)));
			
			if (newHeight - preHeight > GameManager::SQUARE_Z - 1)       // �ǂɏՓ� //
			{
				mVelocity.x = 0;
			}
			else if (newHeight - preHeight < -GameManager::SQUARE_Z + 1) // ������ //
			{
				mIsOnGround = false;
				mCollider.moveBy(Vec3(deltaVelocity.x, 0, 0));
			}
			else                                                         // �n�ʂ���������� //
			{
				mCollider.moveBy(Vec3(deltaVelocity.x, 0, newHeight - preHeight));
			}
		}
		else // �󒆂ɂ���Ƃ� //
		{
			const double myHeight      = mCollider.minPos().z;
			const double terrainHeight = GameManager::instance().getTerrainHeight(mCollider.movedBy(Vec3(deltaVelocity.x, 0, 0)));

			if (terrainHeight - myHeight > 0)
			{
				mVelocity.x = 0;
			}
			else
			{
				mCollider.moveBy(Vec3(deltaVelocity.x, 0, 0));
			}
		}

		// Y�������̓���
		if (mIsOnGround) // �n�ʂɐڂ��Ă���Ƃ� //
		{
			const double preHeight = mCollider.minPos().z;
			const double newHeight = GameManager::instance().getTerrainHeight(mCollider.movedBy(Vec3(0, deltaVelocity.y, 0)));

			if (newHeight - preHeight > 1) // �ǂɏՓ�
			{
				mVelocity.y = 0;
			}
			else if (newHeight - preHeight < -1) // ������
			{
				mCollider.moveBy(Vec3(0, deltaVelocity.y, 0));
				mIsOnGround = false;
			}
			else // �n�ʂ����������
			{
				mCollider.moveBy(Vec3(0, deltaVelocity.y, newHeight - preHeight));
			}
		}
		else // �󒆂ɂ���Ƃ� //
		{
			const double myHeight      = mCollider.minPos().z;
			const double terrainHeight = GameManager::instance().getTerrainHeight(mCollider.movedBy(Vec3(0, deltaVelocity.y, 0)));

			if (terrainHeight - myHeight > 0)
			{
				mVelocity.y = 0;
			}
			else
			{
				mCollider.moveBy(Vec3(0, deltaVelocity.y, 0));
			}
		}

		// Z�������̓���
		if (!mIsOnGround)
		{
			mCollider.moveBy(Vec3(0, 0, deltaVelocity.z));
			const double terrainHeight = GameManager::instance().getTerrainHeight(mCollider);

			if (mCollider.minPos().z < terrainHeight) // �n�ʂɗ������Ƃ�
			{
				mIsOnGround = true;
				mCollider.moveBy(Vec3(0, 0, terrainHeight - mCollider.minPos().z));
			}
		}
	}

}
