#pragma once


#include <future>
#include "../Scene.hpp"


namespace Oni
{
	using LoadFunction = std::function<SceneName()>;
	using ErrorMessage = Optional<String>;


	/// <summary>
	/// 時間のかかる処理を別スレッドで行うシーン
	/// 処理の内容はload関数, 終了時の処理はcomplete関数を
	/// オーバーロードして派生クラスを作成する.
	/// </summary>
	class LoadScene : public MyApp::Scene
	{
	private:

		// ロードするスレッド
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