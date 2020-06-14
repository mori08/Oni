#include "GameObject.hpp"
#include "../GameManager.hpp"
#include "../../MyColor.hpp"


namespace Oni
{

	GameObject::GameObject(const String& name, const Collider& collider, const ObjectType& type, const SliceTexture& slide)
		: mName(name)
		, mCollider(collider)
		, mType(type)
		, mSlide(slide)
		, mIsHiding(true)
		, mEventData(none)
	{

	}


	void GameObject::updateEvent()
	{
		if (mEventData)
		{
			mEventData->update();
			if (!mEventData->isMoving()) 
			{
				mCollider.setVelocity(Collider::X, 0);
				mCollider.setVelocity(Collider::Y, 0);
				mCollider.setVelocity(Collider::Z, 0);
			}
			mCollider.update();
		}
		
		mSlide.update();
	}


	void GameObject::draw() const
	{
		if (!mIsHiding) { return; }

		mSlide.getTexture().draw(getDrawTexturePoint());
	}


	bool GameObject::eraseAble() const
	{
		return false;
	}


	void GameObject::drawCollider() const
	{
		const Vec3 m = mCollider.minPos();
		const Vec3 M = mCollider.maxPos();
		const Vec3 s = mCollider.size();

		RectF(GameManager::instance().drawPos(Vec3(m.x, m.y, M.z)), s.x, s.y).drawFrame(1, Palette::Red);
		RectF(GameManager::instance().drawPos(Vec3(m.x, M.y, M.z)), s.x, s.z).drawFrame(1, Palette::Red);
		RectF(GameManager::instance().drawPos(Vec3(m.x, m.y, m.z)), s.x, s.y).drawFrame(1, Palette::Red);
	}


	Point GameObject::getDrawTexturePoint() const
	{
		Vec2 rtn = GameManager::instance().drawPos(mCollider.centerPos());
		
		rtn.x +=                        - mSlide.getSliceSize().x / 2;
		rtn.y += mCollider.size().z / 2 - mSlide.getSliceSize().y;
		
		return rtn.asPoint();
	}

}
