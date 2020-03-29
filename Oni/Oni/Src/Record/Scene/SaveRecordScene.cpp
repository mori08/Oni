#include "SaveRecordScene.hpp"
#include "../RecordManager.hpp"


namespace Oni
{

	SaveRecordScene::SaveRecordScene(const InitData& init)
		: LoadScene
		(
			init,
			[]()
			{
				RecordManager::instance().save();
				return SceneName::TITLE;
			}
		)
	{
	}

}
