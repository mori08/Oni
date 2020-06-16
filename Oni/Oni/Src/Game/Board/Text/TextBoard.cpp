#include "TextBoard.hpp"
#include "../../../Button/ButtonManager.hpp"


namespace
{
	// 一文字を描画するのにかける時間
	constexpr double ONE_CHAR_DRAW_SPAN = 0.1;

	// 範囲
	constexpr Rect REGION(0, 0, 640, 120);

	// アイコンを描画する座標
	constexpr Point ICON_DRAW_POS(16, 16);

	// 話し手の名前を描画する座標
	constexpr Point SPEAKER_DRAW_POS(60, 25);

	// テキストを表示する座標
	constexpr Point DRAW_TEXT_POS(136, 16);
}


namespace Oni
{

	TextBoard::TextBoard(const String& iconName, const String& speakerName, const String& text)
		: GameBoard(REGION)
		, mDrawAbleLength(text.size()* ONE_CHAR_DRAW_SPAN, text.size())
		, mIconName(iconName)
		, mSpeakerName(speakerName)
		, mText(text)
	{
	}


	void TextBoard::select()
	{

	}


	void TextBoard::update()
	{

	}


	bool TextBoard::selectedUpdate()
	{
		const bool isEnd = mDrawAbleLength.update();

		if (ButtonManager::ok())
		{
			if (isEnd) { return true; }

			mDrawAbleLength.toEndPoint();
		}

		return false;
	}


	void TextBoard::draw() const
	{
		if (mIconName != U"")
		{
			TextureAsset(mIconName).draw(ICON_DRAW_POS);
		}

		FontAsset(U"20")(mSpeakerName).drawAt(SPEAKER_DRAW_POS);

		FontAsset(U"20")(mText.substr(0, mDrawAbleLength.getValue())).draw(DRAW_TEXT_POS);
	}

}
