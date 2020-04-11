#pragma once


#include "../../Collider/Collider.hpp"
#include "../../ObjectType/ObjectType.hpp"


namespace Oni
{
	/// <summary>
	/// GameObject������BattleState�p�̃f�[�^
	/// </summary>
	class ObjectBattleData
	{
	public:

		/// <summary>
		/// �I�u�W�F�N�g����m�F�p
		/// </summary>
		class CheckInfo
		{
		public:

			CheckInfo(const Collider& c, const ObjectType& t, double v)
				: collider(c)
				, type(t)
				, value(v)
			{
			}

			const Collider   collider; // �R���C�_�[
			const ObjectType type;     // ���
			const double     value;    // �_���[�W�ʂȂǂ̒l

		};

	private:

		// �̗�
		double mHp;

		// �̗͂̍ő�l
		double mMaxHp;

		// ���G���� (���̂Ƃ����G)
		double mInvincibleSecond;

		// �A�N�V�����̎���
		double mActionSecond;

		// �I�𒆂̃A�N�V������
		String mActionName;
		
		// �A�N�V�����̃}�b�v
		std::map<String, std::function<void(double)>> mActionMap;

		// �I�u�W�F�N�g����̃��X�g
		Array<CheckInfo> mCheckInfoList;

	public:

		/// <summary>
		/// GameObject������BattleState�p�̃f�[�^
		/// </summary>
		/// <param name="hp"> �����̗� </param>
		ObjectBattleData(double hp);

	public:

		/// <summary>
		/// �X�V
		/// </summary>
		void update();

		/// <summary>
		/// �̗͂̎擾
		/// </summary>
		/// <returns> �̗� </returns>
		double getHp() const
		{
			return mHp;
		}

		/// <summary>
		/// �̗͂̌���
		/// </summary>
		/// <param name="damage"> �_���[�W��(���̒l�Ȃ��) </param>
		void damageHp(double damage)
		{
			mHp = Min(mHp - damage, mMaxHp);
		}

		/// <summary>
		/// ���G���Ԃ̐ݒ�
		/// </summary>
		/// <param name="second"> ���� </param>
		void setInvincibleSecond(double second)
		{
			mInvincibleSecond = second;
		}

		/// <summary>
		/// ���G��Ԃ��̔���
		/// </summary>
		/// <returns> ���G��Ԃ̂Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool isInvincible() const
		{
			return mInvincibleSecond > 0;
		}

		/// <summary>
		/// �A�N�V�����̐ݒ�
		/// </summary>
		/// <param name="name"> �A�N�V�����̖��O </param>
		/// <param name="func"> �A�N�V�����̏��� </param>
		void setAction(const String& name, const std::function<void(double)>& func)
		{
			mActionMap[name] = func;
		}

		/// <summary>
		/// �A�N�V�����̕ύX
		/// </summary>
		/// <param name="name"> �A�N�V�����̖��O </param>
		void changeAction(const String& name);

		/// <summary>
		/// ����̒ǉ�
		/// </summary>
		/// <param name="collider"> �R���C�_�[     </param>
		/// <param name="type"    > ���           </param>
		/// <param name="value"   > �_���[�W�ʂȂ� </param>
		void addCheckInfo(const Collider collider, const ObjectType type, double value = 0)
		{
			mCheckInfoList.emplace_back(collider, type, value);
		}

		/// <summary>
		/// ����̃��X�g�̎擾
		/// </summary>
		/// <returns> ����̃��X�g </returns>
		const Array<CheckInfo>& getCheckInfoList() const
		{
			return mCheckInfoList;
		}

	};
}