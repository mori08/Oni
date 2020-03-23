#pragma once


#include"Button.hpp"


namespace Oni
{
	using ButtonPtr = std::shared_ptr<Button>;

	/// <summary>
	/// Button�̊Ǘ��I��
	/// </summary>
	class ButtonManager
	{
	private:

		// �{�^���̔z��(�{�^���̖��O���L�[)
		std::unordered_map<String, ButtonPtr> mButtonMap;

		// �I�𒆂̃{�^��
		ButtonPtr mSelectedButtonPtr;

	private:

		ButtonManager();

		ButtonManager(const ButtonManager&)            = default;
		ButtonManager& operator=(const ButtonManager&) = default;
		ButtonManager(ButtonManager&&)                 = default;
		ButtonManager& operator=(ButtonManager&&)      = default;

	public:

		/// <summary>
		/// �C���X�^���X�̎擾
		/// </summary>
		/// <returns> �C���X�^���X </returns>
		static ButtonManager& instance()
		{
			static ButtonManager buttonManager;
			return buttonManager;
		}

		/// <summary>
		/// �{�^���̓o�^
		/// </summary>
		/// <param name="name"  > �{�^���̖��O </param>
		/// <param name="region"> �{�^���͈̔� </param>
		void registerButton(const String& name, const Rect& region);

		/// <summary>
		/// �{�^���̓o�^
		/// </summary>
		/// <param name="button"> �{�^�� </param>
		void registerButton(const Button& button);

		/// <summary>
		/// �I�𒆂̃{�^���̕ύX
		/// </summary>
		/// <param name="name"> �{�^���̖��O </param>
		void setSelectedButton(const String& name);

		/// <summary>
		/// �{�^�����������Ƃ��̏����̐ݒ�
		/// </summary>
		/// <param name="name"   > �{�^���̖��O     </param>
		/// <param name="onClick"> �������Ƃ��̏��� </param>
		void setOnClick(const String& name, ButtonOnClick onClick);

		/// <summary>
		/// �I�𒆂̃{�^���̎擾
		/// </summary>
		/// <returns>
		/// �I�𒆂̃{�^��
		/// </returns>
		const Button& getSelectedButton() const
		{
			return *mSelectedButtonPtr;
		}

		/// <summary>
		/// �{�^���̃��X�g����ɂ��܂�
		/// </summary>
		void clearButtonList();

		/// <summary>
		/// �{�^���̑I���y�у{�^���������ꂽ�Ƃ��̏����̌Ăяo��
		/// </summary>
		/// <remarks>
		/// ���͂ɉ������{�^���I���̕ύX��
		/// ����L�[�������ꂽ�Ƃ����̃{�^����OnClick�֐����Ăт܂�
		/// 1�t���[����2�x�ȏ�g��Ȃ��ł��������B
		/// </remarks>
		void update();

	};
}