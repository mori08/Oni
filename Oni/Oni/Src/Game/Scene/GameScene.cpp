#include "GameScene.hpp"
#include "../GameManager.hpp"


namespace Oni
{

	GameScene::GameScene(const InitData& init)
		: IScene(init)
	{
	}

	void GameScene::update()
	{
	}

	void GameScene::draw() const
	{
		GameManager::instance().draw();
	}

}