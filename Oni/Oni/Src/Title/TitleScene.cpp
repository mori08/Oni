#include "TitleScene.hpp"


namespace
{
	// �^�C�g�����S��\��������W
	constexpr Point TITLE_LOGO_POS(320, 100);
}


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
		Scene::Rect().draw(Color(30));
		TextureAsset(U"TitleLogo").drawAt(TITLE_LOGO_POS);
	}

}
