#pragma once


#include<Siv3D.hpp>


namespace Oni
{
	class Button;
	using ButtonPtr     = std::shared_ptr<Button>;
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

		// �אڃ{�^��
		std::list<std::pair<Key, ButtonPtr>> mAdjacentButtonMap;

		// �����ꂽ�Ƃ��̏���
		ButtonOnClick mOnClick;

	public:

		/// <summary>
		/// �{�^��
		/// </summary>
		/// <param name="name">   ���O </param>
		/// <param name="region"> �͈� </param>
		Button(const String& name, const Rect& region)
			: mName(name)
			, mRegion(region)
			, mOnClick([](){})
		{
		}

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
		/// �אڂ���{�^���̐ݒ�
		/// </summary>
		/// <param name="key"      > �Ή�����L�[   </param>
		/// <param name="buttonPtr"> �אڂ���{�^�� </param>
		void setAdjacentButton(const Key& key, ButtonPtr buttonPtr)
		{
			mAdjacentButtonMap.emplace_back(key, buttonPtr);
		}

		/// <summary>
		/// ���͂ɉ������אڃ{�^���̎擾
		/// </summary>
		/// <returns>
		/// ���͂ɉ������אڃ{�^��
		/// </returns>
		Optional<ButtonPtr> getAdjacentButton() const;

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