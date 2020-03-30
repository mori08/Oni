#include "GameManager.hpp"
#include "../MyLibrary.hpp"
#include "../MyColor.hpp"


namespace
{
	// 描画の基準点
	constexpr Point DRAW_BASE_POS;
}


namespace Oni
{

	bool GameManager::load()
	{
		const FilePath filePath = U"Asset/Data/Game/TestStage.csv";

		// CSVファイルの確認
		CSVData csv(filePath);
		if (!csv)
		{
			printDebug(U"CSVファイルを読み込めません");
			printDebug(U"ファイル名 > " + filePath);
			return false;
		}

		int32 readingRow = 0;

		// ステージの大きさの設定
		mStageSize = Parse<Point>(csv[readingRow][0]);
		mHeight = Array<Array<int32>>(mStageSize.x, Array<int32>(mStageSize.y));
		mSlope  = Array<Array<int32>>(mStageSize.x, Array<int32>(mStageSize.y));
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
				Rect(SQUARE_SIZE * Point(x, y), SQUARE_SIZE * Point::One())
					.draw(MyBlack)
					.drawFrame(2, MyWhite);
			}
		}
	}

}
