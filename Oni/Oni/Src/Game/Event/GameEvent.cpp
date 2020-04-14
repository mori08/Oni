#include "GameEvent.hpp"
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

		mEventFunc[U"Wait"] = [this]() { wait(); };
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
		mWaitSecond -= Scene::DeltaTime();

		// �҂�
		if (mError && mWaitSecond > 0) { return; }

		// �ǂݍ��߂�s���܂����邩�m�F
		if (mReadingRow >= mData[mEventName].size()) { return; }
		
		// 0��ڂɑΉ����鏈�������邩�m�F
		if (!mEventFunc.count(mData[mEventName][mReadingRow][0]))
		{
			mError = true;
			outputErrorMessage(U"update");
			return;
		}

		mEventFunc[mData[mEventName][mReadingRow][0]]();

		++mReadingRow;
	}


	void GameEvent::draw() const
	{

	}


	void GameEvent::outputErrorMessage(const String& funcName) const
	{
		printDebug(U"[GameEvent::U" + funcName + U"]");
		printDebug(U"�C�x���g�t�@�C���Ɍ�肪����܂�.");
		printDebug(U"�C�x���g�� > " + mEventName);
		printDebug(U"�s > " + ToString(mReadingRow));
	}


	void GameEvent::wait()
	{
		try
		{
			// �҂����Ԃ̎擾
			mWaitSecond = Parse<double>(mData[mEventName][mReadingRow][1]);
		}
		catch (ParseError)
		{
			outputErrorMessage(U"wait");
		}
	}

}