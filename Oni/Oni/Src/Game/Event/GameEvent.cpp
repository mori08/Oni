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

		// 各イベントの登録
		mEventFunc[U"Wait"] = [this]() { wait(); };
		mEventFunc[U"Move"] = [this]() { moveObject(); };
		mEventFunc[U"Act"]  = [this]() { actObject(); };
		mEventFunc[U"Text"] = [this]() { setText(); };
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
		// エラーでストップ
		if (mError) { return; }

		// 待ち
		mWaitSecond -= Scene::DeltaTime();
		if (mWaitSecond > 0) { return; }

		// テキストボックス
		if (mTextBoard)
		{
			if (mTextBoard->selectedUpdate()) { mTextBoard = nullptr; }
			return;
		}

		// 読み込める行がまだあるか確認
		if (mReadingRow >= mData[mEventName].size()) { return; }
		
		// 0列目に対応する処理があるか確認
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
		printDebug(U"イベントファイルに誤りがあります.");
		printDebug(U"イベント名 > " + mEventName);
		printDebug(U"行 > " + ToString(mReadingRow+1));
		mError = true;
	}


	void GameEvent::wait()
	{
		try
		{
			// 待ち時間の取得 (1列目)
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
			// オブジェクトの名前 (1列目)
			const String objName    = mData[mEventName][mReadingRow][1];

			// 移動時間 (2列目)
			const double moveSecond = Parse<double>(mData[mEventName][mReadingRow][2]);

			// 移動速度 (3列目)
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
					printDebug(U"オブジェクト " + objName + U" がみつかりません");
				}
				else if (!objectPtr.value()->getEventData())
				{
					printDebug(U"EventDataが存在しないオブジェクトです");
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
		// オブジェクトの名前 (1列目)
		const String objName = mData[mEventName][mReadingRow][1];

		// 演出名 (2列目)
		const String actName = mData[mEventName][mReadingRow][2];

		auto objectPtr = GameManager::instance().getObject(objName);
		if (!objectPtr)
		{
			outputErrorMessage(U"actObject"); 
			printDebug(U"オブジェクト " + objName + U" がみつかりません"); 
			return;
		}

		if (!objectPtr.value()->getEventData())
		{
			outputErrorMessage(U"actObject");
			printDebug(U"EventDataが存在しないオブジェクトです");
			return;
		}

		if (!objectPtr.value()->getEventData()->isExistAct(actName))
		{
			outputErrorMessage(U"actObject");
			printDebug(U"オブジェクトの演出 " + actName + U" がみつかりません");
			return;
		}
		
		objectPtr.value()->getEventData()->act(actName);
	}


	void GameEvent::setText()
	{
		// アイコンの画像名 (1列目)
		const String iconName    = mData[mEventName][mReadingRow][1];

		// 話し手の名前 (2列目)
		const String speakerName = mData[mEventName][mReadingRow][2];

		// テキスト (3列目)
		const String text        = mData[mEventName][mReadingRow][3];

		mTextBoard = std::make_unique<TextBoard>(iconName, speakerName, text);
	}

}