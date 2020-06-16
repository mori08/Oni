#include "TextBoard.hpp"
#include "../../../Button/ButtonManager.hpp"


namespace
{
	// �ꕶ����`�悷��̂ɂ����鎞��
	constexpr double ONE_CHAR_DRAW_SPAN = 0.1;

	// �͈�
	constexpr Rect REGION(0, 0, 640, 120);

	// �A�C�R����`�悷����W
	constexpr Point ICON_DRAW_POS(16, 16);

	// �b����̖��O��`�悷����W
	constexpr Point SPEAKER_DRAW_POS(60, 25);

	// �e�L�X�g��\��������W
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
