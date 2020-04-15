#include "StageSupport.hpp"
#include "../../MyColor.hpp"


namespace Oni
{

	void StageSupport::setStageSize(const Size& size)
	{
		mStageSize = size;
		mHeight = Array<Array<int32>>(size.x, Array<int32>(size.y));
		mSlope  = Array<Array<int32>>(size.x, Array<int32>(size.y));
	}


	double StageSupport::height(const Vec2& pixel) const
	{
		// マス座標に変換
		const Point square = Floor(pixel / Vec2(SQUARE_X, SQUARE_Y)).asPoint();

		// ステージ外は高さInf
		if (square.x < 0 || square.x >= mStageSize.x) { return Inf<double>; }
		if (square.y < 0 || square.y >= mStageSize.y) { return Inf<double>; }

		const double slopeRate = (pixel.x - SQUARE_X * square.x) / SQUARE_X;

		return SQUARE_Z*(mHeight[square.x][square.y] + mSlope[square.x][square.y] * slopeRate);
	}


	double StageSupport::height(const std::pair<double, double>& x, double y) const
	{
		double maxHeight = Max(
			height(Vec2(x.first, y)),
			height(Vec2(x.second, y))
		);

		double border = Floor(x.first / SQUARE_X) * SQUARE_X + SQUARE_X;

		for (; border < x.second; border += SQUARE_X)
		{
			maxHeight = Max(maxHeight, height(Vec2(border - 1, y)));
			maxHeight = Max(maxHeight, height(Vec2(border + 1, y)));
		}

		return maxHeight;
	}


	void StageSupport::draw(const Vec2& cameraPos) const
	{
#ifdef _DEBUG

		static Vec2 checkPos = Vec2::Zero();

		for (int32 y : Range(0, mStageSize.y - 1))
		{
			for (int32 x : Range(0, mStageSize.x - 1))
			{
				Point drawPoint
					= cameraPos.asPoint()
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
