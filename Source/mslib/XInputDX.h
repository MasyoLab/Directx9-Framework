//==========================================================================
// X�C���v�b�g [XInputDX.h]
// author : MasyoLab
//==========================================================================
#pragma once

#pragma comment (lib, "xinput.lib") // ���C�u�����̃C���|�[�g
#include <Windows.h>
#include <XInput.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"
#include "Component.h"
#include "Reference.h"

_MSLIB_BEGIN

namespace xinput
{
	using XinputState = reference::WrapperReference<XINPUT_STATE, XINPUT_STATE>;

	//==========================================================================
	//
	// class : Bool4
	// Content : Bool4
	//
	//==========================================================================
	class Bool4
	{
	public:
		Bool4();
		Bool4(bool _up, bool _down, bool _left, bool _right);
		~Bool4();
	public:
		bool m_up, m_down, m_left, m_right;
	};

	//==========================================================================
	//
	// class : AnalogTrigger
	// Content : �A�i���O�X�e�B�b�N�̃g���K�[
	//
	//==========================================================================
	class AnalogTrigger
	{
	public:
		AnalogTrigger();
		~AnalogTrigger();
	public:
		/**
		@brief �X�V
		*/
		void update();

		/**
		@brief �؂�ւ�
		@param input [in] ����L�[
		@param out [in/out] �Ώ�
		*/
		void ifset(bool _input, bool& _out);

		/**
		@brief ��r in1 < in2
		@param in1 [in] �Ώ�1
		@param in2 [in/out] �Ώ�2
		@return in2 ���傫���ꍇ true
		*/
		bool ifbool(float _in1, float _in2);
	public:
		Bool4 m_Ltrigger; // ���A�i���O�̃g���K�[
		Bool4 m_LtriggerOld; // ���A�i���O�̌Â��g���K�[
		Bool4 m_Rtrigger; // �E�A�i���O�̃g���K�[
		Bool4 m_RtriggerOld; // �E�A�i���O�̌Â��g���K�[
	};

	// �A�i���O�̃{�^��
	enum class AnalogButton
	{
		UP, // ��
		DOWN, // ��
		LEFT, // ��
		RIGHT, // �E
	};

	// xBox�̉�����{�^��
	enum class Button
	{
		DPAD_UP = XINPUT_GAMEPAD_DPAD_UP, // �\���{�^�� ��
		DPAD_DOWN = XINPUT_GAMEPAD_DPAD_DOWN, // �\���{�^�� ��
		DPAD_LEFT = XINPUT_GAMEPAD_DPAD_LEFT, // �\���{�^�� ��
		DPAD_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT, // �\���{�^�� �E
		START = XINPUT_GAMEPAD_START, // START�{�^��
		BACK = XINPUT_GAMEPAD_BACK, // BACK�{�^��
		LEFT_THUMB = XINPUT_GAMEPAD_LEFT_THUMB, // ���A�i���O�X�e�B�b�N�̃{�^��
		RIGHT_THUMB = XINPUT_GAMEPAD_RIGHT_THUMB, // �E�A�i���O�X�e�B�b�N�̃{�^��
		LEFT_LB = XINPUT_GAMEPAD_LEFT_SHOULDER, // LB�{�^��
		RIGHT_RB = XINPUT_GAMEPAD_RIGHT_SHOULDER, // RB�{�^��
		A = XINPUT_GAMEPAD_A, // A�{�^��
		B = XINPUT_GAMEPAD_B, // B�{�^��
		X = XINPUT_GAMEPAD_X, // X�{�^��
		Y = XINPUT_GAMEPAD_Y, // Y�{�^��
	};

