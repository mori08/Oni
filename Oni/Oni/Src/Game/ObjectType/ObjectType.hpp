#pragma once


#include<Siv3D.hpp>


namespace Oni
{
	/// <summary>
	/// GameObjectの種類(の集合)
	/// 1bitを1種類に割り当てる
	/// </summary>
	class ObjectType
	{
	private:

		const int8 mValue;

	public:

		static const ObjectType PLAYER; // プレイヤー

		static const ObjectType ENEMY;  // 敵

		static const ObjectType PLAYER_ATTACK; // プレイヤーの攻撃

		static const ObjectType PLAYER_ENERGY; // プレイヤーのエネルギー

	private:

		/// <summary>
		/// オブジェクトの種類
		/// </summary>
		constexpr ObjectType(int8 value)
			: mValue(value)
		{
		}

	public:

		/// <summary>
		/// 和集合の作成
		/// </summary>
		constexpr ObjectType operator|(const ObjectType& another)const
		{
			return ObjectType(mValue | another.mValue);
		}

		/// <summary>
		/// 積集合の作成
		/// </summary>
		constexpr ObjectType operator&(const ObjectType& another)const
		{
			return ObjectType(mValue & another.mValue);
		}

		/// <summary>
		/// 差集合の作成
		/// </summary>
		constexpr ObjectType operator-(const ObjectType& another)const
		{
			return ObjectType(mValue & ~another.mValue);
		}

		/// <summary>
		/// 補集合の取得
		/// </summary>
		constexpr ObjectType operator~()const
		{
			return ObjectType(~mValue);
		}

		/// <summary>
		/// 空集合のとき false , そうでないとき true
		/// </summary>
		explicit operator bool() const
		{
			return mValue != 0;
		}

	};
}