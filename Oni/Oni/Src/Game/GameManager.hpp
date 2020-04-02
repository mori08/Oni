#pragma once


#include "Object/GameObject.hpp"


/*
2種類の座標を以下の表現で使い分ける.
	Vec2  pixel  -> ピクセル座標 : 当たり判定や描画に使用
	Point square -> マス座標     : 障害物の管理や経路探索に使用
*/


namespace Oni
{

	/// <summary>
	/// 地形やオブジェクトの管理
	/// </summary>
	class GameManager
	{
	public:

		static constexpr int32 SQUARE_X = 40; // 1マスのX辺の長さ(ピクセル)
		static constexpr int32 SQUARE_Y = 30; // 1マスのY辺の長さ(ピクセル)
		static constexpr int32 SQUARE_Z = 20; // 1マスのZ辺の長さ(ピクセル)

	private:

		// ステージの広さ(マス座標)
		Size mStageSize;

		// 地形の高さ
		Array<Array<int32>> mHeight;

		// 地形の傾斜
		Array<Array<int32>> mSlope;

		// オブジェクトのリスト
		Array<GameObjectPtr> mObjectList;

	private:

		GameManager();

		GameManager(const GameManager&) = default;
		GameManager& operator=(const GameManager&) = default;
		GameManager(GameManager&&) = default;
		GameManager& operator=(GameManager&&) = default;

	public:

		/// <summary>
		/// シングルトンとして管理しているGameManagerのインスタンスの取得
		/// </summary>
		/// <returns> インスタンス </returns>
		static GameManager& instance()
		{
			static GameManager gameManager;
			return gameManager;
		}

		/// <summary>
		/// 地形やオブジェクトの情報をcsvファイルから読み込み
		/// </summary>
		/// <returns> 正しく読み込めたとき true , そうでないとき false </returns>
		bool load();

		/// <summary>
		/// 更新
		/// </summary>
		void update();

		/// <summary>
		/// 描画
		/// </summary>
		void draw() const;

		/// <summary>
		/// 描画座標の取得
		/// </summary>
		/// <param name="pos"> 座標 </param>
		/// <returns> 描画座標 </returns>
		static Vec2 drawPos(const Vec3& pos);

		/// <summary>
		/// 地形の高さを取得
		/// </summary>
		/// <param name="pixel"> XY座標(ピクセル) </param>
		/// <returns> 地形の高さ </returns>
		double getTerrainHeight(const Vec2& pixel) const;

		/// <summary>
		/// 地形の高さを取得
		/// </summary>
		/// <param name="x"> X座標の範囲 </param>
		/// <param name="y"> Y座標       </param>
		/// <returns> 地形の高さ </returns>
		double getTerrainHeight(const std::pair<double, double>& x , double y) const;

		/// <summary>
		/// 地形の高さを取得
		/// </summary>
		/// <param name="collider"> 直方体 </param>
		/// <returns> 地形の高さ </returns>
		double getTerrainHeight(const Collider& collider) const
		{
			return getTerrainHeight({ collider.minPos().x,collider.maxPos().x }, collider.centerPos().y);
		}

	private:

		/// <summary>
		/// 地形の描画
		/// </summary>
		void drawTerrain() const;

	};

}