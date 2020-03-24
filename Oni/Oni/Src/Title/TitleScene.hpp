#pragma once


#include"../Scene.hpp"


namespace Oni
{
	/// <summary>
	/// タイトルシーン
	/// ButtonManagerを使って他のシーンに遷移
	/// </summary>
	class TitleScene : public MyApp::Scene
	{
		
	public:

		TitleScene(const InitData& init);

		void update() override;

		void draw() const override;

	};
}