#pragma once


#include "../../Load/LoadScene.hpp"


namespace Oni
{

	/// <summary>
	/// csvファイルから地形やオブジェクトをロード
	/// </summary>
	class LoadGameScene : public LoadScene
	{
	public:

		LoadGameScene(const InitData& init);

	};

}
