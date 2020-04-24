#pragma once


#include <Siv3D.hpp>


namespace Oni
{
	/// <summary>
	/// EventやAdventureで表示するウィンドウ
	/// </summary>
	/// <remarks>
	/// 命名被りをさけるためWindowでなくBoard
	/// </remarks>
	class GameBoard
	{
	protected:

		// ウィンドウの範囲
		const RoundRect mRegion;

	public:

		/// <summary>
		/// ウィンドウ
		/// </summary>
		/// <param name="region"> ウィンドウの範囲 </param>
		GameBoard(const Rect& region);

		/// <summary>
		/// このウィンドウが選択されたときの処理
		/// </summary>
		virtual void select() = 0;

		/// <summary>
		/// 更新
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// 選択時の更新
		/// </summary>
		virtual void selectedUpdate() = 0;

		/// <summary>
		/// ウィンドウ背景の描画
		/// </summary>
		void drawBoard() const;

		/// <summary>
		/// 描画
		/// </summary>
		virtual void draw() const = 0;

	};
}