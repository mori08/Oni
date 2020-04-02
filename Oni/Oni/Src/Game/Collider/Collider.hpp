#pragma once


#include <Siv3D.hpp>


namespace Oni
{

	/// <summary>
	/// オブジェクトの衝突判定を行う直方体
	/// 中心座標とサイズを持つ
	/// </summary>
	class Collider
	{
	private:

		Vec3 mPos;

		Vec3 mSize;

	public:

		/// <summary>
		/// 直方体の作成
		/// </summary>
		/// <param name="pos" > 座標   </param>
		/// <param name="size"> サイズ </param>
		constexpr Collider(const Vec3 pos, Vec3 size)
			: mPos(pos)
			, mSize(size)
		{
		}

		/// <summary>
		/// x,y,zが各々の最小値をとる座標の取得
		/// </summary>
		/// <returns> x,y,zが各々の最小値をとる座標 </returns>
		constexpr Vec3 minPos() const
		{
			return std::move(mPos - mSize / 2);
		}

		/// <summary>
		/// x,y,zが各々の最大値をとる座標の取得
		/// </summary>
		/// <returns> x,y,zが各々の最大値をとる座標 </returns>
		constexpr Vec3 maxPos() const
		{
			return std::move(mPos + mSize / 2);
		}

		/// <summary>
		/// 中心座標の取得
		/// </summary>
		constexpr Vec3 centerPos() const
		{
			return mPos;
		}

		/// <summary>
		/// 座標の移動
		/// </summary>
		/// <param name="movement"> 移動量 </param>
		void moveBy(const Vec3& movement)
		{
			mPos += movement;
		}

		/// <summary>
		/// 座標の移動
		/// </summary>
		/// <param name="movement"> 移動量 </param>
		constexpr Collider movedBy(const Vec3& movement) const
		{
			return std::move(Collider(mPos + movement, mSize));
		}

		/// <summary>
		/// 座標の設定
		/// </summary>
		void setPos(const Vec3& pos)
		{
			mPos = pos;
		}

		/// <summary>
		/// 他の直方体との交差判定
		/// </summary>
		/// <param name="another"> 他の直方体 </param>
		/// <returns> 交差しているとき true , そうでないとき false </returns>
		bool intersects(const Collider& another)const
		{
			return compareVec3(Abs(mPos - another.mPos), (mSize + another.mSize) / 2);
		}

		/// <summary>
		/// 他の直方体との包含判定
		/// </summary>
		/// <param name="another"> 他の直方体 </param>
		/// <returns> 包含しているとき true , そうでないとき false </returns>
		bool contains(const Collider& another)const
		{
			return compareVec3(minPos(), another.minPos()) && compareVec3(another.maxPos(), maxPos());
		}

	private:

		/// <summary>
		/// 座標の各要素を比較しaよりbが大きいかか示す
		/// </summary>
		/// <param name="a"> 座標a </param>
		/// <param name="b"> 座標b </param>
		/// <returns> 
		/// 座標の各要素でaよりbが大きくなるなら true , そうでないなら false 
		/// </returns>
		static bool compareVec3(const Vec3& a, const Vec3& b)
		{
			return (a.x < b.x) && (a.y < b.y) && (a.z < b.z);
		}

	};

}