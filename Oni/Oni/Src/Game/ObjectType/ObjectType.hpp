#pragma once


#include<Siv3D.hpp>


namespace Oni
{
	/// <summary>
	/// GameObject�̎��(�̏W��)
	/// 1bit��1��ނɊ��蓖�Ă�
	/// </summary>
	class ObjectType
	{
	private:

		const int8 mValue;

	public:

		static const ObjectType PLAYER; // �v���C���[

		static const ObjectType ENEMY;  // �G

		static const ObjectType PLAYER_ATTACK; // �v���C���[�̍U��

		static const ObjectType PLAYER_ENERGY; // �v���C���[�̃G�l���M�[

	private:

		/// <summary>
		/// �I�u�W�F�N�g�̎��
		/// </summary>
		constexpr ObjectType(int8 value)
			: mValue(value)
		{
		}

	public:

		/// <summary>
		/// �a�W���̍쐬
		/// </summary>
		constexpr ObjectType operator|(const ObjectType& another)const
		{
			return ObjectType(mValue | another.mValue);
		}

		/// <summary>
		/// �ϏW���̍쐬
		/// </summary>
		constexpr ObjectType operator&(const ObjectType& another)const
		{
			return ObjectType(mValue & another.mValue);
		}

		/// <summary>
		/// ���W���̍쐬
		/// </summary>
		constexpr ObjectType operator-(const ObjectType& another)const
		{
			return ObjectType(mValue & ~another.mValue);
		}

		/// <summary>
		/// ��W���̎擾
		/// </summary>
		constexpr ObjectType operator~()const
		{
			return ObjectType(~mValue);
		}

		/// <summary>
		/// ��W���̂Ƃ� false , �����łȂ��Ƃ� true
		/// </summary>
		explicit operator bool() const
		{
			return mValue != 0;
		}

	};
}