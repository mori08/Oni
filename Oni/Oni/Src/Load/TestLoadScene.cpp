#include "TestLoadScene.hpp"


namespace Oni
{

	TestLoadScene::TestLoadScene(const InitData& init)
		: LoadScene
		(
			init,
			[]()
			{
				std::this_thread::sleep_for(std::chrono::seconds(3));
				return SceneName::TITLE;
			}
		)
	{
	}

}
