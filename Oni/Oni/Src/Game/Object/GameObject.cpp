#include "GameObject.hpp"
#include "../GameManager.hpp"


namespace Oni
{

	GameObject::GameObject(const Collider& collider, const ObjectType& type, const SliceTexture& slide)
		: mCollider(collider)
		, mType(type)
		, mSlide(slide)
	{

	}


	void GameObject::updateBattle()
	{
		mCollider.update();

		if (mBattleData)
		{
			mBattleData->update();
		}

		mSlide.update();
	}


	void GameObject::draw() const
	{
		mSlide.getTexture().draw(getDrawTexturePoint());
	}


	Point GameObject::getDrawTexturePoint() const
	{
		Vec2 rtn = GameManager::instance().drawPos(mCollider.centerPos());
		
		rtn.x +=                        - mSlide.getSliceSize().x / 2;
		rtn.y += mCollider.size().z / 2 - mSlide.getSliceSize().y;
		
		return rtn.asPoint();
	}

}
