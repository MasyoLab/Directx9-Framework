//==========================================================================
// �L�[�{�[�h���͏��� [DinputKeyboard.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "DirectInput.h"

_MSLIB_BEGIN

namespace dinput_keyboard
{
	class Button
	{
		static constexpr int __MaxKey = 256;
	public:
		static constexpr int
			KEY_SPACE = DIK_SPACE, // Spause
			KEY_A = DIK_A, // A�`Z
			KEY_B = DIK_B, // A�`Z
			KEY_C = DIK_C, // A�`Z
			KEY_D = DIK_D, // A�`Z
			KEY_E = DIK_E, // A�`Z
			KEY_F = DIK_F, // A�`Z
			KEY_G = DIK_G, // A�`Z
			KEY_H = DIK_H, // A�`Z
			KEY_I = DIK_I, // A�`Z
			KEY_J = DIK_J, // A�`Z
			KEY_K = DIK_K, // A�`Z
			KEY_L = DIK_L, // A�`Z
			KEY_N = DIK_N, // A�`Z
			KEY_M = DIK_M, // A�`Z
			KEY_O = DIK_O, // A�`Z
			KEY_P = DIK_P, // A�`Z
			KEY_Q = DIK_Q, // A�`Z
			KEY_R = DIK_R, // A�`Z
			KEY_S = DIK_S, // A�`Z
			KEY_T = DIK_T, // A�`Z
			KEY_U = DIK_U, // A�`Z
			KEY_V = DIK_V, // A�`Z
			KEY_W = DIK_W, // A�`Z
			KEY_X = DIK_X, // A�`Z
			KEY_Y = DIK_Y, // A�`Z
			KEY_Z = DIK_Z, // A�`Z
			KEY_1 = DIK_1, // ����(���C���E�L�[�{�[�h)
			KEY_2 = DIK_2, // ����(���C���E�L�[�{�[�h)
			KEY_3 = DIK_3, // ����(���C���E�L�[�{�[�h)
			KEY_4 = DIK_4, // ����(���C���E�L�[�{�[�h)
			KEY_5 = DIK_5, // ����(���C���E�L�[�{�[�h)
			KEY_6 = DIK_6, // ����(���C���E�L�[�{�[�h)
			KEY_7 = DIK_7, // ����(���C���E�L�[�{�[�h)
			KEY_8 = DIK_8, // ����(���C���E�L�[�{�[�h)
			KEY_9 = DIK_9, // ����(���C���E�L�[�{�[�h)
			KEY_0 = DIK_0, // ����(���C���E�L�[�{�[�h)
			KEY_MINUS = DIK_MINUS, // [-] (���C���E�L�[�{�[�h)
			KEY_EQUALS = DIK_EQUALS, // [��] (���C���E�L�[�{�[�h)
			KEY_RETURN = DIK_RETURN, // Enter(���C���E�L�[�{�[�h)
			KEY_F1 = DIK_F1, // F1�`F12
			KEY_F2 = DIK_F2, // F1�`F12
			KEY_F3 = DIK_F3, // F1�`F12
			KEY_F4 = DIK_F4, // F1�`F12
			KEY_F5 = DIK_F5, // F1�`F12
			KEY_F6 = DIK_F6, // F1�`F12
			KEY_F7 = DIK_F7, // F1�`F12
			KEY_F8 = DIK_F8, // F1�`F12
			KEY_F9 = DIK_F9, // F1�`F12
			KEY_F10 = DIK_F10, // F1�`F12
			KEY_F11 = DIK_F11, // F1�`F12
			KEY_F12 = DIK_F12, // F1�`F12
			KEY_DOWN = DIK_DOWN, // [��]
			KEY_LEFT = DIK_LEFT, // [��]
			KEY_RIGHT = DIK_RIGHT, // [��]
			KEY_UP = DIK_UP, // [��]
			KEY_CAPITAL = DIK_CAPITAL, // Caps Lock
			KEY_TAB = DIK_TAB, // TAB
			KEY_ESCAPE = DIK_ESCAPE, // Esc
			KEY_BACK = DIK_BACK, // BackSpace
			KEY_INSERT = DIK_INSERT, // insert
			KEY_DELETE = DIK_DELETE, // Delete
			KEY_HOME = DIK_HOME, // Home
			KEY_END = DIK_END, // End
			KEY_PRIOR = DIK_PRIOR, // PageUp
			KEY_NEXT = DIK_NEXT, // PageDown
			KEY_SYSRQ = DIK_SYSRQ, // SysRq
			KEY_SCROLL = DIK_SCROLL, // ScrollLock
			KEY_PAUSE = DIK_PAUSE, // Pause
			KEY_LCONTROL = DIK_LCONTROL, // ��Ctrl
			KEY_RCONTROL = DIK_RCONTROL, // �ECtrl
			KEY_LMENU = DIK_LMENU, // ��Alt
			KEY_RMENU = DIK_RMENU, // �EAlt
			KEY_LSHIFT = DIK_LSHIFT, // ��Shift
			KEY_RSHIFT = DIK_RSHIFT, // �EShift
			KEY_LWIN = DIK_LWIN, // ��Windows
			KEY_RWIN = DIK_RWIN, // �EWindows
			KEY_LBRACKET = DIK_LBRACKET, // ���p�J�b�R {
			KEY_RBRACKET = DIK_RBRACKET, // �E�p�J�b�R }
			KEY_PERIOD = DIK_PERIOD, // �s���I�h(���C���E�L�[�{�[�h)
			KEY_APOSTROPHE = DIK_APOSTROPHE, // �A�|�X�g���t�B
			KEY_APPS = DIK_APPS, // �A�v���P�[�V����
			KEY_BACKSLASH = DIK_BACKSLASH, // �o�b�N�E�X���b�V��
			KEY_SLASH = DIK_SLASH, // �X���b�V��(���C���E�L�[�{�[�h)
			KEY_COMMA = DIK_COMMA, // �R���}
			KEY_SEMICOLON = DIK_SEMICOLON, // �Z�~�R����
			KEY_GRAVE = DIK_GRAVE, // �A�N�T���E�O���[��(`)
			KEY_NUMLOCK = DIK_NUMLOCK, // NumLock
			KEY_NUMPAD0 = DIK_NUMPAD0, // �e���L�[�� 0�`9
			KEY_NUMPAD1 = DIK_NUMPAD1, // �e���L�[�� 0�`9
			KEY_NUMPAD2 = DIK_NUMPAD2, // �e���L�[�� 0�`9
			KEY_NUMPAD3 = DIK_NUMPAD3, // �e���L�[�� 0�`9
			KEY_NUMPAD4 = DIK_NUMPAD4, // �e���L�[�� 0�`9
			KEY_NUMPAD5 = DIK_NUMPAD5, // �e���L�[�� 0�`9
			KEY_NUMPAD6 = DIK_NUMPAD6, // �e���L�[�� 0�`9
			KEY_NUMPAD7 = DIK_NUMPAD7, // �e���L�[�� 0�`9
			KEY_NUMPAD8 = DIK_NUMPAD8, // �e���L�[�� 0�`9
			KEY_NUMPAD9 = DIK_NUMPAD9, // �e���L�[�� 0�`9
			KEY_ADD = DIK_ADD, // �e���L�[��[+]
			KEY_SUBTRACT = DIK_SUBTRACT, // �e���L�[��[-]
			KEY_DECIMAL = DIK_DECIMAL, // �e���L�[��[.]
			KEY_DIVIDE = DIK_DIVIDE, // �e���L�[��[/]
			KEY_MULTIPLY = DIK_MULTIPLY, // �e���L�[��[*]
			KEY_DNUMPADENTER = DIK_NUMPADENTER, // �e���L�[��Enter
			KEY_F13 = DIK_F13, // NEC PC98 F13�`F15
			KEY_F14 = DIK_F14, // NEC PC98 F13�`F15
			KEY_F15 = DIK_F15, // NEC PC98 F13�`F15
			KEY_YEN = DIK_YEN, // ���{��L�[�{�[�h�́�
			KEY_NOCONVERT = DIK_NOCONVERT, // ���{��L�[�{�[�h�̃L�[
			KEY_UNLABELED = DIK_UNLABELED, // ���{��L�[�{�[�h�̃L�[
			KEY_KANA = DIK_KANA, // ���{��L�[�{�[�h�̃L�[
			KEY_KANJI = DIK_KANJI, // ���{��L�[�{�[�h�̃L�[
			KEY_AT = DIK_AT, // ���{��L�[�{�[�h�̃L�[
			KEY_AX = DIK_AX, // ���{��L�[�{�[�h�̃L�[
			KEY_COLON = DIK_COLON, // ���{��L�[�{�[�h�̃L�[
			KEY_CONVERT = DIK_CONVERT; // ���{��L�[�{�[�h�̃L�[
	public:
		static constexpr int size() { return __MaxKey; }
	};

