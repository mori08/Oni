#pragma once


#include<Siv3D.hpp>


namespace Oni
{
	using ButtonOnClick = std::function<void()>;

	/// <summary>
	/// �{�^��
	/// ���ButtonManager�Ŏg�p����
	/// </summary>
	class Button
	{
	private:

		// ���O
		const String mName;

		// �͈�
		const Rect mRegion;

		// �����ꂽ�Ƃ��̏���
		ButtonOnClick mOnClick;

	public:

		/// <summary>
		/// �{�^���̖��O�̎擾
		/// </summary>
		/// <returns> �{�^���̖��O </returns>
		const String& getName() const
		{
			return mName;
		}

		/// <summary>
		/// �{�^���͈̔͂̎擾
		/// </summary>
		/// <returns> �{�^���̖��O </returns>
		const Rect& getRegion() const
		{
			return mRegion;
		}

		/// <summary>
		/// �������Ƃ��̏����̐ݒ�
		/// </summary>
		/// <param name="onClick"> �������Ƃ��̏��� </param>
		void setOnClick(const ButtonOnClick& onClick)
		{
			mOnClick = onClick;
		}

		/// <summary>
		/// �������Ƃ��̏���
		/// </summary>
		void OnClick() const
		{
			mOnClick();
		}

	};
}