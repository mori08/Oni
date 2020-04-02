#pragma once


#include "../Collider/Collider.hpp"
#include "../ObjectType/ObjectType.hpp"


namespace Oni
{
	/// <summary>
	/// GameManager�Ŏg�p����I�u�W�F�N�g
	/// </summary>
	class GameObject
	{
	protected:

		// �n�ʂɐڂ��Ă���Ƃ� true , �����łȂ��Ƃ� false
		bool mIsOnGround;

		// ���x
		Vec3 mVelocity;

		// �����x
		Vec3 mAcceleration;

		// ��������p�̒�����
		Collider mCollider;

		// �I�u�W�F�N�g�̎��
		ObjectType mType;

	public:

		/// <summary>
		/// �I�u�W�F�N�g
		/// </summary>
		/// <param name="pos" > �������W </param>
		/// <param name="size"> �T�C�Y   </param>
		/// <param name="type"> ���     </param>
		GameObject(const Vec3& pos, const Vec3 size, const ObjectType& type);

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// �`��
		/// </summary>
		virtual void draw() const = 0;

	protected:

		/// <summary>
		/// �n�`�����Q�l�ɂ����I�u�W�F�N�g�̈ړ�
		/// </summary>
		void moveObject();

	};

	using GameObjectPtr = std::shared_ptr<GameObject>;

}