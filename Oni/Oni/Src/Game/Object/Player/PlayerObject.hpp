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

	public:

		PlayerObject(const Vec3& pos);

	private:

		void updateBattle() override;

		void draw() const override;

		void checkAnother(const ObjectBattleData::CheckInfo& checkInfo) override;

	public:

		/// <summary>
		/// 待ち状態(バトルで使用)
		/// </summary>
		void control();

	};

}