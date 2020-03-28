#pragma once


#include <Siv3D.hpp>


namespace Oni
{
	/// <summary>
	/// �t���O�␔�l�̊Ǘ�
	/// ��bit�ɑΉ����邩�w�肵�܂�
	/// </summary>
	class Record
	{
	private:

		// ����
		const int32 mDigit;

		// �����l
		const int32 mDefaultValue;

		// �l
		int32 mValue;

		// �����̍��v�l
		static int32 sDigitTotal;

	public:

		/// <summary>
		/// ���R�[�h���\������v�f
		/// </summary>
		/// <param name="digit">        ����   </param>
		/// <param name="defaultValue"> �����l </param>
		Record(int32 digit, int32 defaultValue);

		/// <summary>
		/// ������
		/// </summary>
		void init()
		{
			mValue = mDefaultValue;
		}

		/// <summary>
		/// �l�̐ݒ�
		/// </summary>
		/// <param name="value"> �ύX�������l </param>
		void set(int32 value)
		{
			mValue = Clamp(value, 0, (1 << mDigit) - 1);
		}

		/// <summary>
		/// �l�̎擾
		/// </summary>
		/// <returns>
		/// �Ǘ����Ă���l
		/// </returns>
		int32 get() const
		{
			return mValue;
		}

		/// <summary>
		/// �Í����p�̃��X�g�ɂ��̃��R�[�h��ǉ�
		/// </summary>
		/// <param name="dataList"> �Í����p�̃��X�g </param>
		void addRecordToEncryptionList(std::list<uint32>& dataList) const;

		/// <summary>
		/// �����p�̃��X�g����l��ݒ�
		/// </summary>
		/// <param name="dataList"> �������p�̃��X�g </param>
		void setValueFromDecryption(std::list<uint32>& dataList);

		/// <summary>
		/// �����̍��v�l�̎擾
		/// </summary>
		/// <returns>
		/// �����̍��v�l
		/// </returns>
		static int32 getDigitTotal()
		{
			return sDigitTotal;
		}

	};
}