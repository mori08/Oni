#pragma once


#include<Siv3D.hpp>


// �V�[���̖��O
enum class SceneName
{
	TITLE,       // �^�C�g��

	TEST_LOAD,   // ���[�h�̃e�X�g

	LOAD_RECORD, // ���R�[�h�̃��[�h
	SAVE_RECORD  // ���R�[�h�̃Z�[�u
};


// �Q�[���f�[�^
struct GameData
{

};


// �V�[���Ǘ��N���X
using MyApp = SceneManager<SceneName, GameData>;