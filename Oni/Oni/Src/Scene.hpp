#pragma once


#include<Siv3D.hpp>


// �V�[���̖��O
enum class SceneName
{
	TITLE,    // �^�C�g��

	TEST_LOAD // ���[�h�̃e�X�g
};


// �Q�[���f�[�^
struct GameData
{

};


// �V�[���Ǘ��N���X
using MyApp = SceneManager<SceneName, GameData>;