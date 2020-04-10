#pragma once


#include "../GameObject.hpp"


namespace Oni
{
	/// <summary>
	/// 悪霊の少女のオブジェクト
	/// </summary>
	class GhostGirlObject : public GameObject
	{
	private:

		// 向き ( +1のとき右向き, -1のとき左向き )
		int32 mDirection;

	public:

		GhostGirlObject(const Vec3& pos);

	private:

	};
}