//==========================================================================
// ���C���֐� [main.cpp]
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
//	���C���֐�
//==========================================================================
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// CRT���������[�N�ӏ����o
	// _CrtSetBreakAlloc(35556);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	std::unique_ptr<mslib::component::Component> system_parent(new mslib::component::Component("System Parent"));
	std::unique_ptr<mslib::int2> aspect(new mslib::int2(16, 9));
	int return_message = 0;

	// �}�l�[�W���[�̐e�R���|�[�l���g���w�肵�܂�
	mslib::manager::Manager::SetManagerComponent(system_parent->ThisComponent());

	auto aspectObject = system_parent->AddComponent(new mslib::aspect::AspectRatio);

	// �w�肵�����̃E�B���h�E�T�C�Y�̐���
	for (int i = 0; i < 10; i++)
	{
		if (i < 3)
			continue;

		// �w�肵���A�X�y�N�g�䂩�ǂ����̃Z�b�g&�o�^
		aspectObject->Search((*aspect * 12) * (i + 1), *aspect);
	}

#if defined(_DEBUG) || defined(DEBUG)
	auto gameWindow = system_parent->AddComponent(new main_system::GameWindow("GameWindow", "GameWindow"));

	// �Q�[���E�B���h�E
	return_message = gameWindow->Window(hInstance, aspectObject->Get(3).m_size, false, nCmdShow);
#else
	auto launcher = system_parent->AddComponent(new main_system::Launcher("Config", "Config"));

	// �������ꂽ�E�B���h�E�T�C�Y�̏��̓���
	for (int i = 0; i < aspectObject->Size(); i++)
		launcher->SetAspectRatio(aspectObject->Get(i));

	// �V�X�e���E�B���h�E
	if (launcher->Window(hInstance, nCmdShow))
	{
		// �E�B���h�E���[�h�̎擾
		bool bWinMode = launcher->GetWindowMode();

		// �E�B���h�E�T�C�Y���擾
		*aspect = launcher->GetWindowSize();

		// �����`���[��j��
		system_parent->DestroyComponent(launcher);

		// �Q�[���̃E�B���h�E��ǉ�
		auto gameWindow = system_parent->AddComponent(new main_system::GameWindow("GameWindow", "GameWindow"));

		// �Q�[���E�B���h�E
		return_message = gameWindow->Window(hInstance, *aspect, bWinMode, nCmdShow);
	}
#endif
	mslib::manager::Manager::ReleaseManager();
	return return_message;
}
