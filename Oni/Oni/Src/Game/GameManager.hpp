#pragma once


#include <Siv3D.hpp>


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

		static constexpr int32 SQUARE_SIZE = 40; // 1マスの1辺の長さ(ピクセル)

	private:

		// ステージの広さ(マス座標)
		Size mStageSize;

		// 地形の高さ
		Array<Array<int32>> mHeight;

		// 地形の傾斜
		Array<Array<int32>> mSlope;

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
		/// 描画
		/// </summary>
		void draw() const;

		/// <summary>
		/// 地形の描画
		/// </summary>
		void drawTerrain() const;

	};

}