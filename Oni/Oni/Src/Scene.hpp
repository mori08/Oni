#pragma once


#include<Siv3D.hpp>


// シーンの名前
enum class SceneName
{
	TITLE,       // タイトル

	TEST_LOAD,   // ロードのテスト

	LOAD_RECORD, // レコードのロード
	SAVE_RECORD  // レコードのセーブ
};


// ゲームデータ
struct GameData
{

};


// シーン管理クラス
using MyApp = SceneManager<SceneName, GameData>;