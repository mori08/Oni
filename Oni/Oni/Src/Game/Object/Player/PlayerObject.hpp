#pragma once


#include "../GameObject.hpp"


namespace Oni
{

	/// <summary>
	/// Playerの操作するオブジェクト
	/// </summary>
	class PlayerObject : public GameObject
	{
	private:

		// 向き ( +1のとき右向き, -1のとき左向き )
		int32 mDirection;

		// 攻撃の溜め時間(s)
		double mChargeSecond;

	public:

		PlayerObject(const Vec3& pos);

	private:

		void draw() const override;

	public:

		/// <summary>
		/// 待ち状態(バトルで使用)
		/// </summary>
		void control();

	};

}