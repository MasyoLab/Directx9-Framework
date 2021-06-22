//==========================================================================
// �_�C���N�g�C���v�b�g�̃}�E�X [DinputMouse.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "DirectInput.h"

_MSLIB_BEGIN

namespace dinput_mouse
{
    class Speed
    {
    public:
		Speed();
		Speed(const DIMOUSESTATE2 & dim);
		~Speed();
    public:
		LONG x, y, z; // X�����x
    };

    // �L���{�^��
	class Button
	{
		enum Key
		{
			ELeft = 0,	// ���N���b�N
			ERight,	// �E�N���b�N
			EWheel,	// �z�C�[��
			MAX,
		};
	public:
		static constexpr int
			Left = Key::ELeft,		// ���N���b�N
			Right = Key::ERight,	// �E�N���b�N
			Wheel = Key::EWheel;	// �z�C�[��
	public:
		static constexpr int size() { return Key::MAX; }
	};

    //==========================================================================
    //
    // class : Mouse
    // Content : �}�E�X
    //
    //==========================================================================
    class Mouse :
		public direct_input::DirectInput
    {
	private:
		Mouse(const Mouse&) = delete;
		Mouse(Mouse&&) = delete;
		Mouse& operator=(const Mouse&) = delete;
		Mouse& operator=(Mouse&&) = delete;
	public:
        Mouse();
        ~Mouse();

        /**
        @brief ������
        @param _hInstance [in] �C���X�^���X�n���h��
        @param _hwnd [in] �E�B���h�E�n���h��
        @return ���s�� true ���Ԃ�܂�
        */
        bool Init(HINSTANCE _hInstance, HWND _hwnd);

        /**
        @brief �X�V
        */
        void Update()override;

        /**
        @brief �v���X
        @param _id [in] ���̓L�[
        @return ���͂���Ă���ꍇ true ���Ԃ�܂�
        */
        bool Press(int _id) override;

        /**
        @brief �g���K�[
        @param _id [in] ���̓L�[
        @return ���͂���Ă���ꍇ true ���Ԃ�܂�
        */
        bool Trigger(int _id) override;

        /**
        @brief ���s�[�g
        @param _id [in] ���̓L�[
        @return ���͂���Ă���ꍇ true ���Ԃ�܂�
        */
        bool Repeat(int _id) override;

        /**
        @brief �����[�X
        @param _id [in] ���̓L�[
        @return ���͂���Ă���ꍇ true ���Ԃ�܂�
        */
        bool Release(int _id) override;

        /**
        @brief �}�E�X�̑��x
        @return �}�E�X�̈ړ����x���Ԃ�܂�
        */
        Speed GetSpeed();

        /**
        @brief �J�[�\���̍��W
        @return ��ʓ����W���Ԃ�܂�
        */
        POINT Win32Cursor();

        /**
        @brief ���N���b�N
        @return ���͂���Ă���ꍇ�l���Ԃ�܂�
        */
        SHORT Win32LeftClick();

        /**
        @brief �E�N���b�N
        @return ���͂���Ă���ꍇ�l���Ԃ�܂�
        */
        SHORT Win32RightClick();

        /**
        @brief �}�E�X�z�C�[���̃z�[���h����
        @return ���͂���Ă���ꍇ�l���Ԃ�܂�
        */
        SHORT Win32WheelHold();
    private:
        static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *_didoi, void *_context);
    private: // DirectInput
        DIMOUSESTATE2 m_state; // ���͏�񃏁[�N
        BYTE m_state_trigger[(int)sizeof(DIMOUSESTATE2::rgbButtons)];	// �g���K�[��񃏁[�N
        BYTE m_state_release[(int)sizeof(DIMOUSESTATE2::rgbButtons)]; // �����[�X��񃏁[�N
        BYTE m_state_repeat[(int)sizeof(DIMOUSESTATE2::rgbButtons)]; // ���s�[�g��񃏁[�N
        int m_state_repeat_cnt[(int)sizeof(DIMOUSESTATE2::rgbButtons)]; // ���s�[�g�J�E���^
    private: // WindowsAPI
        POINT m_mouse_pos;
        HWND m_hwnd;
    };

	using MouseReference = reference::IReference<Mouse>;
}
_MSLIB_END