#pragma once


#include <Siv3D.hpp>


namespace Oni
{
	/// <summary>
	/// ���`�I�ɒl��ύX
	/// ���double��Vec2,Vec3�Ȃǂ̏����l�ň���
	/// </summary>
	template<typename Type>
	class Linearly
	{
	private:

		// ���b�Œl��ύX���邩 (DeltaTime��������1�t���[����mRate��1�ɂ���)
		double mChangeSecond;

		// { �n�_, �I�_-�n�_ }
		std::pair<Type, Type> mValue;

		// ������ [0,1]
		double mRate;

	public:

		/// <summary>
		/// ���`�⊮
		/// </summary>
		/// <param name="changeSecond"> ���b�Œl��ύX���邩 </param>
		/// <param name="begin"       > �n�_                 </param>
		/// <param name="movement"    > �I�_ - �n�_          </param>
		Linearly(double changeSecond, const Type& begin, const Type& movement)
			: mChangeSecond(changeSecond)
			, mValue({ begin,movement })
			, mRate(0)
		{
		}

		/// <summary>
		/// ���`�⊮
		/// </summary>
		/// <param name="changeSecond"> ���b�Œl��ύX���邩 </param>
		/// <param name="value">      �I�_                 </param>
		Linearly(double changeSecond, Type value)
			: mChangeSecond(changeSecond)
			, mValue({ Type(),value })
			, mRate(0)
		{
		}

		/// <summary>
		/// �n�_�ɖ߂�
		/// </summary>
		void restart()
		{
			mRate = 0;
		}

		/// <summary>
		/// �I�_�ɂƂ΂�
		/// </summary>
		void toEndPoint()
		{
			mRate = 1;
		}

		/// <summary>
		/// �X�V
		/// </summary>
		/// <returns>
		/// �����䂪 1 �𒴂����� true, �����łȂ��Ƃ� false
		/// </returns>
		bool update()
		{
			const double deltaTime = Scene::DeltaTime();

			if (deltaTime > mChangeSecond) // mChangeSecond��0�̂Ƃ��̑΍�
			{
				mRate = 1;
				return true;
			}

			mRate += deltaTime / mChangeSecond;

			if (mRate > 1)
			{
				mRate = 1;
				return true;
			}

			return false;
		}

		/// <summary>
		/// �l�̎擾
		/// </summary>
		Type getValue() const
		{
			return mValue.first + mRate * mValue.second;
		}

		/// <summary>
		/// �I�_�̎擾
		/// </summary>
		Type getGoal() const
		{
			return mValue.first + mValue.second;
		}

	};

}