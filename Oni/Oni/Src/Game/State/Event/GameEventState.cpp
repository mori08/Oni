#include "GameEventState.hpp"
#include "../../GameManager.hpp"


namespace Oni
{
	GameEventState::GameEventState(const String& eventName)
	{
		// �C�x���g�̎w��
		GameManager::instance().getEvent().jamp(eventName);
	}


	void GameEventState::update()
	{
		// �C�x���g�̍X�V
		GameManager::instance().getEvent().update();

		// �I�u�W�F�N�g�̍X�V
		for (auto& obj : GameManager::instance().getObjectList())
		{
			obj->updateEvent();
		}

		// y���W�Ń\�[�g
		GameManager::instance().getObjectList().sort([](GameObjectPtr& a, GameObjectPtr& b) { return *a < *b; });
	}


	void GameEventState::draw() const
	{
		GameManager::instance().getStage().draw(GameManager::instance().drawPos(Vec3::Zero()));

		// �I�u�W�F�N�g�̕`��
		for (const auto& obj : GameManager::instance().getObjectList())
		{
			obj->draw();
		}

		// �e�L�X�g�{�b�N�X�Ȃǂ̕`��
		GameManager::instance().getEvent().draw();
	}
}
