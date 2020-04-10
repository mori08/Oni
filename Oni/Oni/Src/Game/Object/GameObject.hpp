#pragma once


#include "../Collider/Collider.hpp"
#include "../ObjectType/ObjectType.hpp"
#include "../ObjectData/Battle/ObjectBattleData.hpp"
#include "../../Slice/SliceTexture.hpp"


namespace Oni
{
	/// <summary>
	/// GameManager�Ŏg�p����I�u�W�F�N�g
	/// </summary>
	class GameObject
	{
	protected:

		// ��������p�̒�����
		Collider mCollider;

		// �I�u�W�F�N�g�̎��
		ObjectType mType;

		// �o�g���p�̃f�[�^
		Optional<ObjectBattleData> mBattleData;

		// �摜�ƃA�j���[�V����
		SliceTexture mSlide;

	public:

		/// <summary>
		/// �I�u�W�F�N�g
		/// </summary>
		/// <param name="collider"> �����蔻�� </param>
		/// <param name="type"    > ���       </param>
		/// <param name="slide"   > �摜       </param>
		GameObject(const Collider& collider, const ObjectType& type, const SliceTexture& slide);

		/// <summary>
		/// y���W�̔�r
		/// </summary>
		bool operator<(const GameObject& another)const
		{
			return mCollider.centerPos().y < another.mCollider.centerPos().y;
		}

	public:

		/// <summary>
		/// �o�g�����̍X�V
		/// </summary>
		virtual void updateBattle();

		/// <summary>
		/// �`��
		/// </summary>
		virtual void draw() const;

	protected:

		/// <summary>
		/// Collider��SliceTexture����摜��`�悷����W������
		/// </summary>
		Point getDrawTexturePoint() const;

	};

	using GameObjectPtr = std::shared_ptr<GameObject>;

}