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

		/// <summary>
		/// ���̃I�u�W�F�N�g�֔���̏��n(�o�g���ł̎g�p)
		/// </summary>
		/// <param name="another"> ���I�u�W�F�N�g </param>
		virtual void passAnother(GameObject& another) const;

	protected:

		/// <summary>
		/// ���̃I�u�W�F�N�g�̔�������(�o�g���ł̎g�p)
		/// </summary>
		/// <param name="checkInfo">  </param>
		virtual void checkAnother(const ObjectBattleData::CheckInfo& chekcInfo);

		/// <summary>
		/// Collider��SliceTexture����摜��`�悷����W������
		/// </summary>
		Point getDrawTexturePoint() const;

		/// <summary>
		/// �I�u�W�F�N�g�̎�ނƏՓ˂̔���
		/// </summary>
		/// <param name="checkInfo"> ����m�F�p�̏�� </param>
		/// <param name="checkType"> �w�肷����     </param>
		/// <returns>
		/// �w��̎�ނ̃I�u�W�F�N�g���Փ˂��Ă���Ƃ� true , �����łȂ��Ƃ� false
		/// </returns>
		bool checkTypeAndCollision(const ObjectBattleData::CheckInfo& checkInfo, const ObjectType& checkType) const
		{
			return (checkInfo.type & checkType) && mCollider.intersects(checkInfo.collider);
		}

		/// <summary>
		/// �w��̎�ނ̃I�u�W�F�N�g�̂Ƃ����W�̎擾
		/// </summary>
		/// <param name="checkType"> �w�肷���� </param>
		/// <returns>
		/// ���W
		/// </returns>
		Optional<Vec3> checkTypeAndGetPos(const ObjectType& checkType) const;

	};

	using GameObjectPtr = std::shared_ptr<GameObject>;

}