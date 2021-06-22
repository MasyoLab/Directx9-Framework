//==========================================================================
// MsImGui [MsImGui.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <Windows.h>
#include <memory>
#include <string>
#include <cstdio>
#include "ImGui\imgui.h"
#include "ImGui\imgui_impl_dx9.h"
#include "ImGui\imgui_impl_win32.h"
#include <d3d9.h>
#include <d3dx9.h>
#define DIRECTINPUT_VERSION (0x0800) // DirectInput�̃o�[�W�����w��
#include <dinput.h>
#include <tchar.h>

#include "mslib.hpp"

_MSLIB_BEGIN

namespace imgui
{
	/**
	@brief ������
	@param hWnd [in] �E�B���h�E�n���h��
	@param pDevice [in] �f�o�C�X
	@return ���s���� true ���Ԃ�܂�
	*/
	bool Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice);

	/**
	@brief ���
	*/
	void Uninit(void);

	/**
	@brief �X�V
	*/
	void WindowInfo(void);

	/**
	@brief �`��
	*/
	void Draw(LPDIRECT3DDEVICE9 pDevice);

	/**
	@brief �`�� (Handle loss of D3D9 device)
	@param result [in] Component Object Model defines, and macros
	@param pDevice [in] �f�o�C�X
	@param pd3dpp [in] �f�o�C�X
	*/
	void DeviceReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pd3dpp);

	/**
	@brief WndProc (Process Win32 mouse/keyboard inputs)
	@param hWnd [in] �E�B���h�E�n���h��
	@param uMsg [in] ���b�Z�[�W
	@param wParam [in] �_�u���p����
	@param lParam [in] �G���p����
	@return Types use for passing & returning polymorphic values
	*/
	LRESULT ImGui_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	/**
	@brief ���b�Z�[�W
	@param hWnd [in] �E�B���h�E�n���h��
	@param uMsg [in] ���b�Z�[�W
	@param wParam [in] �_�u���p����
	@param lParam [in] �G���p����
	@param pDevice [in] �f�o�C�X
	@param pd3dpp [in] �f�o�C�X
	@return Types use for passing & returning polymorphic values
	*/
	LRESULT SetMenu(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pd3dpp);

	/**
	@brief �V�����E�B���h�E�J�n
	@param label [in] �E�B���h�E��
	@param p_open [in] false�ŊJ���Ȃ�/true�ŊJ����
	@param flags [in] ImGuiWindowFlags_::??
	*/
	void NewWindow(const std::string& label, bool p_open, ImGuiWindowFlags flags = 0);

	/**
	@brief �V�����E�B���h�E�J�n
	@param label [in] �E�B���h�E��
	@param p_open [in] false�ŊJ���Ȃ�/true�ŊJ����
	@param size_on_first_use [in] �T�C�Y�w��
	@param bg_alpha_override [in]
	@param flags [in] ImGuiWindowFlags_::??
	*/
	void NewWindow(const std::string& label, bool p_open, const ImVec2& size_on_first_use, ImGuiWindowFlags flags, float bg_alpha_override = -1.0f);

	/**
	@brief �V�����E�B���h�E�J�n
	@param label [in] �E�B���h�E��
	@param p_open [in] false�ŊJ���Ȃ�/true�ŊJ����
	@param size_on_first_use [in] �T�C�Y�w��
	@param bg_alpha_override [in]
	*/
	void FixedWindow(const std::string& label, bool p_open, const ImVec2& size_on_first_use, float bg_alpha_override = -1.0f);

	/**
	@brief �E�B���h�E�I��
	*/
	void EndWindow(void);

	/**
	@brief ���̃E�B���h�E�̕\���ʒu��ݒ�
	@param pos [in] ���W
	@param cond [in]
	@param pivot [in]
	*/
	void SetNextWindowPos(const ImVec2& pos, ImGuiCond cond = 0, const ImVec2 & pivot = ImVec2(0, 0));

	/**
	@brief �X�N���[���o�[ int�l����
	@param label [in] �X�N���[���o�[��
	@param v [in/out] ����Ώ�
	@param v_min [in] ����͈͂̍ŏ�
	@param v_max [in] ����͈͂̍ő�
	@param display_format [in] �\���`��
	@return �������� true ���Ԃ�܂�
	*/
	bool SliderInt(const std::string& label, int* v, int v_min, int v_max, const char* display_format = "%f");

	/**
	@brief �X�N���[���o�[ float�l����
	@param label [in] �X�N���[���o�[��
	@param v [in/out] ����Ώ�
	@param v_min [in] ����͈͂̍ŏ�
	@param v_max [in] ����͈͂̍ő�
	@param power [in] ����{��
	@param display_format [in] �\���`��
	@return �������� true ���Ԃ�܂�
	*/
	bool SliderFloat(const std::string& label, float* v, float v_min, float v_max, float power = (1.0f), const char* display_format = "%f");

	/**
	@brief �{�^��
	@param label [in] �{�^����
	@param size [in] �{�^���T�C�Y
	@return �������� true ���Ԃ�܂�
	*/
	bool Button(const std::string& label, const ImVec2& size = ImVec2(0, 0));

	/**
	@brief ���������܂�
	*/
	void Separator(void);

	/**
	@brief �K�w�\���J�n
	@param label [in] �\����
	@param is_open [in] false �f�t�H���g�ŕ��Ă��܂�/true �f�t�H���g�ŊJ���Ă��܂�
	@param args [in] �\���������f�[�^
	@return �������� true ���Ԃ�܂�
	*/
	bool NewTreeNode(const std::string& label, bool is_open);

	/**
	@brief �K�w�\���I���
	*/
	void EndTreeNode(void);

	/**
	@brief �e�L�X�g�\��
	@param label [in] �\�����e
	*/
	void Text(const std::string& label);

	/**
	@brief ���̓{�b�N�X
	@param label [in] �f�t�H���g�̓��e
	@return ���͓��e
	*/
	bool InputText(const std::string& label, std::string& Out, ImGuiInputTextFlags flags = 0, ImGuiTextEditCallback callback = nullptr, void* user_data = nullptr);

	/**
	@brief �\���t���[���J�n
	*/
	void NewFrame(void);

	/**
	@brief NewFrame ���Ă΂ꂽ���ǂ����`�F�b�N���܂�
	*/
	bool NewFrameCheckCall();

	/**
	@brief �\���t���[���J�n�I���
	*/
	void EndFrame(void);

	/**
	@brief �`�F�b�N�{�b�N�X
	@param label [in] �`�F�b�N�{�b�N�X��
	@param v [in/out] ����Ώ�
	@return �������� true ���Ԃ�܂�
	*/
	bool Checkbox(const std::string& label, bool& v);

	/**
	@brief �f�R�C
	@param label [in] �f�R�C��
	*/
	void decoy(const std::string& label, ...);

	/**
	@brief ���j���[�o�[�̊J�n
	@return �������� true ���Ԃ�܂�
	*/
	bool NewMenuBar(void);

	/**
	@brief ���j���[�o�[�̏I��
	*/
	void EndMenuBar(void);

	/**
	@brief ���j���[���A�C�e���̓o�^
	@param label [in] �A�C�e����
	@param shortcut [in]
	@param selected [in]
	@param enabled [in]
	@return �������� true ���Ԃ�܂�
	*/
	bool MenuItem(const std::string& label, const char* shortcut = nullptr, bool selected = false, bool enabled = true);

	/**
	@brief ���j���[�J�n
	@param label [in] ���j���[��
	@param enabled [in] false�Ń��j���[����/true�ŗL��
	@return �������� true ���Ԃ�܂�
	*/
	bool NewMenu(const std::string& label, bool enabled = true);

	/**
	@brief ���j���[�I���
	*/
	void EndMenu(void);

	/**
	@brief �J���[�G�f�B�^
	@param _color [in] ����Ώ�
	@return ���삵���F���Ԃ�܂�
	*/
	D3DXCOLOR ColorEdit(const D3DXCOLOR& _color);

	/**
	@brief �e�N�X�`���`��
	@param user_texture_id [in] �e�N�X�`���|�C���^
	@param size [in] �e�N�X�`���T�C�Y
	@param master_size [in] ��ƂȂ�`��T�C�Y(w,h����)
	*/
	void Image(LPDIRECT3DTEXTURE9 user_texture_id, const ImVec2& size, const ImVec4& tint_col, const ImVec4& border_col, float master_size = 100.0f);

	//==========================================================================
	//
	//
	// ImGui Wrapper
	//
	//
	//==========================================================================

	// �R���e�L�X�g�̍쐬�ƃA�N�Z�X�A�����̃R���e�L�X�g���g�p����ꍇ�́A���W���[���ԂŃR���e�L�X�g�����L���܂��iDLL�Ȃǁj�B
	// �f�t�H���g�ł́A���ׂẴR���e�L�X�g������ImFontAtlas�����L���܂��B �ʂ̃t�H���g�A�g���X���K�v�ȏꍇ�́A������new()����GetIO()�BImgui�R���e�L�X�g��Fonts�ϐ����㏑�����邱�Ƃ��ł��܂��B
	// �����̊֐��͂��ׂČ��݂̃R���e�L�X�g�Ɉˑ����܂���B 
	ImGuiContext* _CreateContext(ImFontAtlas* shared_font_atlas = nullptr);
	void          _DestroyContext(ImGuiContext* ctx = nullptr);   // nullptr = Destroy current context
	ImGuiContext* _GetCurrentContext();
	void          _SetCurrentContext(ImGuiContext* ctx);

	//==========================================================================
	//
	// ���C��
	//
	//==========================================================================

	ImGuiIO& _GetIO();
	ImGuiStyle& _GetStyle();
	ImDrawData* _GetDrawData();                           // io.RenderDrawListsFn()�֐��ɓn�����l�Ɠ����ł��B Render()�̌��NewFrame()�ւ̎��̌Ăяo���܂ŗL���ł��B
	void          _NewFrame();                              // �V����ImGui�t���[�����J�n����Ƃ��́ARender()/EndFrame()�܂ł��̃R�}���h�����s���邱�Ƃ��ł��܂��B
	void          _Render();                                // ImGui�t���[�����I�����A�`��f�[�^���m�肵�Ă���A�ݒ肳��Ă���ꍇ��io.RenderDrawListsFn()�֐����Ăяo���܂��B
	void          _EndFrame();                              // ����ImGui�t���[�������������܂��B Render()�ɂ���Ď����I�ɌĂяo����邽�߁A���ڌĂяo���K�v�͂���܂���B �����_�����O�����s����K�v���Ȃ��ꍇ�AEndFrame()�͌Ăяo�����Ƃ��ł��܂����ACPU�𖳑ʂɂ��܂��B �����_�����O����K�v���Ȃ��ꍇ�́Aimgui�E�B���h�E���쐬���Ȃ��ł��������B

	//==========================================================================
	//
	// �f���A�f�o�b�O�A���
	//
	//==========================================================================

	void          _ShowDemoWindow(bool* p_open = nullptr);        // �f��/�e�X�g�E�B���h�E�i�ȑO��ShowTestWindow�ƌĂ΂�Ă��܂����j���쐬���܂��B �قƂ�ǂ�ImGui�̋@�\�������Ă��܂��B ���C�u�����ɂ��Ċw�Ԃ��߂ɂ�����Ă�ł��������I ���Ȃ��̃A�v���P�[�V�����ł��ł����p�ł���悤�ɂ��Ă��������I
	void          _ShowMetricsWindow(bool* p_open = nullptr);     // ���g���b�N�E�B���h�E���쐬���܂��B ImGui�̓�����\������F�`��R�}���h�i�X�̕`��Ăяo���ƒ��_�t���j�A�E�B���h�E���X�g�A��{�I�ȓ�����ԂȂ�
	void          _ShowStyleEditor(ImGuiStyle* ref = nullptr);    // �X�^�C���G�f�B�^�u���b�N��ǉ����܂��i�E�B���h�E�ł͂���܂���j�B ��r����ImGuiStyle�\���̂�n���Č��ɖ߂��ĕۑ����邱�Ƃ��ł��܂��i����ȊO�̏ꍇ�̓f�t�H���g�X�^�C�����g�p���܂��j
	bool          _ShowStyleSelector(const char* label);
	void          _ShowFontSelector(const char* label);
	void          _ShowUserGuide();                            // ��{�I�ȃw���v/���u���b�N�i�E�B���h�E�ł͂Ȃ��j��ǉ�����FImGui���G���h���[�U�i�}�E�X/�L�[�{�[�h�R���g���[���j�Ƃ��đ��삷����@�B
	const char* _GetVersion();

	//==========================================================================
	//
	// Window
	//
	//==========================================================================

	bool          _Begin(const char* name, bool* p_open = nullptr, ImGuiWindowFlags flags = 0);   // �E�B���h�E���X�^�b�N�Ƀv�b�V�����Ēǉ����J�n���܂��B �ڍׂ�.cpp���Q�Ƃ��Ă��������B �E�B���h�E���܂肽���܂�Ă���Ƃ���false��Ԃ��̂Łi�R�[�h���ő��߂ɍs�����Ƃ��ł��܂��j�AEnd()����ɌĂяo���K�v������܂��B 'bool * p_open'�͉E��ɃE�B�W�F�b�g���쐬���ăE�B���h�E����܂��ibool��false�ɐݒ肵�܂��j�B
	void          _End();                                                              // Begin()��false��Ԃ��ꍇ�ł���ɌĂяo����܂��i�܂肽���܂ꂽ�E�B���h�E�������܂��j�I ���݂̃E�B���h�E�ɒǉ����I�����A�E�B���h�E�X�^�b�N����|�b�v���܂��B
	bool          _BeginChild(const char* str_id, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags flags = 0);  // �X�N���[���̈���J�n���܂��B size == 0.0f�F�c��̃E�B���h�E�T�C�Y�A�T�C�Y<0.0f�F�c��̃E�B���h�E�T�C�Y����abs�i�T�C�Y�j���������l���g�p���܂��B �T�C�Y> 0.0f�F�Œ�T�C�Y�B �e���͈قȂ郂�[�h���g�p���邱�Ƃ��ł���B ImVec2�i0,400�j�B
	bool          _BeginChild(ImGuiID id, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags flags = 0);          // "
	void          _EndChild();                                                         // BeginChild()��false��Ԃ��ꍇ�ł���ɌĂяo����܂��i�q�E�B���h�E���܂肽���܂�Ă��邩�N���b�s���O����Ă��邱�Ƃ������܂��j
	ImVec2        _GetContentRegionMax();                                              // ���݂̃R���e���c���E�i�ʏ�A�X�N���[�����܂ރE�B���h�E���E�A�܂��͌��݂̗񋫊E�j�A�E�B���h�E���W
	ImVec2        _GetContentRegionAvail();                                            // == GetContentRegionMax() - GetCursorPos()
	float         _GetContentRegionAvailWidth();                                       //
	ImVec2        _GetWindowContentRegionMin();                                        // content boundaries min (roughly (0,0)-Scroll), �E�B���h�E���W
	ImVec2        _GetWindowContentRegionMax();                                        // content boundaries max (roughly (0,0)+Size-Scroll) Size�́ASetNextWindowContentSize()���g�p���ăE�B���h�E���W�ŃI�[�o�[���C�h���邱�Ƃ��ł��܂�
	float         _GetWindowContentRegionWidth();                                      //
	ImDrawList* _GetWindowDrawList();                                                // �Ǝ��̕`��v���~�e�B�u��ǉ�����ꍇ�́A�`��R�}���h���X�g���擾����
	ImVec2        _GetWindowPos();                                                     // ��ʃX�y�[�X���̌��݂̃E�B���h�E�ʒu���擾���܂��iDrawList API���g�p���ēƎ��̕`����s�������ꍇ�ɕ֗��ł��j
	ImVec2        _GetWindowSize();                                                    // ���݂̃E�B���h�E�T�C�Y���擾����
	float         _GetWindowWidth();
	float         _GetWindowHeight();
	bool          _IsWindowCollapsed();
	bool          _IsWindowAppearing();
	void          _SetWindowFontScale(float scale);                                    // �E�B���h�E���Ƃ̃t�H���g�T�C�Y�B ���ׂẴE�B���h�E���g��/�k������ꍇ�́ATO.Font GlobalScale�𒲐����܂��B

	void          _SetNextWindowPos(const ImVec2& pos, ImGuiCond cond = 0, const ImVec2 & pivot = ImVec2(0, 0)); // ���̃E�B���h�E�ʒu��ݒ肵�܂��B Begin()�̑O�ɌĂяo���܂��B �s�{�b�g=�i0.5f�A0.5f�j���g�p���āA�^����ꂽ�_�𒆐S�ɂ��܂��B
	void          _SetNextWindowSize(const ImVec2& size, ImGuiCond cond = 0);          // ���̃E�B���h�E�T�C�Y��ݒ肵�܂��B ���̎��ɃI�[�g�t�B�b�g����������ɂ́A0.0f�Ɏ���ݒ肵�܂��B Begin()�̑O�ɌĂяo��
	void          _SetNextWindowSizeConstraints(const ImVec2& size_min, const ImVec2& size_max, ImGuiSizeCallback custom_callback = nullptr, void* custom_callback_data = nullptr); // ���̃E�B���h�E�T�C�Y������ݒ肵�܂��B X / Y���̂����ꂩ��-1�A-1���g�p���Č��݂̃T�C�Y���ێ����܂��B �R�[���o�b�N���g�p���āA�v���O������̐�����y���K�p���܂��B
	void          _SetNextWindowContentSize(const ImVec2& size);                       // ���̃E�B���h�E�̃R���e���c�T�C�Y��ݒ肷��i�X�N���[���o�[�͈̔͂���������j�B �E�B���h�E�����i�^�C�g���o�[�A���j���[�o�[�Ȃǁj�͊܂܂�܂���B 0.0f�Ɏ���ݒ肵�Ď����ɂ��܂��B Begin()�̑O�ɌĂяo��
	void          _SetNextWindowCollapsed(bool collapsed, ImGuiCond cond = 0);         // ���̃E�B���h�E�̐܂��ݏ�Ԃ�ݒ肵�܂��B Begin()�̑O�ɌĂяo��
	void          _SetNextWindowFocus();                                               // ���̃E�B���h�E���t�H�[�J�X/�őO�ʂɐݒ肵�܂��B Begin()�̑O�ɌĂяo��
	void          _SetNextWindowBgAlpha(float alpha);                                  // ���̃E�B���h�E�̔w�i�F�A���t�@��ݒ肵�܂��B ImGuiCol_WindowBg / ChildBg / PopupBg���ȒP�ɕύX����w���p�[�B
	void          _SetWindowPos(const char* name, const ImVec2& pos, ImGuiCond cond = 0);      // ���O�t���E�B���h�E�̈ʒu��ݒ肵�܂��B
	void          _SetWindowSize(const char* name, const ImVec2& size, ImGuiCond cond = 0);    // ���O�t���E�B���h�E�T�C�Y��ݒ肵�܂��B ���̎��ɃI�[�g�t�B�b�g����������ɂ́A0.0f�Ɏ���ݒ肵�܂��B
	void          _SetWindowCollapsed(const char* name, bool collapsed, ImGuiCond cond = 0);   // ���O�t���E�B���h�E�̐܂��ݏ�Ԃ�ݒ肷��
	void          _SetWindowFocus(const char* name);                                           // �w�肳�ꂽ�E�B���h�E���t�H�[�J�X/�őO�ʂɐݒ肵�܂��B �t�H�[�J�X���폜����ɂ�NULL���g�p���܂��B

	float         _GetScrollX();                                                       // �X�N���[���ʂ��擾���� [0..GetScrollMaxX()]
	float         _GetScrollY();                                                       // �X�N���[���ʂ��擾���� [0..GetScrollMaxY()]
	float         _GetScrollMaxX();                                                    // �ő�̃X�N���[���ʂ𓾂� ~~ ContentSize.X - WindowSize.X
	float         _GetScrollMaxY();                                                    // �ő�̃X�N���[���ʂ𓾂� ~~ ContentSize.Y - WindowSize.Y
	void          _SetScrollX(float scroll_x);                                         // �X�N���[���ʂ�ݒ肷�� [0..GetScrollMaxX()]
	void          _SetScrollY(float scroll_y);                                         // �X�N���[���ʂ�ݒ肷�� [0..GetScrollMaxY()]
	void          _SetScrollHere(float center_y_ratio = 0.5f);                         // �X�N���[���ʂ𒲐����āA���݂̃J�[�\���ʒu��\�������܂��B center_y_ratio = 0.0�Ftop�A0.5�Fcenter�A1.0�Fbottom�B �u�f�t�H���g/���݂̃A�C�e���v��\�����邽�߂Ɏg�p����ꍇ�́A�����SetItemDefaultFocus()���g�p���邱�Ƃ��������Ă��������B
	void          _SetScrollFromPosY(float pos_y, float center_y_ratio = 0.5f);        // �w�肵���ʒu��L���ɂ��邽�߂ɃX�N���[���ʂ𒲐����܂��B GetCursorPos()�܂���GetCursorStartPos()+ offset���g�p���ėL���Ȉʒu���擾���܂��B
	void          _SetStateStorage(ImGuiStorage* tree);                                // �c���[��Ԃ̃X�g���[�W�������̂��̂ɒu�������܂��i�����ő��삵�����ꍇ�́A�ʏ�͂��̃T�u�Z�N�V�������N���A���܂��j
	ImGuiStorage* _GetStateStorage();

	//==========================================================================
	//
	// �p�����[�^�X�^�b�N�i���L�j
	//
	//==========================================================================

	void          _PushFont(ImFont* font);                                             // �V���[�g�J�b�g�Ƃ���NULL���g�p���ăf�t�H���g�t�H���g���v�b�V������
	void          _PopFont();
	void          _PushStyleColor(ImGuiCol idx, ImU32 col);
	void          _PushStyleColor(ImGuiCol idx, const ImVec4& col);
	void          _PopStyleColor(int count = 1);
	void          _PushStyleVar(ImGuiStyleVar idx, float val);
	void          _PushStyleVar(ImGuiStyleVar idx, const ImVec2& val);
	void          _PopStyleVar(int count = 1);
	const ImVec4& _GetStyleColorVec4(ImGuiCol idx);                                    // ImGuiStyle�\���̂Ɋi�[����Ă���X�^�C���J���[���擾���܂��B PushStyleColor()�Ƀt�B�[�h�o�b�N���AGetColorU32()���g�p���ăX�^�C���J���[+�A���t�@���擾���܂��B
	ImFont* _GetFont();                                                          // ���݂̃t�H���g���擾����
	float         _GetFontSize();                                                      // ���݂̃t�H���g���K�p����Ă��錻�݂̃t�H���g�T�C�Y�i=�s�N�Z���P�ʂ̍����j���擾����
	ImVec2        _GetFontTexUvWhitePixel();                                           // ImDrawList API���g�p���ăJ�X�^���V�F�C�v��`�悷��ۂɕ֗���UV���W�̎擾
	ImU32         _GetColorU32(ImGuiCol idx, float alpha_mul = 1.0f);                  // �w�肳�ꂽ�X�^�C���J���[���X�^�C���A���t�@��K�p���A�I�v�V�����̃A���t�@�A���t�@
	ImU32         _GetColorU32(const ImVec4& col);                                     // �w�肳�ꂽ�F���X�^�C���A���t�@��K�p���Ď擾����
	ImU32         _GetColorU32(ImU32 col);                                             // �w�肳�ꂽ�F���X�^�C���A���t�@��K�p���Ď擾����

	//==========================================================================
	//
	// �p�����[�^�X�^�b�N�i���݂̃E�B���h�E�j
	//
	//==========================================================================

	void          _PushItemWidth(float item_width);                                    // ���ʃA�C�e���̃A�C�e���̕�+���x���̏ꍇ�A�s�N�Z���B 0.0f =�E�B���h�E�̕���2/3�܂Ńf�t�H���g�A> 0.0f�F�s�N�Z���̕��A<0.0f�E�B���h�E�̉E����xx�s�N�Z����z�u����i-1.0f�͏�ɉE���ɕ��𑵂���j
	void          _PopItemWidth();
	float         _CalcItemWidth();                                                    // �v�b�V�����ꂽ�ݒ�̃A�C�e���̕��ƌ��݂̃J�[�\���ʒu
	void          _PushTextWrapPos(float wrap_pos_x = 0.0f);                           // Text *()�R�}���h�̃��[�h���b�v�B <0.0f�F���b�s���O�Ȃ��B 0.0f�F�E�B���h�E�i�܂��̓J�����j�̏I���܂Ń��b�v���܂��B > 0.0f�F�E�B���h�E���[�J���X�y�[�X�� 'wrap_pos_x'�̈ʒu�Ń��b�v����
	void          _PopTextWrapPos();
	void          _PushAllowKeyboardFocus(bool allow_keyboard_focus);                  // �f�t�H���g�ŗL���ɂȂ��Ă���TAB / Shift-Tab���g���ăt�H�[�J�X�����킹�邱�Ƃ��ł��܂����A����̃E�B�W�F�b�g�ł͖����ɂ��邱�Ƃ��ł��܂�
	void          _PopAllowKeyboardFocus();
	void          _PushButtonRepeat(bool repeat);                                      // 'repeat'���[�h�ł́AButton *()�֐��́iio.KeyRepeatDelay / io.KeyRepeatRate�ݒ���g�p���ājtypematic�ȕ��@�ŌJ��Ԃ�true��Ԃ��܂��B Button()�̌��IsItemActive()���Ăяo���ƁA�{�^�������݂̃t���[���ɕێ�����Ă��邩�ǂ�����m�邱�Ƃ��ł��܂��B
	void          _PopButtonRepeat();

	//==========================================================================
	//
	// �J�[�\��/���C�A�E�g
	//
	//==========================================================================

	void          _Separator();                                                        // �Z�p���[�^�A��ʂɐ����ł���B ���j���[�o�[�̓����܂��͐������C�A�E�g���[�h�ł́A����͐����Z�p���[�^�ɂȂ�܂��B
	void          _SameLine(float pos_x = 0.0f, float spacing_w = -1.0f);              // �E�B�W�F�b�g�܂��̓O���[�v�Ԃ��Ăяo���Ă����𐅕��Ƀ��C�A�E�g����
	void          _NewLine();                                                          // SameLine()�����ɖ߂�
	void          _Spacing();                                                          // �����Ԋu��ǉ�����
	void          _Dummy(const ImVec2& size);                                          // �w�肳�ꂽ�T�C�Y�̃_�~�[�A�C�e����ǉ�����
	void          _Indent(float indent_w = 0.0f);                                      // �R���e���c�̈ʒu��style.IndentSpacing�܂��́I= 0�̏ꍇ��indent_w�ŉE���Ɉړ����܂��B
	void          _Unindent(float indent_w = 0.0f);                                    // �R���e���c�̈ʒu��style.IndentSpacing�܂��́I= 0�̏ꍇ��indent_w�ō��ɖ߂��܂��B
	void          _BeginGroup();                                                       // �i�O���[�v�S�̂�IsItemHovered()��SameLine()�Ȃǂ̃��C�A�E�g�v���~�e�B�u���g�p�ł���悤�ɁA�����J�n�ʒu+�O���[�v�̋��E�{�b�N�X��1�̃A�C�e���ɃL���v�`�����܂��j
	void          _EndGroup();
	ImVec2        _GetCursorPos();                                                     // �J�[�\���̈ʒu�̓E�B���h�E�̈ʒu�ɑ��ΓI�ł�
	float         _GetCursorPosX();                                                    // "
	float         _GetCursorPosY();                                                    // "
	void          _SetCursorPos(const ImVec2& local_pos);                              // "
	void          _SetCursorPosX(float x);                                             // "
	void          _SetCursorPosY(float y);                                             // "
	ImVec2        _GetCursorStartPos();                                                // �����J�[�\���ʒu
	ImVec2        _GetCursorScreenPos();                                               // �J�[�\���ʒu���΍��W[0..io.DisplaySize]�iImDrawList API���g�p����ꍇ�ɕ֗��j
	void          _SetCursorScreenPos(const ImVec2& pos);                              // ��΃X�N���[�����W�̃J�[�\���ʒu[0..io.DisplaySize]
	void          _AlignTextToFramePadding();                                          // ����̃e�L�X�g��FramePadding.y�ɐ��������ɐ���/�����܂��B����ɂ��A����̃E�B�W�F�b�g�ɃA���C�����g����܂��i�ʏ�̃E�B�W�F�b�g�̑O�ɍs���Ƀe�L�X�g������ꍇ�ɌĂяo����܂��j
	float         _GetTextLineHeight();                                                // ~ �t�H���g�T�C�Y
	float         _GetTextLineHeightWithSpacing();                                     // ~ FontSize + style.ItemSpacing.y�i�A������2�s�̃e�L�X�g�Ԃ̋����j
	float         _GetFrameHeight();                                                   // ~ FontSize + style.FramePadding.y * 2
	float         _GetFrameHeightWithSpacing();                                        // ~ FontSize + style.FramePadding.y * 2 + style.ItemSpacing.y �i�t���[���E�B�W�F�b�g��2�̘A�������s�̊Ԃ̃s�N�Z���P�ʂ̋����j

	//==========================================================================
	//
	// ��
	// SameLine�ipos_x�j��P���ȗ�Ɏg�p���邱�Ƃ��ł��܂��B ��API�͂܂��i�s���ł���A�ނ��댇���Ă��܂��B
	//
	//==========================================================================

	void          _Columns(int count = 1, const char* id = nullptr, bool border = true);
	void          _NextColumn();                                                       // ���̗�́A���݂̍s���I�������ꍇ�͌��݂̍s�܂��͎��̍s�Ƀf�t�H���g�ݒ肳��܂�
	int           _GetColumnIndex();                                                   // ���݂̗�C���f�b�N�X���擾����
	float         _GetColumnWidth(int column_index = -1);                              // �񕝂��擾���܂��i�s�N�Z���P�ʁj�B ���݂̗���g�p����ɂ�-1��n��
	void          _SetColumnWidth(int column_index, float width);                      // �񕝂��s�N�Z���P�ʂŐݒ肵�܂��B ���݂̗���g�p����ɂ�-1��n��
	float         _GetColumnOffset(int column_index = -1);                             // ��̍s�̈ʒu���擾���܂��i�R���e���c�̈�̍�������s�N�Z���P�ʁj�B ���݂̗���g�p����ꍇ��-1��n���A����ȊO�̏ꍇ��0..GetColumnsCount()���܂߂܂��B ��0�͒ʏ�0.0f�ł�
	void          _SetColumnOffset(int column_index, float offset_x);                  // ��̍s�̈ʒu��ݒ肵�܂��i�R���e���c�̈�̍�������s�N�Z���P�ʁj�B ���݂̗���g�p����ɂ�-1��n��
	int           _GetColumnsCount();

	//==========================================================================
	//
	// ID�X�R�[�v
	// ���[�v���ɃE�B�W�F�b�g���쐬����ꍇ�́A��ӂ̎��ʎq�i�I�u�W�F�N�g�|�C���^�A���[�v�C���f�b�N�X�Ȃǁj���v�b�V���������Ǝv���\�����������߁AImGui�ŋ�ʂ��邱�Ƃ��ł��܂��B
	// �E�B�W�F�b�g���x������ "## foobar"�\�����g�p���āA��������ʂ��邱�Ƃ��ł��܂��B �ڍׂɂ��ẮAFAQ�́u���x��/ ID�̎g�p�Ɋւ���v���C�}�[�v�����ǂ݂��������B
	//
	//==========================================================================

	void          _PushID(const char* str_id);                                         // ���ʎq��ID�X�^�b�N�Ƀv�b�V�����܂��B ID�̓X�^�b�N�S�̂̃n�b�V���ł��I
	void          _PushID(const char* str_id_begin, const char* str_id_end);
	void          _PushID(const void* ptr_id);
	void          _PushID(int int_id);
	void          _PopID();
	ImGuiID       _GetID(const char* str_id);                                          // ��ӂ�ID�iID�X�^�b�N�S�̂̃n�b�V��+�^����ꂽ�p�����[�^�j���v�Z���܂��B �Ⴆ�� ���Ȃ���ImGuiStorage�ɂ��Ȃ����g���Ɖ�����̂ł����
	ImGuiID       _GetID(const char* str_id_begin, const char* str_id_end);
	ImGuiID       _GetID(const void* ptr_id);

	//==========================================================================
	//
	// �E�B�W�F�b�g�F�e�L�X�g
	//
	//==========================================================================

	void          _TextUnformatted(const char* text, const char* text_end = nullptr);               // �t�H�[�}�b�g�����ɐ��̃e�L�X�g�B �e�L�X�g�i "��s"�A�e�L�X�g�j�Ƃقړ����ł����AA�j 'text_end'���w�肳��Ă���ꍇ��NULL�I���������K�v�Ƃ����AB�j�����ł����A �e�L�X�g�̃������R�s�[���s��ꂸ�A�o�b�t�@�T�C�Y�������Ȃ�
	//void          _Text(const char* fmt, ...)                                     ; // �P���ȏ����t���e�L�X�g
	void          _TextV(const char* fmt, va_list args);
	//void          _TextColored(const ImVec4& col, const char* fmt, va_list args; // �V���[�g�J�b�g for PushStyleColor(ImGuiCol_Text, col); Text(fmt, ...); PopStyleColor();
	void          _TextColoredV(const ImVec4& col, const char* fmt, va_list args);
	//void          _TextDisabled(const char* fmt, ...)                             ; // �V���[�g�J�b�g for PushStyleColor(ImGuiCol_Text, style.Colors[ImGuiCol_TextDisabled]); Text(fmt, ...); PopStyleColor();
	void          _TextDisabledV(const char* fmt, va_list args);
	//void          _TextWrapped(const char* fmt, ...)                              ; // �V���[�g�J�b�g for PushTextWrapPos(0.0f); Text(fmt, ...); PopTextWrapPos();. �E�B���h�E�̕����g�����鑼�̃E�B�W�F�b�g���Ȃ��ꍇ�́A�����T�C�Y�ύX�E�B���h�E�ł͋@�\���܂���.Yoy��SetNextWindowSize()���g�p���ăT�C�Y��ݒ肷��K�v������܂��B
	void          _TextWrappedV(const char* fmt, va_list args);
	//void          _LabelText(const char* label, const char* fmt, ...)             ; // �\���e�L�X�g+���x���͒l+���x���E�B�W�F�b�g�Ɠ������@�Ő��񂳂�܂�
	void          _LabelTextV(const char* label, const char* fmt, va_list args);
	//void          _BulletText(const char* fmt, ...)                               ; // �V���[�g�J�b�g for Bullet()+Text()
	void          _BulletTextV(const char* fmt, va_list args);
	void          _Bullet();                                                                     // �����ȉ~��`���A�����s�ɃJ�[�\����u���܂��B GetTreeNodeToLabelSpacing()�ATreeNode()�Ɠ��������ŃJ�[�\���̈ʒu��i�߂�

	//==========================================================================
	//
	// �E�B�W�F�b�g�F���C��
	//
	//==========================================================================

	bool          _Button(const char* label, const ImVec2& size = ImVec2(0, 0));            // �{�^��
	bool          _SmallButton(const char* label);                                         // �{�^����FramePadding =�i0,0�j���w�肷��ƁA�e�L�X�g���ɊȒP�ɖ��ߍ��ނ��Ƃ��ł��܂�
	bool          _InvisibleButton(const char* str_id, const ImVec2& size);                // �r�W���A���̂Ȃ��{�^���̓���A�p�u���b�NAPI�iIsItemActive�AIsItemHovered�Ȃǁj���g�p���ăJ�X�^���r�w�C�r�A���\�z����ꍇ�ɕ֗��ł��B
	void          _Image(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), const ImVec4& tint_col = ImVec4(1, 1, 1, 1), const ImVec4& border_col = ImVec4(0, 0, 0, 0));
	bool          _ImageButton(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), int frame_padding = -1, const ImVec4 & bg_col = ImVec4(0, 0, 0, 0), const ImVec4 & tint_col = ImVec4(1, 1, 1, 1));    // <0 frame_padding�́A�f�t�H���g�̃t���[�����ߍ��ݐݒ���g�p���܂��B �p�f�B���O�Ȃ��̏ꍇ��0
	bool          _Checkbox(const char* label, bool* v);
	bool          _CheckboxFlags(const char* label, unsigned int* flags, unsigned int flags_value);
	bool          _RadioButton(const char* label, bool active);
	bool          _RadioButton(const char* label, int* v, int v_button);
	void          _PlotLines(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = nullptr, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float));
	void          _PlotLines(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = nullptr, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0));
	void          _PlotHistogram(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = nullptr, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float));
	void          _PlotHistogram(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = nullptr, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0));
	void          _ProgressBar(float fraction, const ImVec2& size_arg = ImVec2(-1, 0), const char* overlay = nullptr);

	//==========================================================================
	//
	// �E�B�W�F�b�g�F�R���{�{�b�N�X
	// �V����BeginCombo()/ EndCombo()API���g�p����ƁA�R���e���c��I����Ԃ����R�ɊǗ��ł��܂��B
	// �Â�Combo()API��BeginCombo()/EndCombo()�̃w���p�[�ł���A���֐��̂��߂ɗ��p�ł��܂��B
	//
	//==========================================================================

	bool          _BeginCombo(const char* label, const char* preview_value, ImGuiComboFlags flags = 0);
	void          _EndCombo(); // BeginCombo()��true��Ԃ��ꍇ�ɂ̂݁AEndCombo()���Ăяo���Ă��������I
	bool          _Combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items = -1);
	bool          _Combo(const char* label, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items = -1);      // Separate items with \0 within a string, end item-list with \0\0. e.g. "One\0Two\0Three\0"
	bool          _Combo(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int popup_max_height_in_items = -1);

	//==========================================================================
	//
	// �E�B�W�F�b�g�F�h���b�O�i��[�Fctrl +�h���b�O�{�b�N�X���N���b�N���ăL�[�{�[�h�œ��͂���B�蓮���͒l�̓N�����v���ꂸ�A�I�t���E�ɍs�����Ƃ��ł���j
	// ���ׂĂ̊֐��̂��ׂĂ�Float2 / Float3 / Float4 / Int2 / Int3 / Int4�o�[�W�����ł́A 'float v [X]'�֐��̈����� 'float * v'�Ɠ����ł��邱�Ƃɒ��ӂ��Ă��������B �A�N�Z�X�\�ł���Ɨ\�z�����v�f�̐� �ŏ��̗v�f�̃A�h���X��A�������Z�b�g����n�����Ƃ��ł��܂��B &myvector.x
	// ���x�̓}�E�X�̓����̃s�N�Z���P�ʂł��iv_speed = 0.2f�F�}�E�X��5�s�N�Z���ړ����Ēl��1���₷�K�v������܂��j�B �Q�[���p�b�h/�L�[�{�[�h�i�r�Q�[�V�����̏ꍇ�A�Œᑬ�x��Max�iv_speed�Aminimum_step_at_given_precision�j�ł��B
	//
	//==========================================================================

	bool          _DragFloat(const char* label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f);     // v_min> = v_max�̏ꍇ�A�o�C���h����Ă��܂���
	bool          _DragFloat2(const char* label, float v[2], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f);
	bool          _DragFloat3(const char* label, float v[3], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f);
	bool          _DragFloat4(const char* label, float v[4], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f);
	bool          _DragFloatRange2(const char* label, float* v_current_min, float* v_current_max, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", const char* display_format_max = nullptr, float power = 1.0f);
	bool          _DragInt(const char* label, int* v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f");                                       // v_min> = v_max�̏ꍇ�A�o�C���h����Ă��܂���
	bool          _DragInt2(const char* label, int v[2], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f");
	bool          _DragInt3(const char* label, int v[3], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f");
	bool          _DragInt4(const char* label, int v[4], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f");
	bool          _DragIntRange2(const char* label, int* v_current_min, int* v_current_max, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f", const char* display_format_max = nullptr);

	//==========================================================================
	//
	// �E�B�W�F�b�g�F�L�[�{�[�h�ɂ�����
	//
	//==========================================================================

	bool          _InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiTextEditCallback callback = nullptr, void* user_data = nullptr);
	bool          _InputTextMultiline(const char* label, char* buf, size_t buf_size, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiTextEditCallback callback = nullptr, void* user_data = nullptr);
	bool          _InputFloat(const char* label, float* v, float step = 0.0f, float step_fast = 0.0f, int decimal_precision = -1, ImGuiInputTextFlags extra_flags = 0);
	bool          _InputFloat2(const char* label, float v[2], int decimal_precision = -1, ImGuiInputTextFlags extra_flags = 0);
	bool          _InputFloat3(const char* label, float v[3], int decimal_precision = -1, ImGuiInputTextFlags extra_flags = 0);
	bool          _InputFloat4(const char* label, float v[4], int decimal_precision = -1, ImGuiInputTextFlags extra_flags = 0);
	bool          _InputInt(const char* label, int* v, int step = 1, int step_fast = 100, ImGuiInputTextFlags extra_flags = 0);
	bool          _InputInt2(const char* label, int v[2], ImGuiInputTextFlags extra_flags = 0);
	bool          _InputInt3(const char* label, int v[3], ImGuiInputTextFlags extra_flags = 0);
	bool          _InputInt4(const char* label, int v[4], ImGuiInputTextFlags extra_flags = 0);

	//==========================================================================
	//
	// �E�B�W�F�b�g�F�X���C�_�i�q���g�Fctrl +�X���C�_���N���b�N���ăL�[�{�[�h�œ��͂��܂��B�蓮���͒l�̓N�����v���ꂸ�A�I�t���E�ɓ��邱�Ƃ�����܂��j
	//
	//==========================================================================

	bool          _SliderFloat(const char* label, float* v, float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);     // display_format�𒲐����āA�X���C�_���̃��x����P�ʕ\���̐ړ����܂��͐ڔ����Œl������܂��B �ΐ��X���C�_�ɂ�power�I= 1.0���g�p����
	bool          _SliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);
	bool          _SliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);
	bool          _SliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);
	bool          _SliderAngle(const char* label, float* v_rad, float v_degrees_min = -360.0f, float v_degrees_max = +360.0f);
	bool          _SliderInt(const char* label, int* v, int v_min, int v_max, const char* display_format = "%.0f");
	bool          _SliderInt2(const char* label, int v[2], int v_min, int v_max, const char* display_format = "%.0f");
	bool          _SliderInt3(const char* label, int v[3], int v_min, int v_max, const char* display_format = "%.0f");
	bool          _SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* display_format = "%.0f");
	bool          _VSliderFloat(const char* label, const ImVec2& size, float* v, float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);
	bool          _VSliderInt(const char* label, const ImVec2& size, int* v, int v_min, int v_max, const char* display_format = "%.0f");

	//==========================================================================
	//
	// �E�B�W�F�b�g�F�J���[�G�f�B�^/�s�b�J�[�i�q���g�FColorEdit *�̋@�\�ɂ́A�s�b�J�[���J�����߂ɍ��N���b�N���ĉE�N���b�N���ăI�v�V�������j���[���J�����Ƃ��ł���A������Ƃ����F�̃v���r���[�X�N�G�A������܂��j
	// 'float v [X]'�֐��̈����� 'float * v'�Ɠ����ł��邱�Ƃɒ��ӂ��Ă��������B�z��̍\���́A�A�N�Z�X�\�Ǝv����v�f�̐����L�^����P�Ȃ���@�ł��B �A������\���̂̂����A�ŏ���float�v�f�̃A�h���X��n�����Ƃ��ł��܂��B &myvector.x
	//
	//==========================================================================

	bool          _ColorEdit3(const char* label, float col[3], ImGuiColorEditFlags flags = 0);
	bool          _ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags = 0);
	bool          _ColorPicker3(const char* label, float col[3], ImGuiColorEditFlags flags = 0);
	bool          _ColorPicker4(const char* label, float col[4], ImGuiColorEditFlags flags = 0, const float* ref_col = nullptr);
	bool          _ColorButton(const char* desc_id, const ImVec4& col, ImGuiColorEditFlags flags = 0, ImVec2 size = ImVec2(0, 0));  // �F�t���̐����`/�{�^����\�����A�ڍׂ�\������ɂ̓z�o�[���A�����ꂽ��^��Ԃ��܂��B
	void          _SetColorEditOptions(ImGuiColorEditFlags flags);                         // ����̌`���A�s�b�J�[�̎�ނȂǂ�I������ꍇ�́A���݂̃I�v�V�������i�ʏ�̓A�v���P�[�V�����̋N�����Ɂj���������܂��B�Ăяo����_NoOptions�t���O��n���Ȃ�����A���[�U�[�͑����̐ݒ��ύX�ł��܂��B

	//==========================================================================
	//
	// �E�B�W�F�b�g�F�c���[
	//
	//==========================================================================

	bool          _TreeNode(const char* label);                                            // 'true'��Ԃ��ƁA�m�[�h�͊J���Ă���A�c���[id��id�X�^�b�N�Ƀv�b�V������܂��B ���[�U�[��TreePop()���Ăяo���ӔC������܂��B
	//bool          _TreeNode(const char* str_id, const char* fmt, ...);       // �Ȃ�ID���g�p����̂��ɂ��Ă�FAQ��ǂ�ł��������B �C�ӂ̃e�L�X�g��TreeNode()�Ɠ������x���ɑ�����ɂ́ABullet()���g�p�ł��܂��B
	//bool          _TreeNode(const void* ptr_id, const char* fmt, ...);       // "
	bool          _TreeNodeV(const char* str_id, const char* fmt, va_list args);
	bool          _TreeNodeV(const void* ptr_id, const char* fmt, va_list args);
	bool          _TreeNodeEx(const char* label, ImGuiTreeNodeFlags flags = 0);
	//bool          _TreeNodeEx(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, ...);
	//bool          _TreeNodeEx(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, ...);
	bool          _TreeNodeExV(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args);
	bool          _TreeNodeExV(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args);
	void          _TreePush(const char* str_id);                                           // ~ Indent()+ PushId()�B true��Ԃ��Ƃ��ɂ��ł�TreeNode()�ɂ���ČĂяo����Ă��܂����A���C�A�E�g�ړI��Push / Pop�������ŌĂяo�����Ƃ��ł��܂�
	void          _TreePush(const void* ptr_id = nullptr);                                    // "
	void          _TreePop();                                                              // ~ Unindent()+PopId()
	void          _TreeAdvanceToLabelPos();                                                // GetTreeNodeToLabelSpacing()�ɂ���ăJ�[�\��x�̈ʒu��i�߂�
	float         _GetTreeNodeToLabelSpacing();                                            // �ʏ��unframed TreeNode�̏ꍇ�ATreeNode *()�܂���Bullet()==�ig.FontSize + style.FramePadding.x * 2�j���g�p����Ƃ��̃��x���̑O�̐�������
	void          _SetNextTreeNodeOpen(bool is_open, ImGuiCond cond = 0);                  // ����TreeNode / CollapsingHeader�I�[�v����Ԃ�ݒ肵�܂��B
	bool          _CollapsingHeader(const char* label, ImGuiTreeNodeFlags flags = 0);      // 'true'��Ԃ��ꍇ�A�w�b�_�[�͊J���Ă��܂��B �C���f���g������AID�X�^�b�N���������肵�܂���B ���[�U�[��TreePop()���Ăяo���K�v�͂���܂���B
	bool          _CollapsingHeader(const char* label, bool* p_open, ImGuiTreeNodeFlags flags = 0); // 'p_open'��NULL�łȂ���΁A�w�b�_�̉E��ɒǉ��̏����ȕ���{�^����\�����܂�

	//==========================================================================
	//
	// �E�B�W�F�b�g�F�I���\/���X�g
	//
	//==========================================================================

	bool          _Selectable(const char* label, bool selected = false, ImGuiSelectableFlags flags = 0, const ImVec2 & size = ImVec2(0, 0));  // "bool selected"�͑I����Ԃ�ێ����܂��i�ǂݎ���p�j�B Selectable()���N���b�N���ꂽ�ꍇ��true��Ԃ��A�I����Ԃ�ύX�ł��܂��B size.x == 0.0�F�c��̕����g�p����Asize.x> 0.0�F�����w�肷��B size.y == 0.0�F���x���̍������g�p�Asize.y> 0.0�F�������w��
	bool          _Selectable(const char* label, bool* p_selected, ImGuiSelectableFlags flags = 0, const ImVec2 & size = ImVec2(0, 0));       // "bool * p_selected"�͕֗��ȃw���p�[�Ƃ��đI����ԁi�ǂݏ����\�j���w���܂��B
	bool          _ListBox(const char* label, int* current_item, const char* const items[], int items_count, int height_in_items = -1);
	bool          _ListBox(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int height_in_items = -1);
	bool          _ListBoxHeader(const char* label, const ImVec2& size = ImVec2(0, 0));     // ListBox()���J�X�^���f�[�^�܂��̓C���^���N�V�������Ď�������ꍇ�Ɏg�p���܂��B ���ListBoxFooter()���Ăяo���悤�ɂ��Ă��������B
	bool          _ListBoxHeader(const char* label, int items_count, int height_in_items = -1); // "
	void          _ListBoxFooter();                                                        // �X�N���[���̈���I������

	//==========================================================================
	//
	// �E�B�W�F�b�g�FValue()�w���p�[�B "name�Fvalue"�`���ŒP��̒l���o�͂���i�q���g�F���Ȃ��̌^���������߂ɃR�[�h���ł����Ǝ��R�ɐ錾����AImGui���O��ԂɊ֐���ǉ����邱�Ƃ��ł���j
	//
	//==========================================================================

	void          _Value(const char* prefix, bool b);
	void          _Value(const char* prefix, int v);
	void          _Value(const char* prefix, unsigned int v);
	void          _Value(const char* prefix, float v, const char* float_format = nullptr);

	//==========================================================================
	//
	// �c�[���`�b�v
	//
	//==========================================================================

	//void          _SetTooltip(const char* fmt, ...);                     // �}�E�X�J�[�\���̉��Ƀe�L�X�g�c�[���`�b�v��ݒ肵�܂��B�ʏ�AImGuI::IsItemHovered()�Ŏg�p���܂��B �ȑO��SetTooltip()�Ăяo�����I�[�o�[���C�h���܂��B
	void          _SetTooltipV(const char* fmt, va_list args);
	void          _BeginTooltip();                                                     // �c�[���`�b�v�E�B���h�E���J�n/�ǉ����܂��B �t�������̃c�[���`�b�v�i�������ނ̃R���e���c���܂ށj���쐬���܂��B
	void          _EndTooltip();

	//==========================================================================
	//
	// ���j���[
	//
	//==========================================================================

	bool          _BeginMainMenuBar();                                                 // �쐬���A�t���X�N���[���̃��j���[�o�[�ɒǉ����܂��B
	void          _EndMainMenuBar();                                                   // BeginMainMenuBar()��true��Ԃ��ꍇ�ɂ̂݁AEndMainMenuBar()���Ăяo���܂��B
	bool          _BeginMenuBar();                                                     // ���݂̃E�B���h�E�̃��j���[�o�[�ɒǉ����܂��i�e�E�B���h�E��ImGuiWindowFlags_MenuBar�t���O���ݒ肳��Ă���K�v������܂��j�B
	void          _EndMenuBar();                                                       // BeginMenuBar()��true��Ԃ��ꍇ�ɂ̂�EndMenuBar()���Ăяo���܂��B
	bool          _BeginMenu(const char* label, bool enabled = true);                  // �T�u���j���[���ڂ��쐬���܂��B true��Ԃ��ꍇ�́AEndMenu()���Ăяo���܂��B
	void          _EndMenu();                                                          // BeginMenu()��true��Ԃ��ꍇ�ɂ̂݁AEndBegin()���Ăяo���Ă��������I
	bool          _MenuItem(const char* label, const char* shortcut = nullptr, bool selected = false, bool enabled = true);  // �N������true��Ԃ��܂��B �V���[�g�J�b�g�͕֋X��\������܂����A�����_�ł�ImGui�ŏ�������܂���
	bool          _MenuItem(const char* label, const char* shortcut, bool* p_selected, bool enabled = true);              // �N�����ɐ^��Ԃ�+ p_selected�I= NULL�̏ꍇ�̓g�O���i* p_selected�j

	//==========================================================================
	//
	// �|�b�v�A�b�v
	//
	//==========================================================================

	void          _OpenPopup(const char* str_id);                                      // �|�b�v�A�b�v���J������ԂŌĂяo���i���ׂẴt���[�����Ăяo���Ȃ��ł��������j�B ���[�U�[���O�����N���b�N���邩�ABeginPopup()/ EndPopup()�u���b�N����CloseCurrentPopup()���Ăяo���ꂽ�Ƃ��Ƀ|�b�v�A�b�v�������܂��B �f�t�H���g�ł́ASelectable()/ MenuItem()��CloseCurrentPopup()���Ăяo���Ă��܂��B �|�b�v�A�b�v���ʎq�͌��݂�ID�X�^�b�N�Ƃ̑��ΓI�Ȃ��̂ł��i���������āAOpenPopup��BeginPopup�͓������x���ɂ���K�v������܂��j�B
	bool          _BeginPopup(const char* str_id, ImGuiWindowFlags flags = 0);                                             // �|�b�v�A�b�v���J���Ă���ꍇ��true��Ԃ��A�o�͂��J�n���邱�Ƃ��ł��܂��B BeginPopup()��true��Ԃ��ꍇ�ɂ̂݁AEndPopup()���Ăяo���܂��B
	bool          _BeginPopupContextItem(const char* str_id = nullptr, int mouse_button = 1);                                 // �Ō�̃A�C�e�����N���b�N����ƃw���p���J���A�|�b�v�A�b�v���J�n���܂��B �O�̍��ڂ�id���������ꍇ�ɂ̂݁ANULL��str_id��n�����Ƃ��ł��܂��B Text()�Ȃǂ̔�C���^���N�e�B�u�ȍ��ڂł�����g�p����ꍇ�́A�����Ŗ����I��ID��n���K�v������܂��B .cpp�̃R�����g��ǂށI
	bool          _BeginPopupContextWindow(const char* str_id = nullptr, int mouse_button = 1, bool also_over_items = true);  // ���݂̃E�B���h�E�ŃN���b�N����ƃ|�b�v�A�b�v���J���A�w���p�[���N�����܂��B
	bool          _BeginPopupContextVoid(const char* str_id = nullptr, int mouse_button = 1);                                 // void�iimgui�E�B���h�E���Ȃ��Ƃ���j���N���b�N����ƁA�w���p�[���J���ă|�b�v�A�b�v���J�n���܂��B
	bool          _BeginPopupModal(const char* name, bool* p_open = nullptr, ImGuiWindowFlags flags = 0);                     // ���[�_���_�C�A���O�i�^�C�g���o�[�����ʏ�̃E�B���h�E�A���[�_���E�B���h�E�̌��̂��Ƃ���u���b�N����A�O�����N���b�N���ă��[�_���E�B���h�E����邱�Ƃ͂ł��܂���j
	void          _EndPopup();                                                                                             // BeginPopupXXX()��true��Ԃ��ꍇ�ɂ̂݁AEndPopup()���Ăяo���܂��B
	bool          _OpenPopupOnItemClick(const char* str_id = nullptr, int mouse_button = 1);                                  // �Ō�̍��ڂ��N���b�N�����Ƃ��Ƀ|�b�v�A�b�v���J���w���p�[�B �J�����Ƃ���true��Ԃ��܂��B
	bool          _IsPopupOpen(const char* str_id);                                    // �|�b�v�A�b�v���J���Ă���ꍇ��true��Ԃ��܂��B
	void          _CloseCurrentPopup();                                                // �J�n�����|�b�v�A�b�v����܂��B MenuItem�܂���Selectable���N���b�N����ƁA���݂̃|�b�v�A�b�v�������I�ɕ��܂��B

	//==========================================================================
	//
	// ���M���O/�L���v�`���F�C���^�[�t�F�C�X����̂��ׂẴe�L�X�g�o�͂́Atty / file / clipboard�ɃL���v�`������܂��B �f�t�H���g�ł́A���O���Ƀc���[�m�[�h�������I�ɊJ���܂��B
	//
	//==========================================================================

	void          _LogToTTY(int max_depth = -1);                                       // tty�ւ̃��M���O���J�n����
	void          _LogToFile(int max_depth = -1, const char* filename = nullptr);         // �t�@�C���ւ̃��M���O���J�n����
	void          _LogToClipboard(int max_depth = -1);                                 // OS�N���b�v�{�[�h�ւ̃��M���O���J�n����
	void          _LogFinish();                                                        // ���M���O���~����i�t�@�C�������Ȃǁj
	void          _LogButtons();                                                       // tty / file / clipboard�ւ̃��M���O�̂��߂̃{�^����\������w���p�[
	void          _LogText(const char* fmt, va_list args);                                       // �e�L�X�g�f�[�^�����̂܂܃��O�ɓn���i�\�������Ɂj

	//==========================================================================
	//
	// �h���b�O�A���h�h���b�v
	// [BETA API]�f���R�[�h������܂���B API���i�����邩������Ȃ��B
	//
	//==========================================================================

	bool          _BeginDragDropSource(ImGuiDragDropFlags flags = 0);										// ���݂̍��ڂ��A�N�e�B�u�ȂƂ��ɌĂяo����܂��B ���ꂪtrue��Ԃ��ꍇ�́ASetDragDropPayload()+ EndDragDropSource()���Ăяo�����Ƃ��ł��܂��B
	bool          _SetDragDropPayload(const char* type, const void* data, size_t size, ImGuiCond cond = 0);// type�͍ő�12�����̃��[�U�[��`������ł��B '_'�Ŏn�܂镶����́A�M�d��imgui�����^�̂��߂ɗ\�񂳂�Ă��܂��B �f�[�^��imgui�ɂ���ăR�s�[����A�ێ�����܂��B
	void          _EndDragDropSource();                                                                    // BeginDragDropSource()��true��Ԃ��ꍇ�ɂ̂݁AEndDragDropSource()���Ăяo���܂��B
	bool          _BeginDragDropTarget();                                                                  // �A�C�e�����󂯎�����A�C�e���𑗐M������ɌĂяo���܂��B true��Ԃ��ꍇ�́AAcceptDragDropPayload()+ EndDragDropTarget()���Ăяo�����Ƃ��ł��܂��B
	const ImGuiPayload* _AcceptDragDropPayload(const char* type, ImGuiDragDropFlags flags = 0);            // �w�肳�ꂽ�^�̓��e���󂯓���܂��B ImGuiDragDropFlags_AcceptBeforeDelivery���ݒ肳��Ă���ꍇ�A�}�E�X�{�^�����������O�Ƀy�C���[�h��`�����Ƃ��ł��܂��B
	void          _EndDragDropTarget();                                                                    // BeginDragDropTarget()��true��Ԃ��ꍇ�ɂ̂݁AEndDragDropTarget()���Ăяo���܂��B

	//==========================================================================
	//
	// �N���b�s���O
	//
	//==========================================================================

	void          _PushClipRect(const ImVec2& clip_rect_min, const ImVec2& clip_rect_max, bool intersect_with_current_clip_rect);
	void          _PopClipRect();

	//==========================================================================
	//
	// �X�^�C��
	//
	//==========================================================================

	void          _StyleColorsClassic(ImGuiStyle* dst = nullptr);
	void          _StyleColorsDark(ImGuiStyle* dst = nullptr);
	void          _StyleColorsLight(ImGuiStyle* dst = nullptr);

	//==========================================================================
	//
	// �t�H�[�J�X�A�A�N�e�B�u��
	// �i�\�ł���� "If�iIsWindowAppearing()�jSetScrollHere()"���� "SetItemDefaultFocus()"���g�p���āA�i�r�Q�[�V�������򂪃}�[�W���ꂽ�Ƃ��ɃR�[�h����菇�����݊��ɂ��邱�Ƃ𐄏����܂��j
	//
	//==========================================================================

	void          _SetItemDefaultFocus();                                              // �Ō�̍��ڂ��E�B���h�E�̃f�t�H���g�t�H�[�J�X���ڂɂ���B "if�iIsWindowAppearing()�jSetScrollHere()"�̑���� "default item"���g�p���Ă��������B
	void          _SetKeyboardFocusHere(int offset = 0);                               // �t�H�[�J�X�L�[�{�[�h�����̃E�B�W�F�b�g�ɒǉ����܂��B �����̃R���|�[�l���g�E�B�W�F�b�g�̃T�u�R���|�[�l���g�ɃA�N�Z�X����ɂ́A���̃I�t�Z�b�g���g�p���܂��B �O�̃E�B�W�F�b�g�ɃA�N�Z�X����ɂ�-1���g�p���܂��B

	//==========================================================================
	//
	// ���[�e�B���e�B�[
	//
	//==========================================================================

	bool          _IsItemHovered(ImGuiHoveredFlags flags = 0);                         // �Ō�Ɍ������A�C�e���ł����H �i�����āA�g�p�\�A�|�b�v�A�b�v�ȂǂŃu���b�N����Ă��Ȃ��j�B ���̑��̃I�v�V�����ɂ��ẮAImGuiHoveredFlags���Q�Ƃ��Ă��������B
	bool          _IsItemActive();                                                     // �Ō�̃A�C�e���̓A�N�e�B�u�ł����H �i�Ⴆ�΁A�{�^����������Ă���A�e�L�X�g�t�B�[���h���ҏW�� - ���ݍ�p���Ȃ��A�C�e���͏��false��Ԃ��j
	bool          _IsItemFocused();                                                    // �L�[�{�[�h/�Q�[���p�b�h�i�r�Q�[�V�����̂��߂̍Ō�̍��ڂł����H
	bool          _IsItemClicked(int mouse_button = 0);                                // �Ō�ɃN���b�N���ꂽ���ڂł����H �i�{�^��/�m�[�h���N���b�N�����Ȃǁj
	bool          _IsItemVisible();                                                    // �Ō�̍��ڂ��\������Ă��܂����H �i�؂蔲��/�X�N���[���ɂ�鎋�o��Q�ł͂���܂���j
	bool          _IsAnyItemHovered();
	bool          _IsAnyItemActive();
	bool          _IsAnyItemFocused();
	ImVec2        _GetItemRectMin();                                                   // �Ō�̃A�C�e���̋��E��`����ʋ�ԂɎ擾����
	ImVec2        _GetItemRectMax();                                                   // "
	ImVec2        _GetItemRectSize();                                                  // ��ʋ�Ԃ̍Ō�̃A�C�e���̃T�C�Y���擾����
	void          _SetItemAllowOverlap();                                              // �Ō�̍��ڂ����̍��ڂƏd�������邱�Ƃ��ł��܂��B �g�p����Ă��Ȃ��̈���L���b�`���邽�߂ɕs���̃{�^����I���\�Ȃ��̂Ȃǂŕ֗��Ȃ��Ƃ�����܂��B
	bool          _IsWindowFocused(ImGuiFocusedFlags flags = 0);                       // ���݂̃E�B���h�E�Ƀt�H�[�J�X���Ă��܂����H �܂��̓t���O�ɉ����Ă��̃��[�g/�q�ɂȂ�܂��B �I�v�V�����̃t���O���Q�Ƃ��Ă��������B
	bool          _IsWindowHovered(ImGuiHoveredFlags flags = 0);                       // ���݂̃E�B���h�E���z�o�����O����Ă��܂��i�ʏ�A�|�b�v�A�b�v/���[�_���Ńu���b�N����܂���j�B �I�v�V�����̃t���O���Q�Ƃ��Ă��������B
	bool          _IsRectVisible(const ImVec2& size);                                  // �w�肳�ꂽ�T�C�Y�̋�`���J�[�\���ʒu����n�܂��Ă��邩�ǂ������e�X�g���܂��B�N���b�v����܂���B
	bool          _IsRectVisible(const ImVec2& rect_min, const ImVec2& rect_max);      // ��`�i��ʋ�ԓ��j�������ǂ����e�X�g���܂��B ���[�U�̑��őe���N���b�s���O�����s����B
	double         _GetTime();
	int           _GetFrameCount();
	ImDrawList* _GetOverlayDrawList();                                               // ���̕`�惊�X�g�͍Ō�Ƀ����_�����O���ꂽ���̂ŁA�I�[�o�[���C�̐}�`��e�L�X�g��f�����`�悷��̂ɕ֗��ł�
	ImDrawListSharedData* _GetDrawListSharedData();
	const char* _GetStyleColorName(ImGuiCol idx);
	ImVec2        _CalcTextSize(const char* text, const char* text_end = nullptr, bool hide_text_after_double_hash = false, float wrap_width = -1.0f);
	void          _CalcListClipping(int items_count, float items_height, int* out_items_display_start, int* out_items_display_end);    // �ϓ��ɑ傫���̂���A�C�e���̑傫�ȃ��X�g�̂��߂̑e���N���b�s���O���v�Z���܂��B �\�ł���΁AImGuiListClipper�̏�ʃw���p�[���g�p���邱�Ƃ������߂��܂��B

	bool          _BeginChildFrame(ImGuiID id, const ImVec2& size, ImGuiWindowFlags flags = 0); // �ʏ�̃E�B�W�F�b�g�t���[���̂悤�Ɍ�����q�E�B���h�E/�X�N���[���̈���쐬����w���p�[
	void          _EndChildFrame();                                                    // BeginChildFrame()�̖߂�l�i�܂肽���܂ꂽ�E�B���h�E�܂��̓N���b�v���ꂽ�E�B���h�E�������j�Ɋ֌W�Ȃ��A���EndChildFrame()���Ăяo���܂��B

	ImVec4        _ColorConvertU32ToFloat4(ImU32 in);
	ImU32         _ColorConvertFloat4ToU32(const ImVec4& in);
	void          _ColorConvertRGBtoHSV(float r, float g, float b, float& out_h, float& out_s, float& out_v);
	void          _ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b);

	//==========================================================================
	//
	// ����
	//
	//==========================================================================

	int           _GetKeyIndex(ImGuiKey imgui_key);                                    // ImGuiKey_ *�̒l�����[�U�[�̃L�[�C���f�b�N�X�Ƀ}�b�v���܂��B == io.KeyMap [key]
	bool          _IsKeyDown(int user_key_index);                                      // �L�[���J�Â���Ă��܂��B == io.KeysDown [user_key_index]�B imgui��io.KeyDown []�̊e�G���g���̈Ӗ���m��Ȃ����Ƃɒ��ӂ��Ă��������B ���Ȃ��̃o�b�N�G���h/�G���W����������KeyDown []�ɕۑ�������@�ɉ����āA�Ǝ��̃C���f�b�N�X/�񋓌^���g�p���Ă��������I
	bool          _IsKeyPressed(int user_key_index, bool repeat = true);               // �L�[�������ꂽ�i�_�E������_�E���ցj�B repeat = true�̏ꍇ�Aio.KeyRepeatDelay / KeyRepeatRate���g�p���܂��B
	bool          _IsKeyReleased(int user_key_index);                                  // �L�[�������[�X����܂����i�_�E������_�E���ցj
	int           _GetKeyPressedAmount(int key_index, float repeat_delay, float rate); // �񋟂��ꂽ�J��Ԃ����[�g/�x�����g�p���܂��B �J�E���g��Ԃ��܂��B�قƂ�ǂ̏ꍇ0�܂���1�ł����ARepeatRate��DeltaTime> RepeatRate
	bool          _IsMouseDown(int button);                                            // �}�E�X�{�^����������Ă���
	bool          _IsMouseClicked(int button, bool repeat = false);                    // �}�E�X�{�^�����N���b�N�������i�I�_�E������_�E���j
	bool          _IsMouseDoubleClicked(int button);                                   // �}�E�X�{�^�����_�u���N���b�N���܂����B �_�u���N���b�N��IsMouseClicked()��false��Ԃ��܂��B io.MouseDoubleClickTime���g�p���܂��B
	bool          _IsMouseReleased(int button);                                        // �}�E�X�{�^����������܂����i�_�E������_�E���ցj
	bool          _IsMouseDragging(int button = 0, float lock_threshold = -1.0f);      // �}�E�X�h���b�O�ł��B lock_threshold <-1.0f��io.MouseDraggingThreshold���g�p����ꍇ
	bool          _IsMouseHoveringRect(const ImVec2& r_min, const ImVec2& r_max, bool clip = true);  // �}�E�X���}�E�X�̏�ɒu����Ă��܂��i�X�N���[���X�y�[�X�Łj�B ���݂̃N���b�s���O�ݒ�ŃN���b�v����܂��B �t�H�[�J�X/�E�B���h�E�����̍l���̖���/�|�b�v�A�b�v�ɂ���ău���b�N����܂��B
	bool          _IsMousePosValid(const ImVec2* mouse_pos = nullptr);                    //
	ImVec2        _GetMousePos();                                                      // ImGui::GetIO()�ւ̃V���[�g�J�b�g�B���[�U�[���񋟂���MousePos�B���̌Ăяo���ƈ�ѐ�������
	ImVec2        _GetMousePosOnOpeningCurrentPopup();                                 // ��������BeginPopup()�������ă|�b�v�A�b�v���J�����Ƀ}�E�X�̈ʒu�̃o�b�N�A�b�v���擾
	ImVec2        _GetMouseDragDelta(int button = 0, float lock_threshold = -1.0f);    // �N���b�N���Ă���h���b�O���܂��B lock_threshold <-1.0f��io.MouseDraggingThreshold���g�p����ꍇ
	void          _ResetMouseDragDelta(int button = 0);                                //
	ImGuiMouseCursor _GetMouseCursor();                                                // ImGui::NewFrame()�Ń��Z�b�g�������J�[�\���^�C�v���擾���܂��B����̓t���[�����ɍX�V����܂��B Render()�̑O�ɗL���ł��B io.MouseDrawCursor��ݒ肵�ă\�t�g�E�F�A�����_�����O���g�p����ꍇ�AImGui�͂����������_�����O���܂�
	void          _SetMouseCursor(ImGuiMouseCursor type);                              // ��]�̃J�[�\���^�C�v��ݒ肷��
	void          _CaptureKeyboardFromApp(bool capture = true);                        // �蓮��io.WantCaptureKeyboard�t���O�����̃t���[���ɃI�[�o�[���C�h���܂��i���̃t���O�̓A�v���P�[�V�����n���h���̂��߂Ɋ��S�Ɏc����Ă��܂��j�B �Ⴆ�� ���Ȃ��̃E�B�W�F�b�g���z�o�����O����Ă���Ƃ��ɋ����I�ɃL���v�`���L�[�{�[�h�B
	void          _CaptureMouseFromApp(bool capture = true);                           // �蓮��io.WantCaptureMouse�t���O�����̃t���[���ɃI�[�o�[���C�h���܂��i���̃t���O�́A�A�v���P�[�V�����n���h���̂��߂Ɋ��S�Ɏc����Ă��܂��j�B

	//==========================================================================
	//
	// �w���p�[�́A�������A���P�[�^�ƃN���b�v�{�[�h�֐��ɃA�N�Z�X����@�\�������Ă��܂��B
	//
	//==========================================================================

	void          _SetAllocatorFunctions(void* (*alloc_func)(size_t sz, void* user_data), void(*free_func)(void* ptr, void* user_data), void* user_data = nullptr);
	void* _MemAlloc(size_t size);
	void          _MemFree(void* ptr);
	const char* _GetClipboardText();
	void          _SetClipboardText(const char* text);

	/**
	@brief �e�L�X�g����
	@param format [in] ���͕�����
	@param args [in] �\�����������l
	@return string �e�L�X�g
	*/
	template<typename ...Args>
	inline const std::string CreateText(const std::string& format, const Args& ... args)
	{
#if defined(_MSLIB_DEBUG)
		size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
		std::unique_ptr<char[]> buf(new char[size]);
		snprintf(buf.get(), size, format.c_str(), args ...);
		return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
#else
		decoy(format, args ...);
		return format;
#endif
	}
};

