//==========================================================================
// ロードシーン[LoadScene.cpp]
// author: MasyoLab
//==========================================================================
#include "LoadScene.h"
#include "LoadScreen.h"

namespace load_screen
{
	LoadScene::LoadScene() : BaseScene("LoadScene")
	{
		AddComponent(new LoadScreen);
	}

	LoadScene::~LoadScene()
	{
	}
}