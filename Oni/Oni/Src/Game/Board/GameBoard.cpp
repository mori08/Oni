#include "GameBoard.hpp"
#include "../../MyColor.hpp"


namespace
{
	// �E�B���h�E�̊p�̊ۂ݂̔��a
	constexpr int32 RADIUS = 3;

	// �E�B���h�E�̉��̌���
	constexpr double BOARD_THICK = 2.0;

	// �E�B���h�E�̐F
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