//==========================================================================
// メイン関数 [main.cpp]
// author : MasyoLab
//==========================================================================
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#define _GLIBCXX_DEBUG
#include "dxlib.h"
#include "GameWindow.h"
#include "Launcher.h"

//==========================================================================
//	メイン関数
//==========================================================================
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// CRTメモリリーク箇所検出
	// _CrtSetBreakAlloc(35556);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	std::unique_ptr<mslib::component::Component> system_parent(new mslib::component::Component("System Parent"));
	std::unique_ptr<mslib::int2> aspect(new mslib::int2(16, 9));
	int return_message = 0;

	// マネージャーの親コンポーネントを指定します
	mslib::manager::Manager::SetManagerComponent(system_parent->ThisComponent());

	auto aspectObject = system_parent->AddComponent(new mslib::aspect::AspectRatio);

	// 指定した数のウィンドウサイズの生成
	for (int i = 0; i < 10; i++)
	{
		if (i < 3)
			continue;

		// 指定したアスペクト比かどうかのセット&登録
		aspectObject->Search((*aspect * 12) * (i + 1), *aspect);
	}

#if defined(_DEBUG) || defined(DEBUG)
	auto gameWindow = system_parent->AddComponent(new main_system::GameWindow("GameWindow", "GameWindow"));

	// ゲームウィンドウ
	return_message = gameWindow->Window(hInstance, aspectObject->Get(3).m_size, false, nCmdShow);
#else
	auto launcher = system_parent->AddComponent(new main_system::Launcher("Config", "Config"));

	// 生成されたウィンドウサイズの情報の入力
	for (int i = 0; i < aspectObject->Size(); i++)
		launcher->SetAspectRatio(aspectObject->Get(i));

	// システムウィンドウ
	if (launcher->Window(hInstance, nCmdShow))
	{
		// ウィンドウモードの取得
		bool bWinMode = launcher->GetWindowMode();

		// ウィンドウサイズを取得
		*aspect = launcher->GetWindowSize();

		// ランチャーを破棄
		system_parent->DestroyComponent(launcher);

		// ゲームのウィンドウを追加
		auto gameWindow = system_parent->AddComponent(new main_system::GameWindow("GameWindow", "GameWindow"));

		// ゲームウィンドウ
		return_message = gameWindow->Window(hInstance, *aspect, bWinMode, nCmdShow);
	}
#endif
	mslib::manager::Manager::ReleaseManager();
	return return_message;
}
