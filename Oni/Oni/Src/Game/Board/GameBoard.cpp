#include "GameBoard.hpp"
#include "../../MyColor.hpp"


namespace
{
	// ウィンドウの角の丸みの半径
	constexpr int32 RADIUS = 3;

	// ウィンドウの縁の厚さ
	constexpr double BOARD_THICK = 2.0;

	// ウィンドウの色
	constexpr Color BOARD_COLOR(Oni::MyBlack, 200);
}


namespace Oni
{

	GameBoard::GameBoard(const Rect& region)
		: mRegion(region, RADIUS)
	{

	}


	void GameBoard::drawBoard() const
	{
		mRegion
			.draw(BOARD_COLOR)
			.drawFrame(BOARD_THICK, MyWhite);
	}

}