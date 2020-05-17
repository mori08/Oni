#pragma once


#include "../GameObject.hpp"


namespace Oni
{

	/// <summary>
	/// �v���C���[�̐�������I�u�W�F�N�g
	/// </summary>
	class PlayerAttackObject : public GameObject
	{
	private:

		// ���L�ԍ�(�U���̖��O�Â��ɗ��p)
		static uint32 sShareId;

	private:

		// �v���C���[��XY���W
		Vec2 mPlayerPos;

		// �폜����
		bool mEraseAble;

	public:

		/// <summary>
		/// �v���C���[�̐�������I�u�W�F�N�g
		/// </summary>
		/// <param name="pos"     > �������W </param>
		/// <param name="velocity"> �������x </param>
		PlayerAttackObject(const Vec3& pos, const Vec3& velocity);

	private:

		void checkAnother(const ObjectBattleData::CheckInfo& checkInfo) override;

		bool eraseAble() const override;

	private:

		/// <summary>
		/// ����Ԃ̍X�V
		/// </summary>
		/// <param name="actionSecond"> �o�ߎ���(s) </param>
		void updateLight(double actionSecond);

		/// <summary>
		/// ������e�ւ̑J��
		/// </summary>
		void lightToShadow();

		/// <summary>
		/// �e��Ԃ̍X�V
		/// </summary>
		/// <param name="actionSecond"> �o�ߎ���(s) </param>
		void updateShadow(double actionSecond);

	};

}