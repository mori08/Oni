#pragma once


#include <Siv3D.hpp>


namespace Oni
{

	/// <summary>
	/// �I�u�W�F�N�g�̏Փ˔�����s��������
	/// ���S���W�ƃT�C�Y������
	/// </summary>
	class Collider
	{
	private:

		Vec3 mPos;

		Vec3 mSize;

	public:

		/// <summary>
		/// �����̂̍쐬
		/// </summary>
		/// <param name="pos" > ���W   </param>
		/// <param name="size"> �T�C�Y </param>
		constexpr Collider(const Vec3 pos, Vec3 size)
			: mPos(pos)
			, mSize(size)
		{
		}

		/// <summary>
		/// x,y,z���e�X�̍ŏ��l���Ƃ���W�̎擾
		/// </summary>
		/// <returns> x,y,z���e�X�̍ŏ��l���Ƃ���W </returns>
		constexpr Vec3 minPos() const
		{
			return std::move(mPos - mSize / 2);
		}

		/// <summary>
		/// x,y,z���e�X�̍ő�l���Ƃ���W�̎擾
		/// </summary>
		/// <returns> x,y,z���e�X�̍ő�l���Ƃ���W </returns>
		constexpr Vec3 maxPos() const
		{
			return std::move(mPos + mSize / 2);
		}

		/// <summary>
		/// ���S���W�̎擾
		/// </summary>
		constexpr Vec3 centerPos() const
		{
			return mPos;
		}

		/// <summary>
		/// ���W�̈ړ�
		/// </summary>
		/// <param name="movement"> �ړ��� </param>
		void moveBy(const Vec3& movement)
		{
			mPos += movement;
		}

		/// <summary>
		/// ���W�̈ړ�
		/// </summary>
		/// <param name="movement"> �ړ��� </param>
		constexpr Collider movedBy(const Vec3& movement) const
		{
			return std::move(Collider(mPos + movement, mSize));
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