#pragma once


#include "../GameBoard.hpp"
#include "../../../Slice/Linearly.hpp"


namespace Oni
{
	/// <summary>
	/// �e�L�X�g��\������E�B���h�E
	/// </summary>
	/// <remarks>
	/// �|�����[�t�B�Y�����g�킸�C�x���g�ł��g�p
	/// </remarks>
	class TextBoard : public GameBoard
	{
	private:

		// �\��������
		Linearly<size_t> mDrawAbleLength;

		// �A�C�R���̉摜��
		const String mIconName;

		// �b����̖��O
		const String mSpeakerName;

		// �e�L�X�g
		const String mText;

	public:

		/// <summary>
		/// �e�L�X�g�E�B���h�E
		/// </summary>
		/// <param name="iconName"   > �A�C�R���̉摜�� </param>
		/// <param name="speakerName"> �b����̖��O     </param>
		/// <param name="text"       > �e�L�X�g         </param>
		TextBoard(const String& iconName, const String& speakerName, const String& text);

		void select() override;

		void update() override;

		bool selectedUpdate() override;

		void draw() const override;

	};
}