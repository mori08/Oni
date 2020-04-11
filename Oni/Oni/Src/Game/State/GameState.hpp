#pragma once


#include<Siv3D.hpp>


namespace Oni
{
	/// <summary>
	/// GameManager�̏�Ԃ�����
	/// </summary>
	class GameState
	{
	public:

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// �`��
		/// </summary>
		virtual void draw() const = 0;

	};

	using GameStatePtr = std::unique_ptr<GameState>;
}