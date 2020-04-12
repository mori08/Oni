#include "GameBattleState.hpp"
#include "../../GameManager.hpp"


namespace Oni
{

	GameBattleState::GameBattleState()
	{
	}


	void GameBattleState::update()
	{
		// �I�u�W�F�N�g�̍X�V
		for (auto& obj : GameManager::instance().getObjectList())
		{
			obj->updateBattle();
		}

		// ���I�u�W�F�N�g�̔���
		for (auto objA = GameManager::instance().getObjectList().begin(); objA != GameManager::instance().getObjectList().end(); ++objA)
		{
			for (auto objB = objA; objB != GameManager::instance().getObjectList().end(); ++objB)
			{
				(*objA)->passAnother(**objB);
				(*objB)->passAnother(**objA);
			}
		}

		// y���W�Ń\�[�g
		std::sort(GameManager::instance().getObjectList().begin(), GameManager::instance().getObjectList().end(), [](auto a, auto b) {return *a < *b; });
	}


	void GameBattleState::draw() const
	{
		// �n�`�̕`��
		GameManager::instance().getStage().draw(GameManager::instance().drawPos(Vec3::Zero()));

		// �I�u�W�F�N�g�̍X�V
		for (const auto& obj : GameManager::instance().getObjectList())
		{
			obj->draw();
		}
	}

}
