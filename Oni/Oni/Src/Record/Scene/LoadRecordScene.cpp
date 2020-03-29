#include "LoadRecordScene.hpp"
#include "../RecordManager.hpp"


namespace Oni
{

	LoadRecordScene::LoadRecordScene(const InitData& init)
		: LoadScene
		(
			init,
			[]()
			{
				// レコードの読み込み
				auto mLoadResult = RecordManager::instance().load();

				// シーン遷移先の指定
				switch (mLoadResult)
				{
				case RecordManager::LoadResult::NEW_GAME:
					return SceneName::TITLE;

				case RecordManager::LoadResult::CONTINUE:
					return SceneName::TITLE;
				}
				return SceneName::TITLE;
			}
		)
	{
	}

}
