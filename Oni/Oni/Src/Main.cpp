#include"MyLibrary.hpp"
#include"MyColor.hpp"

// �V�[��
#include"Title/TitleScene.hpp"
#include"Load/TestLoadScene.hpp"
#include"Record/Scene/LoadRecordScene.hpp"
#include"Record/Scene/SaveRecordScene.hpp"


namespace
{

	// ��ʃT�C�Y
	constexpr Size WINDOW_SIZE(640, 480);
}


void Main()
{
	// �E�B���h�E�̐ݒ�
	Window::Resize(WINDOW_SIZE);
	Window::SetTitle(U"�S");

	// �`��ݒ�
	Scene::SetBackground(Oni::MyBlack);
	Scene::Resize(WINDOW_SIZE);

	// �A�Z�b�g�Ǘ�
	FontAsset::Register(U"10", 10, Typeface::Medium);
	FontAsset::Register(U"15", 15, Typeface::Medium);
	FontAsset::Register(U"20", 20, Typeface::Medium);
	FontAsset::Register(U"30", 30, Typeface::Medium);
	FontAsset::Register(U"40", 40, Typeface::Medium);
	Oni::registerAsset(U"Asset/");

	// �V�[���̊Ǘ�
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