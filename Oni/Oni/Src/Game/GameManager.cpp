#include "GameManager.hpp"
#include "../MyLibrary.hpp"
#include "../MyColor.hpp"


namespace
{
	// �`��̊�_
	constexpr Point DRAW_BASE_POS;
}


namespace Oni
{

	bool GameManager::load()
	{
		const FilePath filePath = U"Asset/Data/Game/TestStage.csv";

		// CSV�t�@�C���̊m�F
		CSVData csv(filePath);
		if (!csv)
		{
			printDebug(U"CSV�t�@�C����ǂݍ��߂܂���");
			printDebug(U"�t�@�C���� > " + filePath);
			return false;
		}

		int32 readingRow = 0;

		// �X�e�[�W�̑傫���̐ݒ�
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
