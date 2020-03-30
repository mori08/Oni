#pragma once


#include <Siv3D.hpp>


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

		static constexpr int32 SQUARE_SIZE = 40; // 1�}�X��1�ӂ̒���(�s�N�Z��)

	private:

		// �X�e�[�W�̍L��(�}�X���W)
		Size mStageSize;

		// �n�`�̍���
		Array<Array<int32>> mHeight;

		// �n�`�̌X��
		Array<Array<int32>> mSlope;

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
		/// �`��
		/// </summary>
		void draw() const;

		/// <summary>
		/// �n�`�̕`��
		/// </summary>
		void drawTerrain() const;

	};

}