#pragma once


#include "../../Load/LoadScene.hpp"


namespace Oni
{
	/// <summary>
	/// ステージを使うシーン
	/// 必ずLoadGameSceneから遷移する
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
