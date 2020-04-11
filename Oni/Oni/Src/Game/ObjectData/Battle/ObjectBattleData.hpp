#pragma once


#include "../../Collider/Collider.hpp"
#include "../../ObjectType/ObjectType.hpp"


namespace Oni
{
	/// <summary>
	/// GameObjectがもつBattleState用のデータ
	/// </summary>
	class ObjectBattleData
	{
	public:

		/// <summary>
		/// オブジェクト判定確認用
		/// </summary>
		class CheckInfo
		{
		public:

			CheckInfo(const Collider& c, const ObjectType& t, double v)
				: collider(c)
				, type(t)
				, value(v)
			{
			}

			const Collider   collider; // コライダー
			const ObjectType type;     // 種類
			const double     value;    // ダメージ量などの値

		};

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

		// オブジェクト判定のリスト
		Array<CheckInfo> mCheckInfoList;

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

		/// <summary>
		/// 判定の追加
		/// </summary>
		/// <param name="collider"> コライダー     </param>
		/// <param name="type"    > 種類           </param>
		/// <param name="value"   > ダメージ量など </param>
		void addCheckInfo(const Collider collider, const ObjectType type, double value = 0)
		{
			mCheckInfoList.emplace_back(collider, type, value);
		}

		/// <summary>
		/// 判定のリストの取得
		/// </summary>
		/// <returns> 判定のリスト </returns>
		const Array<CheckInfo>& getCheckInfoList() const
		{
			return mCheckInfoList;
		}

	};
}