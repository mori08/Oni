#include "TestGameObject.hpp"
#include "../../GameManager.hpp"


namespace
{
	// 初期座標
	constexpr Vec3 INIT_POS(100, 100, 0);
	// サイズ
	constexpr Vec3 OBJECT_SIZE(30, 10, 60);
	
	// 速さ
	constexpr double SPEED = 80;
	// 加速度
	constexpr Vec3 ACCEL(0, 0, -160);

	// ジャンプの速さ
	constexpr double JAMP_SPEED = 120;
}


namespace Oni
{

	TestGameObject::TestGameObject()
		: GameObject(INIT_POS, OBJECT_SIZE, ObjectType::PLAYER)
	{
		mAcceleration = ACCEL;
	}


	void TestGameObject::update()
	{
		Vec2 direction = Vec2::Zero();
		direction.x += KeyRight.pressed() - KeyLeft.pressed();
		direction.y += KeyDown .pressed() - KeyUp  .pressed();
		direction = direction.isZero() ? direction : (SPEED * direction.normalized());

		mVelocity.x = direction.x;
		mVelocity.y = direction.y;

		if (mIsOnGround&&KeyC.down())
		{
			mIsOnGround = false;
			mVelocity.z = JAMP_SPEED;
		}

		ClearPrint();
		if (mVelocity.z > 0)
		{
			Print << U"Jamp";
		}

		moveObject();
	}


	void TestGameObject::draw() const
	{
		RectF
		(
			GameManager::instance().drawPos(Vec3(mCollider.minPos().x, mCollider.centerPos().y, mCollider.maxPos().z)),
			OBJECT_SIZE.x, OBJECT_SIZE.z
		).draw(Color(240, 128)).drawFrame(5, 0, Color(240));

		checkDraw(Vec2(mCollider.minPos().x   , mCollider.centerPos().y));
		checkDraw(Vec2(mCollider.centerPos().x, mCollider.centerPos().y));
		checkDraw(Vec2(mCollider.maxPos().x   , mCollider.centerPos().y));
	}


	void TestGameObject::checkDraw(const Vec2& pos) const
	{
		Vec2 pos1 = GameManager::instance().drawPos(Vec3(pos, mCollider.minPos().z));
		Vec2 pos2 = GameManager::instance().drawPos(Vec3(pos, GameManager::instance().getTerrainHeight(pos)));
		Vec2 pos3 = GameManager::instance().drawPos(Vec3(pos, 0));

		Line(pos1, pos2).draw(1, Color(240));
		Line(pos2, pos3).draw(1, Color(240, 30));

		Circle(pos1, 3).draw(Color(240));
		Circle(pos2, 3).draw(Color(240));
		Circle(pos3, 3).draw(Color(240, 30));
	}

}
