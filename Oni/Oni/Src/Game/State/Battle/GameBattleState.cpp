#include "GameBattleState.hpp"
#include "../../GameManager.hpp"


namespace Oni
{

	GameBattleState::GameBattleState()
	{
	}


	void GameBattleState::update()
	{
		// オブジェクトの更新
		for (auto& obj : GameManager::instance().getObjectList())
		{
			obj->updateBattle();
		}

		// 他オブジェクトの判定
		for (auto objA = GameManager::instance().getObjectList().begin(); objA != GameManager::instance().getObjectList().end(); ++objA)
		{
			for (auto objB = objA; objB != GameManager::instance().getObjectList().end(); ++objB)
			{
				(*objA)->passAnother(**objB);
				(*objB)->passAnother(**objA);
			}
		}

		// y座標でソート
		std::sort(GameManager::instance().getObjectList().begin(), GameManager::instance().getObjectList().end(), [](auto a, auto b) {return *a < *b; });
	}


	void GameBattleState::draw() const
	{
		// 地形の描画
		GameManager::instance().getStage().draw(GameManager::instance().drawPos(Vec3::Zero()));

		// オブジェクトの更新
		for (const auto& obj : GameManager::instance().getObjectList())
		{
			obj->draw();
		}
	}

}
