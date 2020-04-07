#pragma once


#include <Siv3D.hpp>


namespace Oni
{
	// �摜�̐؂�ւ���
	using PosOrder = Array<std::pair<double, Point>>;

	/// <summary>
	/// �摜�̐؂�ւ����Ƃ���ɂ����鎞�Ԃ��܂Ƃ߂�����
	/// </summary>
	class Animation
	{
	private:

		// �摜��؂�ւ��I���܂łɂ����鎞��
		const double mTotalSecond;

		// �摜�̐؂�ւ���
		const PosOrder mPosOrder;

		// ���[�v���邩
		const bool mIsLoop;

	public:

		/// <summary>
		/// �摜�̐؂�ւ����Ƃ���ɂ����鎞�ԂȂ�
		/// </summary>
		/// <param name="posList"> �摜�̐؂�ւ��� </param>
		/// <param name="posList"> ���[�v           </param>
		Animation(const PosOrder& posOrder, bool isLoop);

		/// <summary>
		/// �摜�̎擾
		/// </summary>
		/// <param name="animSecond"> ���� </param>
		/// <returns> ���ԂɑΉ������摜�ԍ� </returns>
		Point getTexture(double animSecond) const;

		/// <summary>
		/// �摜��؂�ւ��I���܂łɂ����鎞�Ԃ̎擾
		/// </summary>
		/// <returns> �摜��؂�ւ��I���܂łɂ����鎞�� </returns>
		double getTotalSecond() const
		{
			return mTotalSecond;
		}

		/// <summary>
		/// ���[�v���邩����
		/// </summary>
		/// <returns> ���[�v����Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool loop() const
		{
			return mIsLoop;
		}

	private:

		/// <summary>
		/// mTotalSecond�̍쐬
		/// </summary>
		static double getTotalSecond(const PosOrder& posOrder);

		/// <summary>
		/// posOrder�̎��Ԃ�݌v�ɕύX
		/// </summary>
		static PosOrder getPosOrder(PosOrder posOrder);

	};
}