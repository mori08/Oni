#pragma once


#include <future>
#include "../Scene.hpp"


namespace Oni
{
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

		LoadScene(const InitData& init);

		virtual ~LoadScene();


	private:

		void update() override;

		virtual void draw() const override;

		void drawFadeIn(double) const override;

		void drawFadeOut(double) const override;

	protected:

		/// <summary>
		/// mLoadThreadで動かす関数
		/// </summary>
		/// <remarks>
		/// ロード中はゲームを終了させることができなくなるので
		/// 現実的な時間で終わる処理を書く.
		/// </remarks>
		virtual SceneName load() = 0;

	};

}