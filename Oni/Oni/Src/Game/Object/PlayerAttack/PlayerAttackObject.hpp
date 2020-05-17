#pragma once


#include "../GameObject.hpp"


namespace Oni
{

	/// <summary>
	/// プレイヤーの生成するオブジェクト
	/// </summary>
	class PlayerAttackObject : public GameObject
	{
	private:

		// 共有番号(攻撃の名前づけに利用)
		static uint32 sShareId;

	private:

		// プレイヤーのXY座標
		Vec2 mPlayerPos;

		// 削除条件
		bool mEraseAble;

	public:

		/// <summary>
		/// プレイヤーの生成するオブジェクト
		/// </summary>
		/// <param name="pos"     > 生成座標 </param>
		/// <param name="velocity"> 初期速度 </param>
		PlayerAttackObject(const Vec3& pos, const Vec3& velocity);

	private:

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

	};

}