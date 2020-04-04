#pragma once


#include <Siv3D.hpp>


namespace Oni
{

	/// <summary>
	/// �I�u�W�F�N�g�̏Փ˔�����s��������
	/// ���S���W�ƃT�C�Y������
	/// ���x�E�����x����I�u�W�F�N�g�̈ړ����s��
	/// </summary>
	class Collider
	{
	public:

		static const size_t X = 0; // X�������̃C���f�b�N�X
		static const size_t Y = 1; // Y�������̃C���f�b�N�X
		static const size_t Z = 2; // Z�������̃C���f�b�N�X

	private:

		// �n�ʂɐڂ��Ă���Ƃ� true , �����łȂ��Ƃ� false
		bool mIsOnGround;

		// ���W
		Vec3 mPos;

		// �T�C�Y
		Vec3 mSize;

		// ���x
		Vec3 mVelocity;

		// �����x
		Vec3 mAcceleration;

	public:

		/// <summary>
		/// �����̂̍쐬
		/// </summary>
		/// <param name="pos" > ���W   </param>
		/// <param name="size"> �T�C�Y </param>
		Collider(const Vec3 pos, Vec3 size);

		/// <summary>
		/// ���x�E�����x��n�`����p�������W�̕ύX
		/// </summary>
		/// <remarks>
		/// 1�t���[����2�x�ȏ�Ă΂Ȃ�
		/// </remarks>
		void update();

		/// <summary>
		/// ���x�̐ݒ�
		/// </summary>
		/// <param name="index"> 0 X�� , 1 Y�� , 2 Z�� </param>
		/// <param name="speed"> ����                  </param>
		void setVelocity(size_t index, double speed);

		/// <summary>
		/// �����x�̐ݒ�
		/// </summary>
		/// <param name="index"> 0 X�� , 1 Y�� , 2 Z�� </param>
		/// <param name="value"> �����x�̑傫��        </param>
		void setAcceleration(size_t index, double value);

		/// <summary>
		/// �n�ʂɐڂ��Ă��邩����
		/// </summary>
		/// <returns> �n�ʂɐڂ��Ă���Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool isOnGround()
		{
			return mIsOnGround;
		}

		/// <summary>
		/// x,y,z���e�X�̍ŏ��l���Ƃ���W�̎擾
		/// </summary>
		/// <returns> x,y,z���e�X�̍ŏ��l���Ƃ���W </returns>
		Vec3 minPos() const
		{
			return std::move(mPos - mSize / 2);
		}

		/// <summary>
		/// x,y,z���e�X�̍ő�l���Ƃ���W�̎擾
		/// </summary>
		/// <returns> x,y,z���e�X�̍ő�l���Ƃ���W </returns>
		Vec3 maxPos() const
		{
			return std::move(mPos + mSize / 2);
		}

		/// <summary>
		/// ���S���W�̎擾
		/// </summary>
		const Vec3& centerPos() const
		{
			return mPos;
		}

		/// <summary>
		/// ���W�̐ݒ�
		/// </summary>
		void setPos(const Vec3& pos)
		{
			mPos = pos;
		}

		/// <summary>
		/// ���̒����̂Ƃ̌�������
		/// </summary>
		/// <param name="another"> ���̒����� </param>
		/// <returns> �������Ă���Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool intersects(const Collider& another)const
		{
			return compareVec3(Abs(mPos - another.mPos), (mSize + another.mSize) / 2);
		}

		/// <summary>
		/// ���̒����̂Ƃ̕�ܔ���
		/// </summary>
		/// <param name="another"> ���̒����� </param>
		/// <returns> ��܂��Ă���Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool contains(const Collider& another)const
		{
			return compareVec3(minPos(), another.minPos()) && compareVec3(another.maxPos(), maxPos());
		}

		/// <summary>
		/// ���W���ړ������������̂̎擾
		/// </summary>
		/// <param name="movement"> �ړ��� </param>
		Collider movedBy(const Vec3& movement) const
		{
			return std::move(Collider(mPos + movement, mSize));
		}

	private:

		/// <summary>
		/// ���W�̊e�v�f���r��a���b���傫����������
		/// </summary>
		/// <param name="a"> ���Wa </param>
		/// <param name="b"> ���Wb </param>
		/// <returns> 
		/// ���W�̊e�v�f��a���b���傫���Ȃ�Ȃ� true , �����łȂ��Ȃ� false 
		/// </returns>
		static bool compareVec3(const Vec3& a, const Vec3& b)
		{
			return (a.x < b.x) && (a.y < b.y) && (a.z < b.z);
		}

	};

}