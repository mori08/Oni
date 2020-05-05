#include "GameEvent.hpp"
#include "../GameManager.hpp"
#include "../../MyLibrary.hpp"


namespace Oni
{

	GameEvent::GameEvent()
		: mEventName(U"")
		, mReadingRow(0)
		, mWaitSecond(0)
		, mError(false)
	{
		mData[mEventName] = Array<Array<String>>();

		// �e�C�x���g�̓o�^
		mEventFunc[U"Wait"] = [this]() { wait(); };
		mEventFunc[U"Move"] = [this]() { moveObject(); };
		mEventFunc[U"Act"]  = [this]() { actObject(); };
		mEventFunc[U"Text"] = [this]() { setText(); };
	}


	void GameEvent::load(const FilePath& dirName)
	{
		// �w�肳�ꂽ�f�B���N�g���̃t�@�C���p�X��z���
		Array<FilePath> contents = FileSystem::DirectoryContents(dirName, false);

		for (const auto& content : contents)
		{
			String fileName = FileSystem::FileName(content);

			// �w�肳�ꂽ�p�X���f�B���N�g���ł���Ƃ�
			if (FileSystem::IsDirectory(content))
			{
				load(dirName + fileName + U"/");
			}

			// �w�肳�ꂽ�p�X��csv�t�@�C���̂Ƃ�
			else if (FileSystem::IsFile(content) && FileSystem::Extension(content) == U"csv")
			{
				mData[FileSystem::BaseName(content)] = CSVData(dirName+fileName).getData();
			}

		}
	}


	void GameEvent::jamp(const String& eventName)
	{
		mReadingRow = 0;

		mEventName = mData.count(eventName) ? eventName : U"";
	}


	void GameEvent::update()
	{
		// �G���[�ŃX�g�b�v
		if (mError) { return; }

		// �҂�
		mWaitSecond -= Scene::DeltaTime();
		if (mWaitSecond > 0) { return; }

		// �e�L�X�g�{�b�N�X
		if (mTextBoard)
		{
			if (mTextBoard->selectedUpdate()) { mTextBoard = nullptr; }
			return;
		}

		// �ǂݍ��߂�s���܂����邩�m�F
		if (mReadingRow >= mData[mEventName].size()) { return; }
		
		// 0��ڂɑΉ����鏈�������邩�m�F
		if (!mEventFunc.count(mData[mEventName][mReadingRow][0]))
		{
			outputErrorMessage(U"update");
			return;
		}

		mEventFunc[mData[mEventName][mReadingRow][0]]();

		++mReadingRow;
	}


	void GameEvent::draw() const
	{
		if (mTextBoard)
		{
			mTextBoard->drawBoard();
			mTextBoard->draw();
		}
	}


	void GameEvent::outputErrorMessage(const String& funcName)
	{
		printDebug(U"[GameEvent::U" + funcName + U"]");
		printDebug(U"�C�x���g�t�@�C���Ɍ�肪����܂�.");
		printDebug(U"�C�x���g�� > " + mEventName);
		printDebug(U"�s > " + ToString(mReadingRow+1));
		mError = true;
	}


	void GameEvent::wait()
	{
		try
		{
			// �҂����Ԃ̎擾 (1���)
			mWaitSecond = Parse<double>(mData[mEventName][mReadingRow][1]);
		}
		catch (ParseError& e)
		{
			outputErrorMessage(U"wait");
			printDebug(e.what());
		}
	}


	void GameEvent::moveObject()
	{
		try
		{
			// �I�u�W�F�N�g�̖��O (1���)
			const String objName    = mData[mEventName][mReadingRow][1];

			// �ړ����� (2���)
			const double moveSecond = Parse<double>(mData[mEventName][mReadingRow][2]);

			// �ړ����x (3���)
			const Vec3   velocity   = Parse<Vec3>(mData[mEventName][mReadingRow][3]);

			auto objectPtr = GameManager::instance().getObject(objName);
			if (objectPtr && objectPtr.value()->getEventData())
			{
				objectPtr.value()->getCollider().setVelocity(Collider::X, velocity.x);
				objectPtr.value()->getCollider().setVelocity(Collider::Y, velocity.y);
				objectPtr.value()->getCollider().setVelocity(Collider::Z, velocity.z);
				objectPtr.value()->getEventData().value().setMoveSecond(moveSecond);
			}
			else
			{
				outputErrorMessage(U"moveObject");
				if (!objectPtr)
				{
					printDebug(U"�I�u�W�F�N�g " + objName + U" ���݂���܂���");
				}
				else if (!objectPtr.value()->getEventData())
				{
					printDebug(U"EventData�����݂��Ȃ��I�u�W�F�N�g�ł�");
				}
			}
		}
		catch (ParseError& e)
		{
			outputErrorMessage(U"moveObject");
			printDebug(e.what());
		}
	}

	void GameEvent::actObject()
	{
		// �I�u�W�F�N�g�̖��O (1���)
		const String objName = mData[mEventName][mReadingRow][1];

		// ���o�� (2���)
		const String actName = mData[mEventName][mReadingRow][2];

		auto objectPtr = GameManager::instance().getObject(objName);
		if (!objectPtr)
		{
			outputErrorMessage(U"actObject"); 
			printDebug(U"�I�u�W�F�N�g " + objName + U" ���݂���܂���"); 
			return;
		}

		if (!objectPtr.value()->getEventData())
		{
			outputErrorMessage(U"actObject");
			printDebug(U"EventData�����݂��Ȃ��I�u�W�F�N�g�ł�");
			return;
		}

		if (!objectPtr.value()->getEventData()->isExistAct(actName))
		{
			outputErrorMessage(U"actObject");
			printDebug(U"�I�u�W�F�N�g�̉��o " + actName + U" ���݂���܂���");
			return;
		}
		
		objectPtr.value()->getEventData()->act(actName);
	}


	void GameEvent::setText()
	{
		// �A�C�R���̉摜�� (1���)
		const String iconName    = mData[mEventName][mReadingRow][1];

		// �b����̖��O (2���)
		const String speakerName = mData[mEventName][mReadingRow][2];

		// �e�L�X�g (3���)
		const String text        = mData[mEventName][mReadingRow][3];

		mTextBoard = std::make_unique<TextBoard>(iconName, speakerName, text);
	}

}