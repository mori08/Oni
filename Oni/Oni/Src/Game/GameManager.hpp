#pragma once


#include "Object/GameObject.hpp"
#include "State/GameState.hpp"
#include "Stage/StageSupport.hpp"
#include "Event/GameEvent.hpp"


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

		// 状態(バトル・イベント・アドベンチャー)
		GameStatePtr mState;

		// ステージ
		StageSupport mStageSupport;

		// 背景画像名
		String mBackGroundName;

		// イベント
		GameEvent mEvent;

		// オブジェクトのリスト
		std::list<GameObjectPtr> mObjectList;

		// オブジェクトとその名前の連想配列
		std::map<String, GameObjectPtr> mObjectNameMap;

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
		/// ステージの取得
		/// </summary>
		const StageSupport& getStage() const
		{
			return mStageSupport;
		}

		/// <summary>
		/// イベントの取得
		/// </summary>
		GameEvent& getEvent()
		{
			return mEvent;
		}

		/// <summary>
		/// オブジェクトの追加
		/// </summary>
		void addObject(const GameObjectPtr& objectPtr);

		/// <summary>
		/// オブジェクトのリストの取得
		/// </summary>
		/// <returns> オブジェクトのリスト </returns>
		std::list<GameObjectPtr>& getObjectList()
		{
			return mObjectList;
		}

		/// <summary>
		/// オブジェクトの取得
		/// </summary>
		/// <param name="objName"> オブジェクトの名前 </param>
		/// <returns> オブジェクト </returns>
		Optional<GameObjectPtr> getObject(const String& objName);

	};

}