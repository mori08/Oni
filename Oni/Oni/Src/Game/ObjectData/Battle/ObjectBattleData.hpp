#pragma once


#include <Siv3D.hpp>


namespace Oni
{
	/// <summary>
	/// GameObjectがもつBattleState用のデータ
	/// </summary>
	class ObjectBattleData
	{
	private:

		// 体力
		double mHp;

		// 体力の最大値
		double mMaxHp;

		// 無敵時間 (正のとき無敵)
		double mInvincibleSecond;

		// アクションの時間
		double mActionSecond;

		// 選択中のアクション名
		String mActionName;
		
		// アクションのマップ
		std::map<String, std::function<void(double)>> mActionMap;

	public:

		/// <summary>
		/// GameObjectがもつBattleState用のデータ
		/// </summary>
		/// <param name="hp"> 初期体力 </param>
		ObjectBattleData(double hp);

	public:

		/// <summary>
		/// 更新
		/// </summary>
		void update();

		/// <summary>
		/// 体力の取得
		/// </summary>
		/// <returns> 体力 </returns>
		double getHp() const
		{
			return mHp;
		}

		/// <summary>
		/// 体力の減少
		/// </summary>
		/// <param name="damage"> ダメージ量(負の値なら回復) </param>
		void damageHp(double damage)
		{
			mHp = Min(mHp - damage, mMaxHp);
		}

		/// <summary>
		/// 無敵時間の設定
		/// </summary>
		/// <param name="second"> 時間 </param>
		void setInvincibleSecond(double second)
		{
			mInvincibleSecond = second;
		}

		/// <summary>
		/// 無敵状態かの判定
		/// </summary>
		/// <returns> 無敵状態のとき true , そうでないとき false </returns>
		bool isInvincible() const
		{
			return mInvincibleSecond > 0;
		}

		/// <summary>
		/// アクションの設定
		/// </summary>
		/// <param name="name"> アクションの名前 </param>
		/// <param name="func"> アクションの処理 </param>
		void setAction(const String& name, const std::function<void(double)>& func)
		{
			mActionMap[name] = func;
		}

		/// <summary>
		/// アクションの変更
		/// </summary>
		/// <param name="name"> アクションの名前 </param>
		void changeAction(const String& name);

	};
}