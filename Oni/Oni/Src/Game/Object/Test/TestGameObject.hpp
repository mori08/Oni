#pragma once


#include "../GameObject.hpp"


namespace Oni
{

	/// <summary>
	/// GameObject�̃e�X�g
	/// </summary>
	class TestGameObject : public GameObject
	{
	public:

		TestGameObject();

	private:

		void update() override;

		void draw() const override;

	private:

		void checkDraw(const Vec2& pos) const;

	};

}