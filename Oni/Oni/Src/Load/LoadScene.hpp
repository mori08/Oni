#pragma once


#include <future>
#include "../Scene.hpp"


namespace Oni
{
	using LoadFunction = std::function<SceneName()>;
	using ErrorMessage = Optional<String>;


	/// <summary>
	/// ���Ԃ̂����鏈����ʃX���b�h�ōs���V�[��
	/// �����̓��e��load�֐�, �I�����̏�����complete�֐���
	/// �I�[�o�[���[�h���Ĕh���N���X���쐬����.
	/// </summary>
	class LoadScene : public MyApp::Scene
	{
	private:

		// ���[�h����X���b�h
		std::future<SceneName> mLoadThread;

	public:

		LoadScene(const InitData& init, LoadFunction loadFunc);

		virtual ~LoadScene();


	private:

		void update() override;

		virtual void draw() const override;

		void drawFadeIn(double) const override;

		void drawFadeOut(double) const override;

	};

}