	//==========================================================================
	//
	// class : XInput
	// Content : X�C���v�b�g
	//
	//==========================================================================
	class XInput :
		public component::Component
	{
	private:
		XInput(const XInput&) = delete;
		XInput(XInput&&) = delete;
		XInput& operator=(const XInput&) = delete;
		XInput& operator=(XInput&&) = delete;
	public:
		XInput();
		virtual ~XInput();

		/**
		@brief ������
		@param num [in] ���R���g���[���[�̐�
		@return ���s�� true
		*/
		bool Init(int _num);

		/**
		@brief ���
		*/
		void Release();

		/**
		@brief �X�V
		*/
		void Update();

		/**
		@brief �v���X
		@param button [in] �{�^��ID
		@param index [in] �����R���g���[���[
		@return �����Ă���Ƃ� true
		*/
		bool Press(Button _button, int _index);

		/**
		@brief �g���K�[
		@param button [in] �{�^��ID
		@param index [in] �����R���g���[���[
		@return �����Ă���Ƃ� true
		*/
		bool Trigger(Button _button, int _index);

		/**
		@brief �����[�X
		@param button [in] �{�^��ID
		@param index [in] �����R���g���[���[
		@return �����Ă���Ƃ� true
		*/
		bool Release(Button _button, int _index);

		/**
		@brief ���A�i���O�X�e�B�b�N
		@param index [in] �����R���g���[���[
		@param Out [in] �X���x�N�g��
		@return �����Ă���Ƃ� true
		*/
		bool AnalogL(int _index, D3DXVECTOR3& _out);

		/**
		@brief ���A�i���O�X�e�B�b�N
		@param index [in] �����R���g���[���[
		@return �����Ă���Ƃ� true
		*/
		bool AnalogL(int _index);

		/**
		@brief �E�A�i���O�X�e�B�b�N
		@param index [in] �����R���g���[���[
		@param Out [in] �X���x�N�g��
		@return �����Ă���Ƃ� true
		*/
		bool AnalogR(int index, D3DXVECTOR3& Out);

		/**
		@brief �E�A�i���O�X�e�B�b�N
		@param index [in] �����R���g���[���[
		@return �����Ă���Ƃ� true
		*/
		bool AnalogR(int _index);

		/**
		@brief ���A�i���O�X�e�B�b�N�̃g���K�[
		@param button [in] �{�^��ID
		@param index [in] �����R���g���[���[
		@return �����Ă���Ƃ� true
		*/
		bool AnalogLTrigger(AnalogButton _button, int _index);

		/**
		@brief ���A�i���O�X�e�B�b�N�̃g���K�[
		@param index [in] �����R���g���[���[
		@param button [in] �{�^��ID
		@param out [in/out] �X���x�N�g��
		@return �����Ă���Ƃ� true
		*/
		bool AnalogLTrigger(AnalogButton _button, int _index, D3DXVECTOR3& _out);

		/**
		@brief �E�A�i���O�X�e�B�b�N�̃g���K�[
		@param index [in] �����R���g���[���[
		@param key [in] �{�^��ID
		@return �����Ă���Ƃ� true
		*/
		bool AnalogRTrigger(AnalogButton _button, int _index);

		/**
		@brief �E�A�i���O�X�e�B�b�N�̃g���K�[
		@param index [in] �����R���g���[���[
		@param key [in] �{�^��ID
		@param Out [in] �X���x�N�g��
		@return �����Ă���Ƃ� true
		*/
		bool AnalogRTrigger(AnalogButton _button, int _index, D3DXVECTOR3& _out);

		/**
		@brief ���g���K�[�{�^��
		@param index [in] �����R���g���[���[
		@return �����Ă���Ƃ� true
		*/
		bool LT(int _index);

		/**
		@brief �E�g���K�[�{�^��
		@param index [in] �����R���g���[���[
		@return �����Ă���Ƃ� true
		*/
		bool RT(int _index);

		/**
		@brief �R���g���[���[�̑��݂̊m�F
		@param index [in] �����R���g���[���[
		@return ���݂���ꍇ true
		*/
		bool Check(int _index);

		/**
		@brief �R���g���[���[�̌��݂̏�Ԃ��擾
		@param index [in] �����R���g���[���[
		@return �C���X�^���X
		*/
		XinputState GetState(int _index);

		/**
		@brief �T�C�Y
		@return �R���g���[���[��
		*/
		int Size();
	private:
		/**
		@brief �R���g���[���̃L�[�g���K�[
		@param new [in] �V��������L�[
		@param old [in] �Â�����L�[
		@return ����
		*/
		bool KeyTrigger(bool _new, bool _old);

		/**
		@brief �R���g���[���̃L�[�����[�X
		@param new [in] �V��������L�[
		@param old [in] �Â�����L�[
		@return ����
		*/
		bool KeyRelease(bool _new, bool _old);
	private:
		XINPUT_STATE* m_state; // �R���g���[���[�̃X�e�[�^�X
		XINPUT_STATE* m_stateOld; // �Â����
		AnalogTrigger* m_trigger; // �A�i���O�̃g���K�[
		bool* m_statedat; //�p�b�h�̗L��
		int m_numdata; // �o�^���ꂽ�f�[�^��
	};

	using XInputReference = reference::IReference<XInput>;
}

_MSLIB_END