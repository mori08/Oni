#pragma once


#include "../../Collider/Collider.hpp"


/*
2種類の座標を以下の表現で使い分ける.
	Vec2  pixel  -> ピクセル座標 : 当たり判定や描画に使用
	Point square -> マス座標     : 障害物の管理や経路探索に使用
*/


namespace Oni
{
	/// <summary>
	/// 地形の管理
	/// </summary>
	class StageSupport
	{
	public:

		static constexpr int32 SQUARE_X = 40; // 1マスのX辺の長さ(ピクセル)
		static constexpr int32 SQUARE_Y = 30; // 1マスのY辺の長さ(ピクセル)
		static constexpr int32 SQUARE_Z = 20; // 1マスのZ辺の長さ(ピクセル)

	private:

		// ステージの広さ(XYのマス座標)
		Size mStageSize;

		// 地形の高さ
		Array<Array<int32>> mHeight;

		// 地形の傾斜
		Array<Array<int32>> mSlope;

	public:

		/// <summary>
		/// ステージのXY方向のマスの設定
		/// </summary>
		/// <param name="size"> XY方向の広さ </param>
		void setStageSize(const Size& size);

		/// <summary>
		/// 指定したxyマス座標の高さ(zマス座標)の設定
		/// </summary>
		/// <param name="x"> xマス座標 </param>
		/// <param name="y"> yマス座標 </param>
		/// <param name="z"> zマス座標 </param>
		void setHeight(int32 x, int32 y, int32 z)
		{
			mHeight[x][y] = z;
		}

		/// <summary>
		/// 指定したxyマス座標の高さ(zマス座標)の設定
		/// </summary>
		/// <param name="x"> xマス座標 </param>
		/// <param name="y"> yマス座標 </param>
		/// <param name="z"> 傾斜 </param>
		void setSlope(int32 x, int32 y, int32 s)
		{
			mSlope[x][y] = s;
		}

		/// <summary>
		/// 地形の高さを取得
		/// </summary>
		/// <param name="pos"> XY座標 </param>
		double height(const Vec2& pixel)const;

		/// <summary>
		/// 地形の高さを取得
		/// </summary>
		/// <param name="x"> X座標の範囲 </param>
		/// <param name="y"> Y座標       </param>
		/// <returns> 地形の高さ </returns>
		double height(const std::pair<double, double>& x, double y) const;

		/// <summary>
		/// 地形の高さを取得
		/// </summary>
		/// <param name="collider"> 直方体 </param>
		/// <returns> 地形の高さ </returns>
		double height(const Collider& collider) const
		{
			return height({ collider.minPos().x,collider.maxPos().x }, collider.centerPos().y);
		}

		/// <summary>
		/// 地形の描画
		/// </summary>
		/// <param name="cameraPos"> カメラ座標 </param>
		void draw(const Vec2& cameraPos) const;

	};
}