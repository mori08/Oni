#pragma once


#include "Object/GameObject.hpp"
#include "State/GameState.hpp"
#include "Stage/StageSupport.hpp"
#include "Event/GameEvent.hpp"


/*
2��ނ̍��W���ȉ��̕\���Ŏg��������.
	Vec2  pixel  -> �s�N�Z�����W : �����蔻���`��Ɏg�p
	Point square -> �}�X���W     : ��Q���̊Ǘ���o�H�T���Ɏg�p
*/


namespace Oni
{

	/// <summary>
	/// �n�`��I�u�W�F�N�g�̊Ǘ�
	/// </summary>
	class GameManager
	{
	public:

		static constexpr int32 SQUARE_X = 40; // 1�}�X��X�ӂ̒���(�s�N�Z��)
		static constexpr int32 SQUARE_Y = 30; // 1�}�X��Y�ӂ̒���(�s�N�Z��)
		static constexpr int32 SQUARE_Z = 20; // 1�}�X��Z�ӂ̒���(�s�N�Z��)

	private:

		// ���(�o�g���E�C�x���g�E�A�h�x���`���[)
		GameStatePtr mState;

		// �X�e�[�W
		StageSupport mStageSupport;

		// �w�i�摜��
		String mBackGroundName;

		// �C�x���g
		GameEvent mEvent;

		// �I�u�W�F�N�g�̃��X�g
		std::list<GameObjectPtr> mObjectList;

		// �I�u�W�F�N�g�Ƃ��̖��O�̘A�z�z��
		std::map<String, GameObjectPtr> mObjectNameMap;

	private:

		GameManager();

		GameManager(const GameManager&) = default;
		GameManager& operator=(const GameManager&) = default;
		GameManager(GameManager&&) = default;
		GameManager& operator=(GameManager&&) = default;

	public:

		/// <summary>
		/// �V���O���g���Ƃ��ĊǗ����Ă���GameManager�̃C���X�^���X�̎擾
		/// </summary>
		/// <returns> �C���X�^���X </returns>
		static GameManager& instance()
		{
			static GameManager gameManager;
			return gameManager;
		}

		/// <summary>
		/// �n�`��I�u�W�F�N�g�̏���csv�t�@�C������ǂݍ���
		/// </summary>
		/// <returns> �������ǂݍ��߂��Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool load();

		/// <summary>
		/// �X�V
		/// </summary>
		void update();

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;

		/// <summary>
		/// �`����W�̎擾
		/// </summary>
		/// <param name="pos"> ���W </param>
		/// <returns> �`����W </returns>
		static Vec2 drawPos(const Vec3& pos);

		/// <summary>
		/// �X�e�[�W�̎擾
		/// </summary>
		const StageSupport& getStage() const
		{
			return mStageSupport;
		}

		/// <summary>
		/// �C�x���g�̎擾
		/// </summary>
		GameEvent& getEvent()
		{
			return mEvent;
		}

		/// <summary>
		/// �I�u�W�F�N�g�̒ǉ�
		/// </summary>
		void addObject(const GameObjectPtr& objectPtr);

		/// <summary>
		/// �I�u�W�F�N�g�̃��X�g�̎擾
		/// </summary>
		/// <returns> �I�u�W�F�N�g�̃��X�g </returns>
		std::list<GameObjectPtr>& getObjectList()
		{
			return mObjectList;
		}

		/// <summary>
		/// �I�u�W�F�N�g�̎擾
		/// </summary>
		/// <param name="objName"> �I�u�W�F�N�g�̖��O </param>
		/// <returns> �I�u�W�F�N�g </returns>
		Optional<GameObjectPtr> getObject(const String& objName);

	};

}