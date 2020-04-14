#pragma once


#include "../../Collider/Collider.hpp"


/*
2��ނ̍��W���ȉ��̕\���Ŏg��������.
	Vec2  pixel  -> �s�N�Z�����W : �����蔻���`��Ɏg�p
	Point square -> �}�X���W     : ��Q���̊Ǘ���o�H�T���Ɏg�p
*/


namespace Oni
{
	/// <summary>
	/// �n�`�̊Ǘ�
	/// </summary>
	class StageSupport
	{
	public:

		static constexpr int32 SQUARE_X = 40; // 1�}�X��X�ӂ̒���(�s�N�Z��)
		static constexpr int32 SQUARE_Y = 30; // 1�}�X��Y�ӂ̒���(�s�N�Z��)
		static constexpr int32 SQUARE_Z = 20; // 1�}�X��Z�ӂ̒���(�s�N�Z��)

	private:

		// �X�e�[�W�̍L��(XY�̃}�X���W)
		Size mStageSize;

		// �n�`�̍���
		Array<Array<int32>> mHeight;

		// �n�`�̌X��
		Array<Array<int32>> mSlope;

	public:

		/// <summary>
		/// �X�e�[�W��XY�����̃}�X�̐ݒ�
		/// </summary>
		/// <param name="size"> XY�����̍L�� </param>
		void setStageSize(const Size& size);

		/// <summary>
		/// �w�肵��xy�}�X���W�̍���(z�}�X���W)�̐ݒ�
		/// </summary>
		/// <param name="x"> x�}�X���W </param>
		/// <param name="y"> y�}�X���W </param>
		/// <param name="z"> z�}�X���W </param>
		void setHeight(int32 x, int32 y, int32 z)
		{
			mHeight[x][y] = z;
		}

		/// <summary>
		/// �w�肵��xy�}�X���W�̍���(z�}�X���W)�̐ݒ�
		/// </summary>
		/// <param name="x"> x�}�X���W </param>
		/// <param name="y"> y�}�X���W </param>
		/// <param name="z"> �X�� </param>
		void setSlope(int32 x, int32 y, int32 s)
		{
			mSlope[x][y] = s;
		}

		/// <summary>
		/// �n�`�̍������擾
		/// </summary>
		/// <param name="pos"> XY���W </param>
		double height(const Vec2& pixel)const;

		/// <summary>
		/// �n�`�̍������擾
		/// </summary>
		/// <param name="x"> X���W�͈̔� </param>
		/// <param name="y"> Y���W       </param>
		/// <returns> �n�`�̍��� </returns>
		double height(const std::pair<double, double>& x, double y) const;

		/// <summary>
		/// �n�`�̍������擾
		/// </summary>
		/// <param name="collider"> ������ </param>
		/// <returns> �n�`�̍��� </returns>
		double height(const Collider& collider) const
		{
			return height({ collider.minPos().x,collider.maxPos().x }, collider.centerPos().y);
		}

		/// <summary>
		/// �n�`�̕`��
		/// </summary>
		/// <param name="cameraPos"> �J�������W </param>
		void draw(const Vec2& cameraPos) const;

	};
}