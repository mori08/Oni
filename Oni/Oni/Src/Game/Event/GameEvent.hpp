#pragma once


#include <Siv3D.hpp>


namespace Oni
{

	/// <summary>
	/// �C�x���g�Ǘ�
	/// </summary>
	class GameEvent
	{
	private:

		// �C�x���g���e
		std::map<String, Array<Array<String>>> mData;

		// �C�x���g��
		String mEventName;

		// �ǂݍ��ݒ��̍s
		int32 mReadingRow;

		// �C�x���g�p�̏���
		std::map<String, std::function<void()>> mEventFunc;

		// �҂�����
		double mWaitSecond;

		// �G���[�����������Ƃ� true �ɂ��ăC�x���g���~
		bool mError;

	public:

		GameEvent();

		/// <summary>
		/// �C�x���g���L�q����csv�t�@�C���̃��[�h
		/// </summary>
		/// <param name="dirName"> �f�B���N�g���̖��O </param>
		void load(const FilePath& dirName);

		/// <summary>
		/// �w�肵���C�x���g�ɏ����ʒu�ɔ��
		/// </summary>
		/// <param name="eventName"> �C�x���g�� </param>
		void jamp(const String& eventName);

		/// <summary>
		/// �X�V
		/// </summary>
		void update();

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;

	private:

		/// <summary>
		/// �G���[���b�Z�[�W�̏o��
		/// </summary>
		/// <param name="funcName"> ������ </param>
		void outputErrorMessage(const String& funcName);

	private:

		/// <summary>
		/// �҂�
		/// </summary>
		void wait();

		/// <summary>
		/// �I�u�W�F�N�g�̈ړ�
		/// </summary>
		void moveObject();

		/// <summary>
		/// �I�u�W�F�N�g�̉��o
		/// </summary>
		void actObject();

	};

}