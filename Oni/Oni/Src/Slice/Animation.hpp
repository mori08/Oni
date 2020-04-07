#pragma once


#include <Siv3D.hpp>


namespace Oni
{
	// 画像の切り替え順
	using PosOrder = Array<std::pair<double, Point>>;

	/// <summary>
	/// 画像の切り替え準とそれにかかる時間をまとめたもの
	/// </summary>
	class Animation
	{
	private:

		// 画像を切り替え終わるまでにかかる時間
		const double mTotalSecond;

		// 画像の切り替え順
		const PosOrder mPosOrder;

		// ループするか
		const bool mIsLoop;

	public:

		/// <summary>
		/// 画像の切り替え順とそれにかかる時間など
		/// </summary>
		/// <param name="posList"> 画像の切り替え順 </param>
		/// <param name="posList"> ループ           </param>
		Animation(const PosOrder& posOrder, bool isLoop);

		/// <summary>
		/// 画像の取得
		/// </summary>
		/// <param name="animSecond"> 時間 </param>
		/// <returns> 時間に対応した画像番号 </returns>
		Point getTexture(double animSecond) const;

		/// <summary>
		/// 画像を切り替え終わるまでにかかる時間の取得
		/// </summary>
		/// <returns> 画像を切り替え終わるまでにかかる時間 </returns>
		double getTotalSecond() const
		{
			return mTotalSecond;
		}

		/// <summary>
		/// ループするか示す
		/// </summary>
		/// <returns> ループするとき true , そうでないとき false </returns>
		bool loop() const
		{
			return mIsLoop;
		}

	private:

		/// <summary>
		/// mTotalSecondの作成
		/// </summary>
		static double getTotalSecond(const PosOrder& posOrder);

		/// <summary>
		/// posOrderの時間を累計に変更
		/// </summary>
		static PosOrder getPosOrder(PosOrder posOrder);

	};
}