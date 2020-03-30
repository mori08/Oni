#include "GameManager.hpp"
#include "../MyLibrary.hpp"
#include "../MyColor.hpp"


namespace
{
	// 描画の基準点
	constexpr Point DRAW_BASE_POS(0, 240);
}


namespace Oni
{
	GameManager::GameManager()
	{
	}


	bool GameManager::load()
	{
		const FilePath filePath = U"Asset/Data/Game/TestStage.csv";

		// CSVファイルの確認
		CSVData csv(filePath);
		if (!csv)
		{
			printDebug(U"[AdventureManager::load]");
			printDebug(U"CSVファイルを読み込めません");
			printDebug(U"ファイル名 > " + filePath);
			return false;
		}

		int32 readingRow = 0;

		// ステージの大きさの設定
		try
		{
			mStageSize = Parse<Point>(csv[readingRow][0]);
			mHeight = Array<Array<int32>>(mStageSize.x, Array<int32>(mStageSize.y));
			mSlope = Array<Array<int32>>(mStageSize.x, Array<int32>(mStageSize.y));
			++readingRow;
		}
		catch (const ParseError&)
		{
			printDebug(U"[AdventureManager::load]");
			printDebug(U"座標に変換できません");
			printDebug(U"row > " + ToString(readingRow));
			return false;
		}

		// ステージの高さの設定
		for (int32 y : Range(0, mStageSize.y - 1))
		{
			for (int32 x : Range(0, mStageSize.x - 1))
			{
				try
				{
					mHeight[x][y] = Parse<int32>(csv[readingRow][x]);
				}
				catch (const ParseError&)
				{
					printDebug(U"[AdventureManager::load]");
					printDebug(U"整数値に変換できません");
					printDebug(U"row > "    + ToString(readingRow));
					printDebug(U"column > " + ToString(x));
					return false;
				}
			}
			++readingRow;
		}

		// ステージの傾斜の設定
		for (int32 y : Range(0, mStageSize.y - 1))
		{
			for (int32 x : Range(0, mStageSize.x - 1))
			{
				try
				{
					mSlope[x][y] = Parse<int32>(csv[readingRow][x]);
				}
				catch (const ParseError&)
				{
					printDebug(U"[AdventureManager::load]");
					printDebug(U"整数値に変換できません");
					printDebug(U"row > "    + ToString(readingRow));
					printDebug(U"column > " + ToString(x));
					return false;
				}
			}
			++readingRow;
		}

		return true;
	}


	void GameManager::draw() const
	{
		drawTerrain();
	}


	void GameManager::drawTerrain() const
	{
		for (int32 y : Range(0, mStageSize.y - 1))
		{
			for (int32 x : Range(0, mStageSize.x - 1))
			{
				Point drawPoint
					= DRAW_BASE_POS
					+ Point(SQUARE_X, SQUARE_Y) * Point(x, y)
					+ mHeight[x][y] * SQUARE_Z * Point::Up()
					+ mSlope[x][y] * SQUARE_Z * Point::Up() / 2;
				
				Rect(drawPoint, Point(SQUARE_X, SQUARE_Y) * Point::One())
					.shearedY(-mSlope[x][y] * SQUARE_Z / 2)
					.draw(Color(90))
					.drawFrame(2, MyWhite);
			}
		}
	}

}
