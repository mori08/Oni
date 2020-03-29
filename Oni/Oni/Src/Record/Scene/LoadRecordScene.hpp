#pragma once


#include "../../Load/LoadScene.hpp"


namespace Oni
{
	/// <summary>
	/// レコードをテキストファイルからロードするシーン
	/// </summary>
	class LoadRecordScene : public LoadScene
	{
	public:

		LoadRecordScene(const InitData& init);

	};
}
