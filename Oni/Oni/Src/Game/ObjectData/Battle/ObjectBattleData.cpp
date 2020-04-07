#include "ObjectBattleData.hpp"
#include "../../../MyLibrary.hpp"


namespace Oni
{

	ObjectBattleData::ObjectBattleData(double hp)
		: mHp(hp)
		, mMaxHp(hp)
		, mInvincibleSecond(0)
		, mActionSecond(0)
		, mActionName(U"")
	{
		mActionMap[mActionName] = [](double){};
	}


	void ObjectBattleData::update()
	{
		mActionSecond     += Scene::DeltaTime();
		mInvincibleSecond -= Scene::DeltaTime();

		mActionMap[mActionName](mActionSecond);
	}


	void ObjectBattleData::changeAction(const String& name)
	{
		if (!mActionMap.count(name))
		{
			printDebug(U"[ObjectBattleData::changeAction]");
			printDebug(U"アクションが見つかりません.");
			printDebug(U"ファイル名 > " + name);
			return;
		}

		mActionName   = name;
		mActionSecond = 0;
	}

}
