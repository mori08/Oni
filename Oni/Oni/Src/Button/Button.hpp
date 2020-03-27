#pragma once


#include<Siv3D.hpp>


namespace Oni
{
	class Button;
	using ButtonPtr     = std::shared_ptr<Button>;
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

		// 隣接ボタン
		std::list<std::pair<Key, ButtonPtr>> mAdjacentButtonMap;

		// 押されたときの処理
		ButtonOnClick mOnClick;

	public:

		/// <summary>
		/// ボタン
		/// </summary>
		/// <param name="name">   名前 </param>
		/// <param name="region"> 範囲 </param>
		Button(const String& name, const Rect& region)
			: mName(name)
			, mRegion(region)
			, mOnClick([](){})
		{
		}

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
		/// 隣接するボタンの設定
		/// </summary>
		/// <param name="key"      > 対応するキー   </param>
		/// <param name="buttonPtr"> 隣接するボタン </param>
		void setAdjacentButton(const Key& key, ButtonPtr buttonPtr)
		{
			mAdjacentButtonMap.emplace_back(key, buttonPtr);
		}

		/// <summary>
		/// 入力に応じた隣接ボタンの取得
		/// </summary>
		/// <returns>
		/// 入力に応じた隣接ボタン
		/// </returns>
		Optional<ButtonPtr> getAdjacentButton() const;

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