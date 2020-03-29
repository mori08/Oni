#pragma once


#include "../../Load/LoadScene.hpp"


namespace Oni
{
	
	/// <summary>
	/// レコードをテキストファイルにセーブするシーン
	/// </summary>
	class SaveRecordScene : public LoadScene
	{
	public:

		SaveRecordScene(const InitData& init);

	};

}