#include "GameEventState.hpp"
#include "../../GameManager.hpp"


namespace Oni
{
	GameEventState::GameEventState(const String& eventName)
	{
		// イベントの指定
		GameManager::instance().getEvent().jamp(eventName);
	}


	void GameEventState::update()
	{
		// イベントの更新
		GameManager::instance().getEvent().update();

		// オブジェクトの更新
		for (auto& obj : GameManager::instance().getObjectList())
		{
			obj->updateEvent();
		}

		// y座標でソート
		GameManager::instance().getObjectList().sort([](GameObjectPtr& a, GameObjectPtr& b) { return *a < *b; });
	}


	void GameEventState::draw() const
	{
		GameManager::instance().getStage().draw(GameManager::instance().drawPos(Vec3::Zero()));

		// オブジェクトの描画
		for (const auto& obj : GameManager::instance().getObjectList())
		{
			obj->draw();
		}

		// テキストボックスなどの描画
		GameManager::instance().getEvent().draw();
	}
}
