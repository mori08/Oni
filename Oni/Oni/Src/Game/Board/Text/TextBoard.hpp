#pragma once


#include "../GameBoard.hpp"
#include "../../../Slice/Linearly.hpp"


namespace Oni
{
	/// <summary>
	/// テキストを表示するウィンドウ
	/// </summary>
	/// <remarks>
	/// ポリモーフィズムを使わずイベントでも使用
	/// </remarks>
	class TextBoard : public GameBoard
	{
	private:

		// 表示文字数
		Linearly<size_t> mDrawAbleLength;

		// アイコンの画像名
		const String mIconName;

		// 話し手の名前
		const String mSpeakerName;

		// テキスト
		const String mText;

	public:

		/// <summary>
		/// テキストウィンドウ
		/// </summary>
		/// <param name="iconName"   > アイコンの画像名 </param>
		/// <param name="speakerName"> 話し手の名前     </param>
		/// <param name="text"       > テキスト         </param>
		TextBoard(const String& iconName, const String& speakerName, const String& text);

		void select() override;

		void update() override;

		bool selectedUpdate() override;

		void draw() const override;

	};
}