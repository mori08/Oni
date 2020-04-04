#pragma once


#include <Siv3D.hpp>


namespace Oni
{

	/// <summary>
	/// オブジェクトの衝突判定を行う直方体
	/// 中心座標とサイズを持つ
	/// 速度・加速度からオブジェクトの移動も行う
	/// </summary>
	class Collider
	{
	public:

		static const size_t X = 0; // X軸方向のインデックス
		static const size_t Y = 1; // Y軸方向のインデックス
		static const size_t Z = 2; // Z軸方向のインデックス

	private:

		// 地面に接しているとき true , そうでないとき false
		bool mIsOnGround;

		// 座標
		Vec3 mPos;

		// サイズ
		Vec3 mSize;

		// 速度
		Vec3 mVelocity;

		// 加速度
		Vec3 mAcceleration;

	public:

		/// <summary>
		/// 直方体の作成
		/// </summary>
		/// <param name="pos" > 座標   </param>
		/// <param name="size"> サイズ </param>
		Collider(const Vec3 pos, Vec3 size);

		/// <summary>
		/// 速度・加速度や地形情報を用いた座標の変更
		/// </summary>
		/// <remarks>
		/// 1フレームに2度以上呼ばない
		/// </remarks>
		void update();

		/// <summary>
		/// 速度の設定
		/// </summary>
		/// <param name="index"> 0 X軸 , 1 Y軸 , 2 Z軸 </param>
		/// <param name="speed"> 速さ                  </param>
		void setVelocity(size_t index, double speed);

		/// <summary>
		/// 加速度の設定
		/// </summary>
		/// <param name="index"> 0 X軸 , 1 Y軸 , 2 Z軸 </param>
		/// <param name="value"> 加速度の大きさ        </param>
		void setAcceleration(size_t index, double value);

		/// <summary>
		/// 地面に接しているか示す
		/// </summary>
		/// <returns> 地面に接しているとき true , そうでないとき false </returns>
		bool isOnGround()
		{
			return mIsOnGround;
		}

		/// <summary>
		/// x,y,zが各々の最小値をとる座標の取得
		/// </summary>
		/// <returns> x,y,zが各々の最小値をとる座標 </returns>
		Vec3 minPos() const
		{
			return std::move(mPos - mSize / 2);
		}

		/// <summary>
		/// x,y,zが各々の最大値をとる座標の取得
		/// </summary>
		/// <returns> x,y,zが各々の最大値をとる座標 </returns>
		Vec3 maxPos() const
		{
			return std::move(mPos + mSize / 2);
		}

		/// <summary>
		/// 中心座標の取得
		/// </summary>
		const Vec3& centerPos() const
		{
			return mPos;
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

		/// <summary>
		/// 座標を移動させた直方体の取得
		/// </summary>
		/// <param name="movement"> 移動量 </param>
		Collider movedBy(const Vec3& movement) const
		{
			return std::move(Collider(mPos + movement, mSize));
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