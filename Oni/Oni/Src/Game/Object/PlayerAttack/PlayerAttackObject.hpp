#pragma once


#include "../GameObject.hpp"


namespace Oni
{

	/// <summary>
	/// プレイヤーの生成する攻撃オブジェクト
	/// </summary>
	class PlayerAttackObject : public GameObject
	{
	private:

		// 共有番号(攻撃の名前づけに利用)
		static uint32 sShareId;

	protected:

		// プレイヤーの座標
		Vec3 mPlayerPos;

		// 敵がいるか
		bool mEnemyExist;

		// 一番近くの敵
		Vec3 mNearestEnemyPos;

		// 影の移動方向
		Vec2 mShadowMoveDirection;

		// 光から影への遷移
		bool mCollisionEnemy;

		// 削除条件
		bool mEraseAble;

	public:

		/// <summary>
		/// プレイヤーの生成するオブジェクト
		/// </summary>
		/// <param name="pos"     > 生成座標 </param>
		/// <param name="velocity"> 初期速度 </param>
		/// <param name="actionName"> 初期アクション名 </param>
		PlayerAttackObject(const Vec3& pos, const Vec3& velocity, const String& actionName = U"Light");

	private:

		void passAnother(GameObject& another) const override;

		void checkAnother(const ObjectBattleData::CheckInfo& checkInfo) override;

		bool eraseAble() const override;

	private:

		/// <summary>
		/// 光状態の更新
		/// </summary>
		/// <param name="actionSecond"> 経過時間(s) </param>
		void updateLight(double actionSecond);

		/// <summary>
		/// 光から影への遷移
		/// </summary>
		void lightToShadow();

		/// <summary>
		/// 影状態の更新
		/// </summary>
		/// <param name="actionSecond"> 経過時間(s) </param>
		void updateShadow(double actionSecond);

		/// <summary>
		/// 光状態でプレイヤーの周りを周回
		/// </summary>
		void spinToPlayer(double actionSecond);

		/// <summary>
		/// 光状態でプレイヤーを追跡
		/// </summary>
		void chaseEnemy(double actionSecond);

	};

}