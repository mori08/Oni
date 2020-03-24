#include"MyLibrary.hpp"

// シーン
#include"Title/TitleScene.hpp"


void Main()
{
	// ウィンドウの設定
	Window::Resize(640, 480);
	Window::SetTitle(U"鬼");

	// アセット管理
	FontAsset::Register(U"10", 10, Typeface::Medium);
	FontAsset::Register(U"15", 15, Typeface::Medium);
	FontAsset::Register(U"20", 20, Typeface::Medium);
	FontAsset::Register(U"30", 30, Typeface::Medium);
	FontAsset::Register(U"40", 40, Typeface::Medium);
	Oni::registerAsset(U"Asset/");

	// シーンの管理
	MyApp sceneManager;
	sceneManager.add<Oni::TitleScene>(SceneName::TITLE);

	while (System::Update())
	{
		sceneManager.update();

		Oni::showFps();
	}
}