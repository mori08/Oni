#pragma once


#include<Siv3D.hpp>


namespace Oni
{
	using ButtonOnClick = std::function<void()>;

	/// <summary>
	/// ボタン
	/// 主にButtonManagerで使用する
	/// </summary>
	class Button
	{
	private:

		// 名前
		const String mName;

		// 範囲
		const Rect mRegion;

		// 押されたときの処理
		ButtonOnClick mOnClick;

	public:

		/// <summary>
		/// ボタンの名前の取得
		/// </summary>
		/// <returns> ボタンの名前 </returns>
		const String& getName() const
		{
			return mName;
		}

		/// <summary>
		/// ボタンの範囲の取得
		/// </summary>
		/// <returns> ボタンの名前 </returns>
		const Rect& getRegion() const
		{
			return mRegion;
		}

		/// <summary>
		/// 押したときの処理の設定
		/// </summary>
		/// <param name="onClick"> 押したときの処理 </param>
		void setOnClick(const ButtonOnClick& onClick)
		{
			mOnClick = onClick;
		}

		/// <summary>
		/// 押したときの処理
		/// </summary>
		void OnClick() const
		{
			mOnClick();
		}

	};
}