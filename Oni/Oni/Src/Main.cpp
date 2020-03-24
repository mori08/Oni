#include"MyLibrary.hpp"

// �V�[��
#include"Title/TitleScene.hpp"


void Main()
{
	// �E�B���h�E�̐ݒ�
	Window::Resize(640, 480);
	Window::SetTitle(U"�S");

	// �A�Z�b�g�Ǘ�
	FontAsset::Register(U"10", 10, Typeface::Medium);
	FontAsset::Register(U"15", 15, Typeface::Medium);
	FontAsset::Register(U"20", 20, Typeface::Medium);
	FontAsset::Register(U"30", 30, Typeface::Medium);
	FontAsset::Register(U"40", 40, Typeface::Medium);
	Oni::registerAsset(U"Asset/");

	// �V�[���̊Ǘ�
	MyApp sceneManager;
	sceneManager.add<Oni::TitleScene>(SceneName::TITLE);

	while (System::Update())
	{
		sceneManager.update();

		Oni::showFps();
	}
}