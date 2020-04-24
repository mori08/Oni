#pragma once


#include <Siv3D.hpp>


namespace Oni
{
	/// <summary>
	/// Event��Adventure�ŕ\������E�B���h�E
	/// </summary>
	/// <remarks>
	/// �������������邽��Window�łȂ�Board
	/// </remarks>
	class GameBoard
	{
	protected:

		// �E�B���h�E�͈̔�
		const RoundRect mRegion;

	public:

		/// <summary>
		/// �E�B���h�E
		/// </summary>
		/// <param name="region"> �E�B���h�E�͈̔� </param>
		GameBoard(const Rect& region);

		/// <summary>
		/// ���̃E�B���h�E���I�����ꂽ�Ƃ��̏���
		/// </summary>
		virtual void select() = 0;

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// �I�����̍X�V
		/// </summary>
		virtual void selectedUpdate() = 0;

		/// <summary>
		/// �E�B���h�E�w�i�̕`��
		/// </summary>
		void drawBoard() const;

		/// <summary>
		/// �`��
		/// </summary>
		virtual void draw() const = 0;

	};
}