#pragma once


#include "../GameObject.hpp"


namespace Oni
{
	/// <summary>
	/// ����̏����̃I�u�W�F�N�g
	/// </summary>
	class GhostGirlObject : public GameObject
	{
	private:

		// ���� ( +1�̂Ƃ��E����, -1�̂Ƃ������� )
		int32 mDirection;

	public:

		GhostGirlObject(const Vec3& pos);

	private:

	};
}