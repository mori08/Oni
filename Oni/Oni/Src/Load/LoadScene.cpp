#include "LoadScene.hpp"


namespace
{
	// テキストを表示する座標
	constexpr Point TEXT_POS = Point(530, 445);
}


namespace Oni
{

	LoadScene::LoadScene(const InitData& init, LoadFunction loadFunc)
		: IScene(init)
	{
		mLoadThread = std::async
		(
			std::launch::async,
			loadFunc
		);
	}


	LoadScene::~LoadScene()
	{

	}


	void LoadScene::update()
	{
		// スレッドの状況を取得
		auto status = mLoadThread.wait_for(std::chrono::microseconds(0));

		// スレッドが終了していたらシーン遷移
		if (status != std::future_status::timeout)
		{
			auto sceneName = mLoadThread.get();

			if (!changeScene(sceneName))
			{
				changeScene(SceneName::TITLE);
			}
		}
	}


	void LoadScene::draw() const
	{
		FontAsset(U"20")(U"Loading").draw(TEXT_POS);
	}


	void LoadScene::drawFadeIn(double) const
	{
		draw();
	}


	void LoadScene::drawFadeOut(double) const
	{
		draw();
	}

}