_MSLIB_END

/*

struct  ImGuiStyle
{
float        Alpha ;                       //�O���[�o���A���t�@��ImGui
ImVec2       WindowPadding�̂��ׂĂɓK�p����܂��B              //�E�B���h�E���̃p�f�B���O
ImVec2       WindowMinSize ;               //�ŏ��E�B���h�E�T�C�Y
float        WindowRounding ;              //�E�B���h�E�R�[�i�[�̊ۂ߂̔��a�B0.0f�ɐݒ肷��ƁA�����`�̃E�B���h�E���\������܂�
�BImGuiAlign   WindowTitleAlign ;            //�^�C�g���o�[�̃e�L�X�g�̐���
float        ChildWindowRounding ;         //�q�E�B���h�E�̎l���̊ۂ߂̔��a�B�����`�̃E�B���h�E�����悤��0.0f�ɐݒ�
ImVec2       �t���[���p�b�f�B���O;                //�t���[�������ꂽ��`����
�]���i�قƂ�ǂ̃E�B�W�F�b�g�Ŏg�p�����jfloat        FrameRounding ;               //�t���[���R�[�i�[�̊ۂ߂̔��a�B�قƂ�ǂ̃E�B�W�F�b�g�Ŏg�p����钷���`�̃t���[�������ɂ́A0.0f�ɐݒ肵�܂��B
ImVec2       ItemSpacing ;                 //�E�B�W�F�b�g/���C���Ԃ̐��������Ɛ��������̊Ԋu
ImVec2       ItemInnerSpacing ;            //�������ꂽ�E�B�W�F�b�g�̗v�f���ł̐��������Ɛ��������̊Ԋu�i�X���C�_�Ƃ��̃��x���Ȃǁj
ImVec2       TouchExtraPadding ;          //�^�b�`�ʒu�����m�ł͂Ȃ��^�b�`�x�[�X�̃V�X�e���̃��A�N�V�����o�E���f�B���O�{�b�N�X���g������B�c�O�Ȃ���A��X�̓E�B�W�F�b�g���\�[�g���Ȃ��̂ŁA�I�[�o�[���b�v�̗D�揇�ʂ͏�ɍŏ��̃E�B�W�F�b�g�ɗ^�����܂��B�����炱������܂�傫�����Ȃ��ł��������I
float        IndentSpacing ;               //�Ⴆ�΁A�c���[�m�[�h�ɓ���Ƃ��̉��C���f���g�B��ʓI��==�iFontSize + FramePadding.x * 2�j�B
float        ColumnsMinSpacing ;           // 2�̗�̊Ԃ̍ŏ��̐����X�y�[�V���O
float        ScrollbarSize ;               //�����X�N���[���o�[�̕��A�����X�N���[���o�[�̍���
float        ScrollbarRounding ;           //�X�N���[���o�[�̃O���u�̊p�̔��a
float        GrabMinSize ;                //�X���C�_/�X�N���[���o�[�̃O���u�{�b�N�X�̍ŏ���/����
float        GrabRounding ;                //�O���u�p�̊ۂ߂̔��a�B�����`�̃X���C�_�[�O���u�����ɂ�0.0f�ɐݒ肵�܂��B
ImVec2       DisplayWindowPadding ;        //�E�B���h�E�̈ʒu�́A���Ȃ��Ƃ����̗ʂ����\���̈���ɕ\�������悤�ɌŒ肳��܂��B�ʏ�̃E�B���h�E�݂̂��J�o�[���܂��B
ImVec2       DisplaySafeAreaPadding ;      //��ʂ̒[�����邱�Ƃ��ł��Ȃ��ꍇ�i�Ⴆ��TV�Łj�A���S�̈�̃p�f�B���O�𑝂₵�Ă��������B�ʏ�̃E�B���h�E�Ɠ��l�Ƀ|�b�v�A�b�v/�c�[���`�b�v���J�o�[���܂��B
bool         AntiAliasedLines ;            //���C��/�{�[�_�[�ŃA���`�G�C���A�X��L���ɂ���B���Ȃ����{����CPU / GPU�Ń^�C�g�ȏꍇ�͖����ɂ��Ă��������B
bool         AntiAliasedShapes;           //�h��Ԃ��ꂽ�}�`�i�ۂ��l�p�`�A�~�Ȃǁj�ŃA���`�G�C���A�X��L���ɂ���
float        CurveTessellationTol ;        //�e�b�Z���[�V�������e�l�B���x�Ƀe�b�Z���[�V�������ꂽ�J�[�u�i���i���A���p�`�j�����炵�A�i����ቺ�����܂��B
ImVec4��      �F[ ImGuiCol_COUNT ];

  ImGuiStyle �i�j;
};



// Cinder-ImGui
const  auto  opts  =  ui :: Options �i�j�̗�
�ł��BantiAliasedLines �i�^�j
�BantiAliasedShapes �itrue �j
�ł��BwindowRounding �i0.0 F �j
�BframeRounding �i0.0 f �j;

ui :: initialize �iopts �j;


// https://github.com/ocornut/imgui/blob/v1.49/imgui.h#L592-L638
enum  ImGuiCol_
{
ImGuiCol_Text �A
ImGuiCol_TextDisabled �A
ImGuiCol_WindowBg �A              //�ʏ�̃E�B���h�E��
�w�iImGuiCol_ChildWindowBg �A         //�q�E�B���h�E�̔w�i
ImGuiCol_PopupBg �A               //�|�b�v�A�b�v�A���j���[�A�c�[���`�b�v�E�B���h�E��
�w�iImGuiCol_Border �A
ImGuiCol_BorderShadow �A
ImGuiCol_FrameBg �A               //�`�F�b�N�{�b�N�X�A���W�I�{�^���A�v���b�g�A�X���C�_�A�e�L�X�g���͂�
�w�iImGuiCol_FrameBgHovered �A
ImGuiCol_FrameBgActive �A
ImGuiCol_TitleBg �A
ImGuiCol_TitleBgCollapsed �A
ImGuiCol_TitleBgActive �A
ImGuiCol_MenuBarBg �A
ImGuiCol_ScrollbarBg �A
ImGuiCol_ScrollbarGrab �A
ImGuiCol_ScrollbarGrabHovered �A
ImGuiCol_ScrollbarGrabActive �A
ImGuiCol_ComboBg �A
ImGuiCol_CheckMark �A
ImGuiCol_SliderGrab �A
ImGuiCol_SliderGrabActive �A
ImGuiCol_Button �A
ImGuiCol_ButtonHovered �A
ImGuiCol_ButtonActive �A
ImGuiCol_Header �A
ImGuiCol_HeaderHovered �A
ImGuiCol_HeaderActive �A
ImGuiCol_Column �A
ImGuiCol_ColumnHovered �A
ImGuiCol_ColumnActive �A
ImGuiCol_ResizeGrip �A
ImGuiCol_ResizeGripHovered �A
ImGuiCol_ResizeGripActive �A
ImGuiCol_CloseButton �A
ImGuiCol_CloseButtonHovered �A
ImGuiCol_CloseButtonActive �A
ImGuiCol_PlotLines �A
ImGuiCol_PlotLinesHovered �A
ImGuiCol_PlotHistogram �A
ImGuiCol_PlotHistogramHovered �A
ImGuiCol_TextSelectedBg �A
ImGuiCol_ModalWindowDarkening �A  //���[�_���E�B���h�E���A�N�e�B�u�ł���ꍇ�A��ʑS�̂��Â�
ImGuiCol_COUNT
}�B

*/