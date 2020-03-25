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
	private:

		// 選択中のボタンを指す長方形
		RectF mCursor;

	public:

		TitleScene(const InitData& init);

		void update() override;

		void draw() const override;

	};
}