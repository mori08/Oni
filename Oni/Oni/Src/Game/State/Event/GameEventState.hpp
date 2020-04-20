#pragma once


#include "../GameState.hpp"


namespace Oni
{
	class GameEventState : public GameState
	{
	public:

		GameEventState(const String& eventName);

	private:

		void update() override;

		void draw() const override;

	};
}