#pragma once


#include <Siv3D.hpp>


namespace Oni
{
	/// <summary>
	/// 線形的に値を変更
	/// 主にdoubleやVec2,Vec3などの小数値で扱う
	/// </summary>
	template<typename Type>
	class Linearly
	{
	private:

		// 何秒で値を変更するか (DeltaTimeを下回ると1フレームでmRateを1にする)
		double mChangeSecond;

		// { 始点, 終点-始点 }
		std::pair<Type, Type> mValue;

		// 内分比 [0,1]
		double mRate;

	public:

		/// <summary>
		/// 線形補完
		/// </summary>
		/// <param name="changeSecond"> 何秒で値を変更するか </param>
		/// <param name="begin"       > 始点                 </param>
		/// <param name="movement"    > 終点 - 始点          </param>
		Linearly(double changeSecond, const Type& begin, const Type& movement)
			: mChangeSecond(changeSecond)
			, mValue({ begin,movement })
			, mRate(0)
		{
		}

		/// <summary>
		/// 線形補完
		/// </summary>
		/// <param name="changeSecond"> 何秒で値を変更するか </param>
		/// <param name="value">      終点                 </param>
		Linearly(double changeSecond, Type value)
			: mChangeSecond(changeSecond)
			, mValue({ Type(),value })
			, mRate(0)
		{
		}

		/// <summary>
		/// 始点に戻す
		/// </summary>
		void restart()
		{
			mRate = 0;
		}

		/// <summary>
		/// 終点にとばす
		/// </summary>
		void toEndPoint()
		{
			mRate = 1;
		}

		/// <summary>
		/// 更新
		/// </summary>
		/// <returns>
		/// 内分比が 1 を超えたら true, そうでないとき false
		/// </returns>
		bool update()
		{
			const double deltaTime = Scene::DeltaTime();

			if (deltaTime > mChangeSecond) // mChangeSecondが0のときの対策
			{
				mRate = 1;
				return true;
			}

			mRate += deltaTime / mChangeSecond;

			if (mRate > 1)
			{
				mRate = 1;
				return true;
			}

			return false;
		}

		/// <summary>
		/// 値の取得
		/// </summary>
		Type getValue() const
		{
			return mValue.first + mRate * mValue.second;
		}

		/// <summary>
		/// 終点の取得
		/// </summary>
		Type getGoal() const
		{
			return mValue.first + mValue.second;
		}

	};

}