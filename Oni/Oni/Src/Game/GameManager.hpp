#pragma once


#include "Object/GameObject.hpp"


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

		// �X�e�[�W�̍L��(�}�X���W)
		Size mStageSize;

		// �n�`�̍���
		Array<Array<int32>> mHeight;

		// �n�`�̌X��
		Array<Array<int32>> mSlope;

		// �I�u�W�F�N�g�̃��X�g
		Array<GameObjectPtr> mObjectList;

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
		/// �n�`�̍������擾
		/// </summary>
		/// <param name="pixel"> XY���W(�s�N�Z��) </param>
		/// <returns> �n�`�̍��� </returns>
		double getTerrainHeight(const Vec2& pixel) const;

		/// <summary>
		/// �n�`�̍������擾
		/// </summary>
		/// <param name="x"> X���W�͈̔� </param>
		/// <param name="y"> Y���W       </param>
		/// <returns> �n�`�̍��� </returns>
		double getTerrainHeight(const std::pair<double, double>& x , double y) const;

		/// <summary>
		/// �n�`�̍������擾
		/// </summary>
		/// <param name="collider"> ������ </param>
		/// <returns> �n�`�̍��� </returns>
		double getTerrainHeight(const Collider& collider) const
		{
			return getTerrainHeight({ collider.minPos().x,collider.maxPos().x }, collider.centerPos().y);
		}

	private:

		/// <summary>
		/// �n�`�̕`��
		/// </summary>
		void drawTerrain() const;

	};

}