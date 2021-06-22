//==========================================================================
// �R���g���[���[ [DinputController.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "DirectInput.h"

_MSLIB_BEGIN

namespace dinput_controller
{
	// �����L�[
	class CrossKey
	{
		// �����L�[
		enum Key
		{
			EUp,
			EUpRight,
			ERight,
			EUnderRight,
			EUnder,
			EUnderLeft,
			ELeft,
			EUpLeft,
			MAX
		};
	public:
		static constexpr int
			Up = Key::EUp,
			UpRight = Key::EUpRight,
			Right = Key::ERight,
			UnderRight = Key::EUnderRight,
			Under = Key::EUnder,
			UnderLeft = Key::EUnderLeft,
			Left = Key::ELeft,
			UpLeft = Key::EUpLeft;
	public:
		static constexpr int size() { return Key::MAX; }
	};

	// PS4 �{�^��
	class PS4Button
	{
		enum Key
		{
			ESquare,	// ��
			EXButton,	// �w
			ERound,		// �Z
			ETriangle,	// ��
			EL1,		// L1
			ER1,		// R1
			EL2,		// L2
			ER2,		// R2
			ESHARE,		// SHARE
			ESOPTIONS,	// OPTIONS
			EL3,		// L3
			ER3,		// R3
			EPS,		// PS
			ETouchPad,	// TouchPad
			MAX
		};
	public:
		static constexpr int
			Square = Key::ESquare,
			XButton = Key::EXButton,
			Round = Key::ERound,
			Triangle = Key::ETriangle,
			L1 = Key::EL1,
			R1 = Key::ER1,
			L2 = Key::EL2,
			R2 = Key::ER2,
			SHARE = Key::ESHARE,
			SOPTIONS = Key::ESOPTIONS,
			L3 = Key::EL3,
			R3 = Key::ER3,
			PS = Key::EPS,
			TouchPad = Key::ETouchPad;
	public:
		static constexpr int size() { return Key::MAX; }
	};

	//==========================================================================
	//
	// class : CPS4
	// Content : PS4�R���g���[���[
	//
	//==========================================================================
	class Stick
	{
	public:
		Stick();
		Stick(const Stick& obj);
		~Stick();
		Stick& operator =(const Stick& obj);
	public:
		LONG m_left_right;
		LONG m_up_under;
	};

	//==========================================================================
	//
	// class : Controller
	// Content : �R���g���[���[
	//
	//==========================================================================
	class Controller :
		public direct_input::DirectInput
	{
	private:
		Controller(const Controller&) = delete;
		Controller(Controller&&) = delete;
		Controller& operator=(const Controller&) = delete;
		Controller& operator=(Controller&&) = delete;
	public:
		Controller();
		~Controller();

		/**
		@brief ������
		@param hInstance [in] �C���X�^���X�n���h��
		@param hWnd [in] �E�B���h�E�n���h��
		@return ���s���� true ���Ԃ�܂�
		*/
		bool Init(HINSTANCE _hInstance, HWND _hWnd);

		/**
		@brief �X�V
		*/
		void Update()override;

		/**
		@brief ���X�e�B�b�N�̏�Ԏ擾
		@return �X�e�b�N�̏��
		*/
		Stick LeftStick();

		/**
		@brief �E�X�e�B�b�N�̏�Ԏ擾
		@return �X�e�b�N�̏��
		*/
		Stick RightStick();

		/**
		@brief L2�{�^���̏�Ԏ擾
		@return L2�{�^���̏��
		*/
		LONG L2();

		/**
		@brief R2�{�^���̏�Ԏ擾
		@return R2�{�^���̏��
		*/
		LONG R2();

		/**
		@brief PS4 �����L�[
		@param _id [in] �g�p�L�[�̎w��
		@return ���͂���Ă���ꍇ true ���Ԃ�܂�
		*/
		bool CrossButton(int _id);

		/**
		@brief PS4 �����L�[ �v���X
		@param _id [in] �g�p�L�[�̎w��
		@return ���͂���Ă���ꍇ true ���Ԃ�܂�
		*/
		bool CrossButtonPress(int _id);

		/**
		@brief PS4 �����L�[ �g���K�[
		@param _id [in] �g�p�L�[�̎w��
		@return ���͂���Ă���ꍇ true ���Ԃ�܂�
		*/
		bool CrossButtonTrigger(int _id);

		/**
		@brief PS4 �����L�[ ���s�[�g
		@param _id [in] �g�p�L�[�̎w��
		@return ���͂���Ă���ꍇ true ���Ԃ�܂�
		*/
		bool CrossButtonRepeat(int _id);

		/**
		@brief PS4 �����L�[ �����|�X
		@param _id [in] �g�p�L�[�̎w��
		@return ���͂���Ă���ꍇ true ���Ԃ�܂�
		*/
		bool CrossButtonRelease(int _id);

		/**
		@brief PS4 �{�^�� �v���X
		@param _id [in] �g�p�L�[�̎w��
		@return ���͂���Ă���ꍇ true ���Ԃ�܂�
		*/
		bool Press(int _id) override;

		/**
		@brief PS4 �{�^�� �g���K�[
		@param _id [in] �g�p�L�[�̎w��
		@return ���͂���Ă���ꍇ true ���Ԃ�܂�
		*/
		bool Trigger(int _id) override;

		/**
		@brief PS4 �{�^�� ���s�[�g
		@param _id [in] �g�p�L�[�̎w��
		@return ���͂���Ă���ꍇ true ���Ԃ�܂�
		*/
		bool Repeat(int _id) override;

		/**
		@brief PS4 �{�^�� �����|�X
		@param _id [in] �g�p�L�[�̎w��
		@return ���͂���Ă���ꍇ true ���Ԃ�܂�
		*/
		bool Release(int _id) override;
	private:
		/**
		@brief PS4 ���͌덷�C��
		@param _set [in] ����
		@return �l���Ԃ�܂�
		*/
		LONG Adjustment(LONG _set);

		/**
		@brief PS4 �X�e�b�N���͐���
		@param _stick1 [in] ����
		@param _stick2 [in] ����
		@return �l���Ԃ�܂�
		*/
		Stick StickFunction(LONG _stick1, LONG _stick2);
	private:
		static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* _didInstance, void* _context);
		static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE* _didoi, void* _context);
	private:
		DIJOYSTATE m_state; // ���͏�񃏁[�N
		BYTE m_state_trigger[(int)sizeof(DIJOYSTATE::rgbButtons)]; // �g���K�[��񃏁[�N
		BYTE m_state_release[(int)sizeof(DIJOYSTATE::rgbButtons)]; // �����[�X��񃏁[�N
		BYTE m_state_repeat[(int)sizeof(DIJOYSTATE::rgbButtons)]; // ���s�[�g��񃏁[�N
		int m_state_repeat_cnt[(int)sizeof(DIJOYSTATE::rgbButtons)]; // ���s�[�g�J�E���^

		BYTE m_pov_state[CrossKey::size()]; // POV���͏�񃏁[�N
		BYTE m_pov_trigger[CrossKey::size()]; // �g���K�[��񃏁[�N
		BYTE m_pov_release[CrossKey::size()]; // �����[�X��񃏁[�N
		BYTE m_pov_repeat[CrossKey::size()]; // ���s�[�g��񃏁[�N
		int m_pov_repeat_cnt[CrossKey::size()]; // ���s�[�g�J�E���^
	};

	using ControllerReference = reference::IReference<Controller>;
}

_MSLIB_END