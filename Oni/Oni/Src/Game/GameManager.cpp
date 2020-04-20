#include "GameManager.hpp"
#include "../MyLibrary.hpp"
#include "../MyColor.hpp"

// ���
#include "State/Battle/GameBattleState.hpp"
#include "State/Event/GameEventState.hpp"

// �I�u�W�F�N�g
#include "Object/Player/PlayerObject.hpp"
#include "Object/GhostGirl/GhostGirlObject.hpp"


namespace
{
	// �`��̊�_
	constexpr Point DRAW_BASE_POS(0, 240);
}


namespace Oni
{

	GameManager::GameManager()
	{
		mState = std::make_unique<GameBattleState>();
	}


	bool GameManager::load()
	{
		const FilePath filePath = U"Asset/Data/Stage/TestStage.csv";

		// CSV�t�@�C���̊m�F
		CSVData csv(filePath);
		if (!csv)
		{
			printDebug(U"[AdventureManager::load]");
			printDebug(U"CSV�t�@�C����ǂݍ��߂܂���");
			printDebug(U"�t�@�C���� > " + filePath);
			return false;
		}

		int32 readingRow = 0;
		Size stageSize;

		// �X�e�[�W�̑傫���̐ݒ�
		try
		{
			stageSize = Parse<Point>(csv[readingRow][0]);
			mStageSupport.setStageSize(stageSize);
			++readingRow;
		}
		catch (const ParseError&)
		{
			printDebug(U"[AdventureManager::load]");
			printDebug(U"���W�ɕϊ��ł��܂���");
			printDebug(U"row > " + ToString(readingRow));
			return false;
		}

		// �X�e�[�W�̍����̐ݒ�
		for (int32 y : Range(0, stageSize.y - 1))
		{
			for (int32 x : Range(0, stageSize.x - 1))
			{
				try
				{
					mStageSupport.setHeight(x, y, Parse<int32>(csv[readingRow][x]));
				}
				catch (const ParseError&)
				{
					printDebug(U"[AdventureManager::load]");
					printDebug(U"�����l�ɕϊ��ł��܂���");
					printDebug(U"row > "    + ToString(readingRow));
					printDebug(U"column > " + ToString(x));
					return false;
				}
			}
			++readingRow;
		}

		// �X�e�[�W�̌X�΂̐ݒ�
		for (int32 y : Range(0, stageSize.y - 1))
		{
			for (int32 x : Range(0, stageSize.x - 1))
			{
				try
				{
					mStageSupport.setSlope(x, y, Parse<int32>(csv[readingRow][x]));
				}
				catch (const ParseError&)
				{
					printDebug(U"[AdventureManager::load]");
					printDebug(U"�����l�ɕϊ��ł��܂���");
					printDebug(U"row > "    + ToString(readingRow));
					printDebug(U"column > " + ToString(x));
					return false;
				}
			}
			++readingRow;
		}

		mObjectList.emplace_back(std::make_shared<PlayerObject>(Vec3(100, 100, 0)));
		for (const auto& object : mObjectList)
		{
			mObjectNameMap[object->getName()] = object;
		}
		mState = std::make_unique<GameEventState>(U"TestEvent");

		return true;
	}


	void GameManager::update()
	{
		mState->update();
	}


	void GameManager::draw() const
	{
		mState->draw();
	}


	Vec2 GameManager::drawPos(const Vec3& pos)
	{
		return DRAW_BASE_POS + Vec2(pos.x, pos.y - pos.z);
	}


	Optional<GameObjectPtr> GameManager::getObject(const String& objName)
	{
		if (mObjectNameMap.count(objName)) { return mObjectNameMap[objName]; }
		return none;
	}

}
