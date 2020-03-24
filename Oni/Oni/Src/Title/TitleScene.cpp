#include "TitleScene.hpp"


namespace Oni
{

	TitleScene::TitleScene(const InitData& init)
		: IScene(init)
	{
	}


	void TitleScene::update()
	{

	}


	void TitleScene::draw() const
	{
		TextureAsset(U"Title").draw();
	}

}
