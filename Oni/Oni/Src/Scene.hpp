#pragma once


#include<Siv3D.hpp>


// シーンの名前
enum class SceneName
{
	TITLE // タイトル
};


// ゲームデータ
struct GameData
{

};


// シーン管理クラス
using MyApp = SceneManager<SceneName, GameData>;