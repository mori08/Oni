#pragma once


#include "../Collider/Collider.hpp"
#include "../ObjectType/ObjectType.hpp"
#include "../ObjectData/Event/ObjectEventData.hpp"
#include "../../Slice/SliceTexture.hpp"


namespace Oni
{
	/// <summary>
	/// GameManager�Ŏg�p����I�u�W�F�N�g
	/// </summary>
	class GameObject
	{
	protected:

		// ���O
		const String mName;

		// ��������p�̒�����
		Collider mCollider;

		// �I�u�W�F�N�g�̎��
		ObjectType mType;

		// �C�x���g�p�̃f�[�^
		Optional<ObjectEventData> mEventData;

		// �摜�ƃA�j���[�V����
		SliceTexture mSlide;

		// true �̂Ƃ���\��
		bool mIsHiding;

	public:

		/// <summary>
		/// �I�u�W�F�N�g
		/// </summary>
		/// <param name="name"    > ���O       </param>
		/// <param name="collider"> �����蔻�� </param>
		/// <param name="type"    > ���       </param>
		/// <param name="slide"   > �摜       </param>
		GameObject(const String& name, const Collider& collider, const ObjectType& type, const SliceTexture& slide);

		/// <summary>
		/// y���W�̔�r
		/// </summary>
		bool operator<(const GameObject& another)const
		{
			return mCollider.centerPos().y < another.mCollider.centerPos().y;
		}

	public:

		/// <summary>
		/// �C�x���g���̍X�V
		/// </summary>
		virtual void updateEvent();

		/// <summary>
		/// �`��
		/// </summary>
		virtual void draw() const;

		/// <summary>
		/// �R���C�_�[�̎擾
		/// </summary>
		Collider& getCollider()
		{
			return mCollider;
		}

		/// <summary>
		/// �폜�������
		/// </summary>
		/// <returns> true �̂Ƃ��폜 </returns>
		virtual bool eraseAble() const;

		/// <summary>
		/// �R���C�_�[�̕`��
		/// </summary>
		void drawCollider() const;

		/// <summary>
		/// ���O�̎擾
		/// </summary>
		const String& getName() const
		{
			return mName;
		}

		/// <summary>
		/// �C�x���g�f�[�^�̎擾
		/// </summary>
		/// <returns> �C�x���g�f�[�^ </returns>
		Optional<ObjectEventData>& getEventData()
		{
			return mEventData;
		}

	protected:

		/// <summary>
		/// Collider��SliceTexture����摜��`�悷����W������
		/// </summary>
		Point getDrawTexturePoint() const;

		/// <summary>
		/// �A�j���[�V������ݒ肷��
		/// </summary>
		/// <param name="name"> ���O           </param>
		/// <param name="anim"> �A�j���[�V���� </param>
		void setAnim(const String& name, const Animation& anim);

	};

	using GameObjectPtr = std::shared_ptr<GameObject>;

}