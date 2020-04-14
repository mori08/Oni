#pragma once


#include"../../../Slice/SliceTexture.hpp"


namespace Oni
{
	/// <summary>
	/// GameObject������EventState�p�̃f�[�^
	/// </summary>
	class ObjectEventData
	{
	private:

		// �C�x���g�p�֐�
		std::unordered_map<String, std::function<void()>> mActMap;

		// �ړ�����
		double mMoveSecond;

	public:

		ObjectEventData(SliceTexture& slide);

		/// <summary>
		/// �X�V
		/// </summary>
		void update();

		/// <summary>
		/// �ړ����Ԃ̐ݒ�
		/// </summary>
		/// <param name="moveSecond"> �ړ����� </param>
		void setMoveSecond(double moveSecond)
		{
			mMoveSecond = moveSecond;
		}

		/// <summary>
		/// �ړ������ǂ�������
		/// </summary>
		/// <returns> true �̂Ƃ��ړ��� </returns>
		bool isMoving() const
		{
			return mMoveSecond > 0;
		}

		/// <summary>
		/// �C�x���g�p�֐��̐ݒ�
		/// </summary>
		/// <param name="actName"> ���O           </param>
		/// <param name="actFunc"> �C�x���g�p�֐� </param>
		void setAct(const String& actName, const std::function<void()>& actFunc)
		{
			mActMap[actName] = actFunc;
		}

		/// <summary>
		/// �C�x���g�p�֐������݂��邩�m�F
		/// </summary>
		/// <param name="actName"> ���O </param>
		/// <returns> ���݂���Ƃ� true , ���Ȃ��Ƃ� false </returns>
		bool isExistAct(const String& actName) const
		{
			return mActMap.count(actName);
		}

		/// <summary>
		/// �C�x���g�p�֐������s
		/// </summary>
		/// <param name="actName"> ���O </param>
		void act(const String& actName)
		{
			mActMap[actName]();
		}

	};
}