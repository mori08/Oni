#pragma once


#include"../Scene.hpp"


namespace Oni
{
	/// <summary>
	/// �^�C�g���V�[��
	/// ButtonManager���g���đ��̃V�[���ɑJ��
	/// </summary>
	class TitleScene : public MyApp::Scene
	{
	private:

		// �I�𒆂̃{�^�����w�������`
		RectF mCursor;

	public:

		TitleScene(const InitData& init);

		void update() override;

		void draw() const override;

	};
}