#pragma once


#include "../GameState.hpp"


namespace Oni
{
	class GameBattleState : public GameState
	{
	public:

		GameBattleState();

	private:

		void update() override;

		void draw() const;

	};
}