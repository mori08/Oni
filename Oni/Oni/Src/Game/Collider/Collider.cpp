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
		Vec3 v = Scene::DeltaTime() * mVelocity; // 速度(pixel/second)

		mIsOnCollisionStage = false;

		// -------------
		// Z軸方向の動き
		// -------------
		if (mIsOnGround)
		{
			// 地上
			if (v.z > 0)
			{
				// 空中へ
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
			// 空中
			mPos.z += v.z;
			const double terrainHeight = GameManager::instance().getStage().height(*this);

			if (minPos().z < terrainHeight) // 地上に落ちたとき
			{
				mIsOnGround = true;
				mVelocity.z = 0;
				mPos.z = terrainHeight + mSize.z / 2;
			}
		}

		// -------------
		// X軸方向の動き
		// -------------
		if (mIsOnGround)
		{
			// 地上
			const double terrainHeight // 移動先の地形の高さ
				= GameManager::instance().getStage().height(movedBy(Vec3(v.x, 0, 0)));

			if (terrainHeight - minPos().z > GameManager::SQUARE_Z - 1)
			{
				// 壁に衝突
				mVelocity.x = 0;
				mIsOnCollisionStage = true;
			}
			else if (terrainHeight - minPos().z < -GameManager::SQUARE_Z + 1)
			{
				// 落ちて空中へ
				mIsOnGround = false;
				mPos.x += v.x;
			}
			else
			{
				// 地上を歩き続ける
				mPos.x += v.x;
				mPos.z =  terrainHeight + mSize.z / 2;
			}

		}
		else
		{
			// 空中
			const double terrainHeight // 移動先の地形の高さ
				= GameManager::instance().getStage().height(movedBy(Vec3(v.x, 0, 0)));

			if (terrainHeight - minPos().z > 0)
			{
				// 壁にぶつかる
				mVelocity.x = 0;
				mIsOnCollisionStage = true;
			}
			else
			{
				// 空中を移動
				mPos.x += v.x;
			}

		}

		// -------------
		// Y軸方向の動き
		// -------------
		if (mIsOnGround)
		{
			// 地上
			const double terrainHeight // 移動先の地形の高さ
				= GameManager::instance().getStage().height(movedBy(Vec3(0, v.y, 0)));

			if (terrainHeight - minPos().z > 1)
			{
				// 壁に衝突
				mVelocity.y = 0;
				mIsOnCollisionStage = true;
			}
			else if (terrainHeight - minPos().z < -1)
			{
				// 落ちて空中へ
				mIsOnGround = false;
				mPos.y += v.y;
			}
			else
			{
				// 地面を歩き続ける
				mPos.y += v.y;
				mPos.z =  terrainHeight + mSize.z / 2;
			}
		}
		else
		{
			// 空中
			const double terrainHeight // 移動先の地形の高さ
				= GameManager::instance().getStage().height(movedBy(Vec3(0, v.y, 0)));

			if (terrainHeight - minPos().z > 0)
			{
				// 壁にぶつかる
				mVelocity.y = 0;
				mIsOnCollisionStage = true;
			}
			else
			{
				// 空中を移動
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