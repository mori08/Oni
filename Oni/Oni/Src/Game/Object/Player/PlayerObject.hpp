#pragma once


#include "../GameObject.hpp"


namespace Oni
{

	/// <summary>
	/// Player�̑��삷��I�u�W�F�N�g
	/// </summary>
	class PlayerObject : public GameObject
	{
	private:

		// ���� ( +1�̂Ƃ��E����, -1�̂Ƃ������� )
		int32 mDirection;

		// �U���̗��ߎ���(s)
		double mChargeSecond;

	public:

		PlayerObject(const Vec3& pos);

	private:

		void updateBattle() override;

		void draw() const override;

		void checkAnother(const ObjectBattleData::CheckInfo& checkInfo) override;

	public:

		/// <summary>
		/// �҂����(�o�g���Ŏg�p)
		/// </summary>
		void control();

	private:

		/// <summary>
		/// 3�A�U��
		/// </summary>
		void tripleAttack();

		/// <summary>
		/// ��]�U��
		/// </summary>
		void spinAttack();

		/// <summary>
		/// �ǐՍU��
		/// </summary>
		void chaseAttack();

	};

}