#include "LoadScene.hpp"


namespace
{
	// �e�L�X�g��\��������W
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
		// �X���b�h�̏󋵂��擾
		auto status = mLoadThread.wait_for(std::chrono::microseconds(0));

		// �X���b�h���I�����Ă�����V�[���J��
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