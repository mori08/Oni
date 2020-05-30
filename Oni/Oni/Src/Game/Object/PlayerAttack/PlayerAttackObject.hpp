#pragma once


#include "../GameObject.hpp"


namespace Oni
{

	/// <summary>
	/// �v���C���[�̐�������U���I�u�W�F�N�g
	/// </summary>
	class PlayerAttackObject : public GameObject
	{
	private:

		// ���L�ԍ�(�U���̖��O�Â��ɗ��p)
		static uint32 sShareId;

	protected:

		// �v���C���[�̍��W
		Vec3 mPlayerPos;

		// �G�����邩
		bool mEnemyExist;

		// ��ԋ߂��̓G
		Vec3 mNearestEnemyPos;

		// �e�̈ړ�����
		Vec2 mShadowMoveDirection;

		// ������e�ւ̑J��
		bool mCollisionEnemy;

		// �폜����
		bool mEraseAble;

	public:

		/// <summary>
		/// �v���C���[�̐�������I�u�W�F�N�g
		/// </summary>
		/// <param name="pos"     > �������W </param>
		/// <param name="velocity"> �������x </param>
		/// <param name="actionName"> �����A�N�V������ </param>
		PlayerAttackObject(const Vec3& pos, const Vec3& velocity, const String& actionName = U"Light");

	private:

		void passAnother(GameObject& another) const override;

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

		/// <summary>
		/// ����ԂŃv���C���[�̎��������
		/// </summary>
		void spinToPlayer(double actionSecond);

		/// <summary>
		/// ����ԂŃv���C���[��ǐ�
		/// </summary>
		void chaseEnemy(double actionSecond);

	};

}