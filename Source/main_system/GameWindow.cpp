//==========================================================================
// �Q�[���E�B���h�E [GameWindow.cpp]
// author : MasyoLab
//==========================================================================
#include "GameWindow.h"
#include "Screen.h"
#include "resource.h"

namespace main_system
{
	//==========================================================================
	// �萔��`
	//==========================================================================
	constexpr DWORD WINDOW_STYLE = (WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX));
	constexpr int __fps = 60;
	constexpr long long __time_per_frame = (long long)1000 / __fps;

	//==========================================================================
	// �֐�
	//==========================================================================
	// FPS�Œ�
	static const bool FpsFixed();

	GameWindow::GameWindow()
	{
		AddComponent(new mslib::window::WindowsAPI("Default", "Default"));
		SetComponentName("GameWindow");
	}

	GameWindow::GameWindow(const std::string& _class_name, const std::string& _window_name)
	{
		AddComponent(new mslib::window::WindowsAPI(_class_name, _window_name));
		SetComponentName("GameWindow");
	}

	GameWindow::~GameWindow()
	{
	}

	int GameWindow::Window(HINSTANCE _Instance, const mslib::int2& _data, bool _Mode, int _CmdShow)
	{
		RECT wr, dr;
		auto windows_api = GetComponent<mslib::window::WindowsAPI>();

		windows_api->SetWindowClass(CS_VREDRAW | CS_HREDRAW, WndProc, nullptr, nullptr, nullptr, _Instance);

		// �}�E�X�J�[�\���\���ݒ�
		ShowCursor(true);

		// Direct3D�I�u�W�F�N�g�̍쐬 �Ɏ��s���I�� 
		auto device = mslib::manager::Manager::GetDevice();
		device->Init();

		// �E�B���h�ERECT
		wr = windows_api->GetWindowRECT(WINDOW_STYLE, _data.x, _data.y, false);

		//�f�X�N�g�b�v�T�C�Y�K��
		GetWindowRect(GetDesktopWindow(), &dr);

		// �����ʒu�C��
		wr.left = dr.right / 2;
		wr.top = dr.bottom / 2;
		wr.left -= wr.right / 2;
		wr.top -= wr.bottom / 2;

		// �E�B���h�E�̐���
		windows_api->Create(WINDOW_STYLE, wr, nullptr, nullptr, nullptr, _CmdShow);

		// �F�X���s�������I��
		if (device->CreateWindowMode(_data, _Mode))
			return -1;

		// �f�o�C�X�ɃE�B���h�E�n���h����������
		device->SetHwnd(windows_api->GetHWND());

		// �Q�[�����[�v
		return GameLoop(_Instance, windows_api->GetHWND());
	}

	LRESULT CALLBACK GameWindow::WndProc(HWND _Wnd, UINT _Msg, WPARAM _wParam, LPARAM _lParam)
	{
		auto device = mslib::manager::Manager::GetDevice();
		device->GetWindowsSize();
		if (device->GetHwnd() != nullptr)
			_Wnd = device->GetHwnd();

		if (mslib::imgui::ImGui_WndProcHandler(_Wnd, _Msg, _wParam, _lParam))
			return true;

		// ���b�Z�[�W�̎�ނɉ����ď����𕪊򂵂܂��B
		switch (_Msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:	// �L�[����
			switch (_wParam)
			{
			case VK_ESCAPE:
				// [ESC]�L�[�������ꂽ��
				if (MessageBox(_Wnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) == IDYES)
					DestroyWindow(_Wnd);	// �E�B���h�E��j��
				else
					return 0;	// �������̎�
			}
			break;
		case WM_LBUTTONDOWN:
			SetFocus(_Wnd);
			break;
		case WM_CLOSE:	// �~�{�^����������
			if (MessageBox(_Wnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) == IDYES)
				DestroyWindow(_Wnd);	// �E�B���h�E��j��
			else
				return 0;	// �������̎�
			break;
		default:
			break;
		}

		//�f�t�H���g�̏���
		return mslib::imgui::SetMenu(_Wnd, _Msg, _wParam, _lParam, device->Getd3ddevice(), &device->Getd3dpp());
	}

	int GameWindow::GameLoop(HINSTANCE _Instance, HWND _hWnd)
	{
		auto windows_api = GetComponent<mslib::window::WindowsAPI>();
		auto screen = AddComponent(new Screen);
		MSG& msg = windows_api->GetMSG(); // ���b�Z�[�W�\����

		if (screen->Init(_Instance, _hWnd))
		{
			windows_api->ErrorMessage("�������Ɏ��s���܂���");
			return-1;
		}

		// ���b�Z�[�W���[�v
		for (;;)
		{
			// ���������Ă��X���[
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					break;

				//���b�Z�[�W����
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				continue;
			}

			if (!FpsFixed())
				continue;

			if (screen->Update())
			{
				windows_api->ErrorMessage("�������Ɏ��s���܂���");
				return-1;
			}

			//�`��
			screen->Draw();
		}

		return (int)msg.wParam;
	}

	const bool FpsFixed()
	{
		static auto start = std::chrono::system_clock::now();

		while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() < __time_per_frame);

		start = std::chrono::system_clock::now();

		return true;
	}
}