#include"MyLibrary.hpp"
#include"MyColor.hpp"

// シーン
#include"Title/TitleScene.hpp"
#include"Load/TestLoadScene.hpp"
#include"Record/Scene/LoadRecordScene.hpp"
#include"Record/Scene/SaveRecordScene.hpp"


namespace
{

	// 画面サイズ
	constexpr Size WINDOW_SIZE(640, 480);
}


void Main()
{
	// ウィンドウの設定
	Window::Resize(WINDOW_SIZE);
	Window::SetTitle(U"鬼");

	// 描画設定
	Scene::SetBackground(Oni::MyBlack);
	Scene::Resize(WINDOW_SIZE);

	// アセット管理
	FontAsset::Register(U"10", 10, Typeface::Medium);
	FontAsset::Register(U"15", 15, Typeface::Medium);
	FontAsset::Register(U"20", 20, Typeface::Medium);
	FontAsset::Register(U"30", 30, Typeface::Medium);
	FontAsset::Register(U"40", 40, Typeface::Medium);
	Oni::registerAsset(U"Asset/");

	// シーンの管理
	MyApp sceneManager;
	sceneManager.add<Oni::TitleScene>     (SceneName::TITLE);
	sceneManager.add<Oni::TestLoadScene>  (SceneName::TEST_LOAD);
	sceneManager.add<Oni::LoadRecordScene>(SceneName::LOAD_RECORD);
	sceneManager.add<Oni::SaveRecordScene>(SceneName::SAVE_RECORD);

	while (System::Update())
	{
		sceneManager.update();

		Oni::showFps();
	}
}