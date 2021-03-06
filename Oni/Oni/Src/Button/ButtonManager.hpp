#pragma once


#include"Button.hpp"


namespace Oni
{
	/// <summary>
	/// Buttonの管理選択
	/// </summary>
	class ButtonManager
	{
	private:

		// ボタンの配列(ボタンの名前をキー)
		std::unordered_map<String, ButtonPtr> mButtonMap;

		// 選択中のボタン
		ButtonPtr mSelectedButtonPtr;

	private:

		ButtonManager();

		ButtonManager(const ButtonManager&)            = default;
		ButtonManager& operator=(const ButtonManager&) = default;
		ButtonManager(ButtonManager&&)                 = default;
		ButtonManager& operator=(ButtonManager&&)      = default;

	public:

		/// <summary>
		/// インスタンスの取得
		/// </summary>
		/// <returns> インスタンス </returns>
		static ButtonManager& instance()
		{
			static ButtonManager buttonManager;
			return buttonManager;
		}

		/// <summary>
		/// ボタンの登録
		/// </summary>
		/// <param name="name"  > ボタンの名前 </param>
		/// <param name="region"> ボタンの範囲 </param>
		void registerButton(const String& name, const Rect& region);

		/// <summary>
		/// ボタンの登録
		/// </summary>
		/// <param name="button"> ボタン </param>
		void registerButton(const Button& button);

		/// <summary>
		/// ボタンの垂直方向の隣接関係の設定
		/// </summary>
		/// <param name="upName">   上側のボタンの名前 </param>
		/// <param name="downName"> 下側のボタンの名前 </param>
		void setVerticalAdjacentButton(const String& upName, const String& downName);

		/// <summary>
		/// ボタンの水平方向の隣接関係の設定
		/// </summary>
		/// <param name="leftName">  左側のボタンの名前 </param>
		/// <param name="rightName"> 右側のボタンの名前 </param>
		void setHorizontalAdjacentButton(const String& leftName, const String& rightName);

		/// <summary>
		/// 選択中のボタンの変更
		/// </summary>
		/// <param name="name"> ボタンの名前 </param>
		void setSelectedButton(const String& name);

		/// <summary>
		/// ボタンを押したときの処理の設定
		/// </summary>
		/// <param name="name"   > ボタンの名前     </param>
		/// <param name="onClick"> 押したときの処理 </param>
		void setOnClick(const String& name, ButtonOnClick onClick);

		/// <summary>
		/// 選択中のボタンの取得
		/// </summary>
		/// <returns>
		/// 選択中のボタン
		/// </returns>
		const Button& getSelectedButton() const
		{
			return *mSelectedButtonPtr;
		}

		/// <summary>
		/// ボタンのリストを空にします
		/// </summary>
		void clearButtonList();

		/// <summary>
		/// ボタンの選択及びボタンを押されたときの処理の呼び出し
		/// </summary>
		/// <remarks>
		/// 入力に応じたボタン選択の変更と
		/// 決定キーが押されたときそのボタンのOnClick関数を呼びます
		/// 1フレームに2度以上使わないでください。
		/// </remarks>
		void update();

	public:

		/// <summary>
		/// 決定入力
		/// </summary>
		static bool ok()
		{
			return KeyZ.up() || KeyEnter.up();
		}

		/// <summary>
		/// キャンセル入力
		/// </summary>
		static bool cancel()
		{
			return !ok() && (KeyX.up() || KeyBackspace.up());
		}

	};
}