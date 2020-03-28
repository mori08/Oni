#include "LoadScene.hpp"


namespace
{
	// テキストを表示する座標
	constexpr Point TEXT_POS = Point(530, 445);
}


Oni::LoadScene::LoadScene(const InitData& init)
	: IScene(init)
{
	mLoadThread = std::async
	(
		std::launch::async,
		[this]()
		{
			return load();
		}
	);
}


Oni::LoadScene::~LoadScene()
{
	mLoadThread.get();
}


void Oni::LoadScene::update()
{
	// スレッドの状況を取得
	auto status = mLoadThread.wait_for(std::chrono::microseconds(0));

	// スレッドが終了していたらシーン遷移
	if (status == std::future_status::ready)
	{
		auto sceneName = mLoadThread.get();

		if (!changeScene(sceneName))
		{
			changeScene(SceneName::TITLE);
		}
	}
}


void Oni::LoadScene::draw() const
{
	FontAsset(U"20")(U"Loading").draw(TEXT_POS);
}


void Oni::LoadScene::drawFadeIn(double) const
{
	draw();
}


void Oni::LoadScene::drawFadeOut(double) const
{
	draw();
}
