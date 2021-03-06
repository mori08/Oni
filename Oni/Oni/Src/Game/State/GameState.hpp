#pragma once


#include<Siv3D.hpp>


namespace Oni
{
	/// <summary>
	/// GameManagerの状態を示す
	/// </summary>
	class GameState
	{
	public:

		/// <summary>
		/// 更新
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// 描画
		/// </summary>
		virtual void draw() const = 0;

	};

	using GameStatePtr = std::unique_ptr<GameState>;
}