	//==========================================================================
	//
	// class : DirectInputKeyboard
	// Content : �L�[�{�[�h
	//
	//==========================================================================
	class Keyboard :
		public direct_input::DirectInput
	{
	private:
		Keyboard(const Keyboard&) = delete;
		Keyboard(Keyboard&&) = delete;
		Keyboard& operator=(const Keyboard&) = delete;
		Keyboard& operator=(Keyboard&&) = delete;
	public:
		Keyboard();
		~Keyboard();

		/**
		@brief ������
		@param _hInstance [in] �C���X�^���X�n���h��
		@param _hWnd [in] �E�B���h�E�n���h��
		@return ���s���� true ���Ԃ�܂�
		*/
		bool Init(HINSTANCE _hInstance, HWND _hWnd);

		/**
		@brief �X�V
		*/
		void Update()override;

		/**
		@brief �v���X
		@param _id [in] ���̓L�[
		@return ������Ă���ꍇ true ���Ԃ�܂�
		*/
		bool Press(int _id) override;

		/**
		@brief �g���K�[
		@param _id [in] ���̓L�[
		@return ������Ă���ꍇ true ���Ԃ�܂�
		*/
		bool Trigger(int _id) override;

		/**
		@brief ���s�[�g
		@param _id [in] ���̓L�[
		@return ������Ă���ꍇ true ���Ԃ�܂�
		*/
		bool Repeat(int _id) override;

		/**
		@brief �����[�X
		@param _id [in] ���̓L�[
		@return ������Ă���ꍇ true ���Ԃ�܂�
		*/
		bool Release(int _id) override;
	private:
		BYTE m_state[Button::size()] = { 0 }; // �L�[�{�[�h�̓��͏�񃏁[�N
		BYTE m_state_trigger[Button::size()] = { 0 }; // �L�[�{�[�h�̃g���K�[��񃏁[�N
		BYTE m_state_release[Button::size()] = { 0 }; // �L�[�{�[�h�̃����[�X��񃏁[�N
		BYTE m_state_repeat[Button::size()] = { 0 }; // �L�[�{�[�h�̃��s�[�g��񃏁[�N
		int m_state_repeat_cnt[Button::size()] = { 0 }; // �L�[�{�[�h�̃��s�[�g�J�E���^
	};

	using KeyboardReference = reference::IReference<Keyboard>;
}

_MSLIB_END