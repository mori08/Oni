#include "LoadGameScene.hpp"
#include "../GameManager.hpp"


namespace Oni
{

	LoadGameScene::LoadGameScene(const InitData& init)
		: LoadScene
		(
			init,
			[]()
			{
				if (GameManager::instance().load()) { return SceneName::GAME; }
				return SceneName::TITLE;
			}
		)
	{
	}

}
