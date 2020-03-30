#pragma once


#include "../../Load/LoadScene.hpp"


namespace Oni
{
	/// <summary>
	/// �X�e�[�W���g���V�[��
	/// �K��LoadGameScene����J�ڂ���
	/// </summary>
	class GameScene : public MyApp::Scene
	{
	public:

		GameScene(const InitData& init);

	private:

		void update();

		void draw() const;

	};
}
