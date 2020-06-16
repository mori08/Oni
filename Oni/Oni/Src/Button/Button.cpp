#include "Button.hpp"


namespace Oni
{

	Optional<ButtonPtr> Button::getAdjacentButton() const
	{
		for (const auto& keyAndButton : mAdjacentButtonMap)
		{
			if (keyAndButton.first.up())
			{
				return keyAndButton.second;
			}
		}

		return none;
	}

}
