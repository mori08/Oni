#include "ObjectEventData.hpp"


namespace Oni
{

	ObjectEventData::ObjectEventData(SliceTexture& slide)
		: mMoveSecond(0)
	{
		mActMap[U"Mirror"] = [&slide](){ slide.mirror(); };
	}


	void ObjectEventData::update()
	{
		mMoveSecond -= Scene::DeltaTime();
	}

}
