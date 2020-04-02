#include "GameObject.hpp"
#include "../GameManager.hpp"


namespace Oni
{

	GameObject::GameObject(const Vec3& pos, const Vec3 size, const ObjectType& type)
		: mCollider(pos, size)
		, mType(type)
		, mVelocity(0,0,0)
		, mAcceleration(0,0,0)
	{
		mIsOnGround = false;
		if (mCollider.minPos().z < GameManager::instance().getTerrainHeight(mCollider))
		{
			mIsOnGround = true;
			mCollider.moveBy(Vec3(0, 0, GameManager::instance().getTerrainHeight(mCollider) - mCollider.minPos().z));
		}
	}


	void GameObject::moveObject()
	{
		mVelocity += Scene::DeltaTime() * mAcceleration;
		Vec3 deltaVelocity = Scene::DeltaTime() * mVelocity;

		// Z軸方向の動き
		if (mIsOnGround)
		{
			mVelocity.z = 0;
		}
		else
		{
			mCollider.moveBy(Vec3(0, 0, deltaVelocity.z));
			const double terrainHeight = GameManager::instance().getTerrainHeight(mCollider);

			if (mCollider.minPos().z < terrainHeight) // 地面に落ちたとき
			{
				mIsOnGround = true;
				mCollider.moveBy(Vec3(0, 0, terrainHeight - mCollider.minPos().z));
				mVelocity.z = 0;
			}
		}

		// X軸方向の動き
		if (mIsOnGround) // 地面に接しているとき //
		{
			const double preHeight = mCollider.minPos().z;
			const double newHeight = GameManager::instance().getTerrainHeight(mCollider.movedBy(Vec3(deltaVelocity.x, 0, 0)));
			
			if (newHeight - preHeight > GameManager::SQUARE_Z - 1)       // 壁に衝突 //
			{
				mVelocity.x = 0;
			}
			else if (newHeight - preHeight < -GameManager::SQUARE_Z + 1) // 落ちる //
			{
				mIsOnGround = false;
				mCollider.moveBy(Vec3(deltaVelocity.x, 0, 0));
			}
			else                                                         // 地面を歩き続ける //
			{
				mCollider.moveBy(Vec3(deltaVelocity.x, 0, newHeight - preHeight));
			}
		}
		else // 空中にいるとき //
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

		// Y軸方向の動き
		if (mIsOnGround) // 地面に接しているとき //
		{
			const double preHeight = mCollider.minPos().z;
			const double newHeight = GameManager::instance().getTerrainHeight(mCollider.movedBy(Vec3(0, deltaVelocity.y, 0)));

			if (newHeight - preHeight > 1) // 壁に衝突
			{
				mVelocity.y = 0;
			}
			else if (newHeight - preHeight < -1) // 落ちる
			{
				mCollider.moveBy(Vec3(0, deltaVelocity.y, 0));
				mIsOnGround = false;
			}
			else // 地面を歩き続ける
			{
				mCollider.moveBy(Vec3(0, deltaVelocity.y, newHeight - preHeight));
			}
		}
		else // 空中にいるとき //
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
	}

}
