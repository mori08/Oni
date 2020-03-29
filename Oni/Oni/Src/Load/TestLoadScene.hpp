#pragma once


#include "LoadScene.hpp"


namespace Oni
{

	/// <summary>
	/// ロードシーンのデバッグ用シーン
	/// </summary>
	class TestLoadScene : public LoadScene
	{
	public:

		TestLoadScene(const InitData& init);

	};

}