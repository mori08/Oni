#include "TitleScene.hpp"
#include "../MyColor.hpp"
#include "../MyLibrary.hpp"
#include "../Button/ButtonManager.hpp"


namespace
{
	// ボタンのサイズ
	constexpr Size BUTTON_SIZE(150, 30);
	// 「はじめから」ボタン
	const Oni::Button NEWGAME_BUTTON (U"はじめから", Oni::getRectFromCenter(Point(320, 300), BUTTON_SIZE));
	// 「つづきから」ボタン
	const Oni::Button CONTINUE_BUTTON(U"つづきから", Oni::getRectFromCenter(Point(320, 380), BUTTON_SIZE));
	// ボタンのリスト
	const Array<Oni::Button> BUTTON_LIST
	{
		NEWGAME_BUTTON,
		CONTINUE_BUTTON
	};

	// カーソル移動の比
	constexpr double CURSOR_RATE = 0.005;
}


namespace Oni
{

	TitleScene::TitleScene(const InitData& init)
		: IScene(init)
		, mCursor(CONTINUE_BUTTON.getRegion())
	{
		// ボタンのリセット
		ButtonManager::instance().clearButtonList();

		// ボタンの設定
		ButtonManager::instance().registerButton(NEWGAME_BUTTON);
		ButtonManager::instance().registerButton(CONTINUE_BUTTON);

		// ボタンの位置関係の設定
		ButtonManager::instance().setVerticalAdjacentButton(NEWGAME_BUTTON.getName(), CONTINUE_BUTTON.getName());

		// ボタンを押したときの処理の設定
		ButtonManager::instance().setOnClick
		(
			NEWGAME_BUTTON.getName(),
			[this]() { changeScene(SceneName::TEST_LOAD); }
		);

		// 選択中のボタンの設定
		ButtonManager::instance().setSelectedButton(CONTINUE_BUTTON.getName());
	}


	void TitleScene::update()
	{
		// カーソルの移動
		internalDividingPoint
		(
			mCursor.pos,
			ButtonManager::instance().getSelectedButton().getRegion().pos,
			CURSOR_RATE
		);

		// ボタンの更新
		ButtonManager::instance().update();

		changeScene(SceneName::TEST_LOAD);
	}


	void TitleScene::draw() const
	{
		TextureAsset(U"Title").draw();

		// ボタンとカーソルの描画
		mCursor.draw(MyWhite);
		for (const auto& button : BUTTON_LIST)
		{
			Color color = (button.getName() == ButtonManager::instance().getSelectedButton().getName())
				? MyBlack
				: MyWhite;

			FontAsset(U"20")(button.getName()).drawAt(button.getRegion().center(), color);
		}
	}

}
