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
		// 指定されたディレクトリのファイルパスを配列に
		Array<FilePath> contents = FileSystem::DirectoryContents(dirName, false);

		for (const auto& content : contents)
		{
			String fileName = FileSystem::FileName(content);

			// 指定されたパスがディレクトリであるとき
			if (FileSystem::IsDirectory(content))
			{
				load(dirName + fileName + U"/");
			}

			// 指定されたパスがcsvファイルのとき
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

		// 待ち
		if (mError && mWaitSecond > 0) { return; }

		// 読み込める行がまだあるか確認
		if (mReadingRow >= mData[mEventName].size()) { return; }
		
		// 0列目に対応する処理があるか確認
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
		printDebug(U"イベントファイルに誤りがあります.");
		printDebug(U"イベント名 > " + mEventName);
		printDebug(U"行 > " + ToString(mReadingRow));
	}


	void GameEvent::wait()
	{
		try
		{
			// 待ち時間の取得
			mWaitSecond = Parse<double>(mData[mEventName][mReadingRow][1]);
		}
		catch (ParseError)
		{
			outputErrorMessage(U"wait");
		}
	}

}