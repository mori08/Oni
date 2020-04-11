#include "GameManager.hpp"
#include "../MyLibrary.hpp"
#include "../MyColor.hpp"

#include "Object/Player/PlayerObject.hpp"
#include "Object/GhostGirl/GhostGirlObject.hpp"


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

		mObjectList.emplace_back(std::make_shared<PlayerObject>(Vec3(100, 100, 100)));
		mObjectList.emplace_back(std::make_shared<GhostGirlObject>(Vec3(100, 100, 100)));

		return true;
	}


	void GameManager::update()
	{
		// 各オブジェクトの更新
		for (auto& object : mObjectList)
		{
			object->updateBattle();
		}

		// 判定の確認
		for (auto objA = mObjectList.begin(); objA != mObjectList.end(); ++objA)
		{
			auto objB = objA;
			while (++objB != mObjectList.end())
			{
				(*objA)->passAnother(**objB);
				(*objB)->passAnother(**objA);
			}
		}

		// y座標でソート
		std::sort(mObjectList.begin(), mObjectList.end(), [](auto a, auto b) {return *a < *b; });
	}


	void GameManager::draw() const
	{
		drawTerrain();

		for (const auto& object : mObjectList)
		{
			object->draw();
		}
	}


	Vec2 GameManager::drawPos(const Vec3& pos)
	{
		return DRAW_BASE_POS + Vec2(pos.x, pos.y - pos.z);
	}


	double GameManager::getTerrainHeight(const Vec2& pixel) const
	{
		const Point square = Floor(pixel / Vec2(SQUARE_X, SQUARE_Y)).asPoint();

		if (square.x < 0 || square.x >= mStageSize.x) { return Inf<double>; }
		if (square.y < 0 || square.y >= mStageSize.y) { return Inf<double>; }

		const double slopeRate = (pixel.x - SQUARE_X * square.x) / SQUARE_X;

		return SQUARE_Z *
			(
				mHeight[square.x][square.y]
				+ mSlope[square.x][square.y] * slopeRate
			);
	}


	double GameManager::getTerrainHeight(const std::pair<double, double>& x, double y) const
	{
		double maxHeight = Max(
			getTerrainHeight(Vec2(x.first , y)),
			getTerrainHeight(Vec2(x.second, y))
		);

		double border = Floor(x.first / SQUARE_X) * SQUARE_X + SQUARE_X;

		for (; border < x.second; border += SQUARE_X)
		{
			maxHeight = Max(maxHeight, getTerrainHeight(Vec2(border - 1, y)));
			maxHeight = Max(maxHeight, getTerrainHeight(Vec2(border + 1, y)));
		}

		return maxHeight;
	}


	void GameManager::drawTerrain() const
	{
#ifdef _DEBUG

		static Vec2 checkPos = Vec2::Zero();

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

#endif // _DEBUG
	}

}
