#include "TitleScene.hpp"
#include "../MyColor.hpp"
#include "../MyLibrary.hpp"
#include "../Button/ButtonManager.hpp"


namespace
{
	// �{�^���̃T�C�Y
	constexpr Size BUTTON_SIZE(150, 30);
	// �u�͂��߂���v�{�^��
	const Oni::Button NEWGAME_BUTTON (U"�͂��߂���", Oni::getRectFromCenter(Point(320, 300), BUTTON_SIZE));
	// �u�Â�����v�{�^��
	const Oni::Button CONTINUE_BUTTON(U"�Â�����", Oni::getRectFromCenter(Point(320, 380), BUTTON_SIZE));
	// �{�^���̃��X�g
	const Array<Oni::Button> BUTTON_LIST
	{
		NEWGAME_BUTTON,
		CONTINUE_BUTTON
	};

	// �J�[�\���ړ��̔�
	constexpr double CURSOR_RATE = 0.005;
}


namespace Oni
{

	TitleScene::TitleScene(const InitData& init)
		: IScene(init)
		, mCursor(CONTINUE_BUTTON.getRegion())
	{
		// �{�^���̃��Z�b�g
		ButtonManager::instance().clearButtonList();

		// �{�^���̐ݒ�
		ButtonManager::instance().registerButton(NEWGAME_BUTTON);
		ButtonManager::instance().registerButton(CONTINUE_BUTTON);

		// �{�^���̈ʒu�֌W�̐ݒ�
		ButtonManager::instance().setVerticalAdjacentButton(NEWGAME_BUTTON.getName(), CONTINUE_BUTTON.getName());

		// �{�^�����������Ƃ��̏����̐ݒ�
		ButtonManager::instance().setOnClick
		(
			NEWGAME_BUTTON.getName(),
			[this]() { changeScene(SceneName::TEST_LOAD); }
		);

		// �I�𒆂̃{�^���̐ݒ�
		ButtonManager::instance().setSelectedButton(CONTINUE_BUTTON.getName());
	}


	void TitleScene::update()
	{
		// �J�[�\���̈ړ�
		internalDividingPoint
		(
			mCursor.pos,
			ButtonManager::instance().getSelectedButton().getRegion().pos,
			CURSOR_RATE
		);

		// �{�^���̍X�V
		ButtonManager::instance().update();

		changeScene(SceneName::TEST_LOAD);
	}


	void TitleScene::draw() const
	{
		TextureAsset(U"Title").draw();

		// �{�^���ƃJ�[�\���̕`��
		mCursor.draw(MyWhite);
		for (const auto& button : BUTTON_LIST)
		{
			Color color = (button.getName() == ButtonManager::instance().getSelectedButton().getName())
				? MyBlack
				: MyWhite;

			FontAsset(U"20")(button.getName()).drawAt(button.getRegion().center(), color);
		}
	}

}
