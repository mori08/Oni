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
				// ���R�[�h�̓ǂݍ���
				auto mLoadResult = RecordManager::instance().load();

				// �V�[���J�ڐ�̎w��
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
