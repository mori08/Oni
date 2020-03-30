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
				GameManager::instance().load();
				return SceneName::TITLE;
			}
		)
	{
	}

}
