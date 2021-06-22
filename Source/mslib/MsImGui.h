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
#define DIRECTINPUT_VERSION (0x0800) // DirectInputのバージョン指定
#include <dinput.h>
#include <tchar.h>

#include "mslib.hpp"

_MSLIB_BEGIN

namespace imgui
{
	/**
	@brief 初期化
	@param hWnd [in] ウィンドウハンドル
	@param pDevice [in] デバイス
	@return 失敗時に true が返ります
	*/
	bool Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice);

	/**
	@brief 解放
	*/
	void Uninit(void);

	/**
	@brief 更新
	*/
	void WindowInfo(void);

	/**
	@brief 描画
	*/
	void Draw(LPDIRECT3DDEVICE9 pDevice);

	/**
	@brief 描画 (Handle loss of D3D9 device)
	@param result [in] Component Object Model defines, and macros
	@param pDevice [in] デバイス
	@param pd3dpp [in] デバイス
	*/
	void DeviceReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pd3dpp);

	/**
	@brief WndProc (Process Win32 mouse/keyboard inputs)
	@param hWnd [in] ウィンドウハンドル
	@param uMsg [in] メッセージ
	@param wParam [in] ダブルパラム
	@param lParam [in] エルパラム
	@return Types use for passing & returning polymorphic values
	*/
	LRESULT ImGui_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	/**
	@brief メッセージ
	@param hWnd [in] ウィンドウハンドル
	@param uMsg [in] メッセージ
	@param wParam [in] ダブルパラム
	@param lParam [in] エルパラム
	@param pDevice [in] デバイス
	@param pd3dpp [in] デバイス
	@return Types use for passing & returning polymorphic values
	*/
	LRESULT SetMenu(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pd3dpp);

	/**
	@brief 新しいウィンドウ開始
	@param label [in] ウィンドウ名
	@param p_open [in] falseで開けない/trueで開ける
	@param flags [in] ImGuiWindowFlags_::??
	*/
	void NewWindow(const std::string& label, bool p_open, ImGuiWindowFlags flags = 0);

	/**
	@brief 新しいウィンドウ開始
	@param label [in] ウィンドウ名
	@param p_open [in] falseで開けない/trueで開ける
	@param size_on_first_use [in] サイズ指定
	@param bg_alpha_override [in]
	@param flags [in] ImGuiWindowFlags_::??
	*/
	void NewWindow(const std::string& label, bool p_open, const ImVec2& size_on_first_use, ImGuiWindowFlags flags, float bg_alpha_override = -1.0f);

	/**
	@brief 新しいウィンドウ開始
	@param label [in] ウィンドウ名
	@param p_open [in] falseで開けない/trueで開ける
	@param size_on_first_use [in] サイズ指定
	@param bg_alpha_override [in]
	*/
	void FixedWindow(const std::string& label, bool p_open, const ImVec2& size_on_first_use, float bg_alpha_override = -1.0f);

	/**
	@brief ウィンドウ終了
	*/
	void EndWindow(void);

	/**
	@brief 次のウィンドウの表示位置を設定
	@param pos [in] 座標
	@param cond [in]
	@param pivot [in]
	*/
	void SetNextWindowPos(const ImVec2& pos, ImGuiCond cond = 0, const ImVec2 & pivot = ImVec2(0, 0));

	/**
	@brief スクロールバー int値操作
	@param label [in] スクロールバー名
	@param v [in/out] 操作対象
	@param v_min [in] 操作範囲の最小
	@param v_max [in] 操作範囲の最大
	@param display_format [in] 表示形式
	@return 処理時に true が返ります
	*/
	bool SliderInt(const std::string& label, int* v, int v_min, int v_max, const char* display_format = "%f");

	/**
	@brief スクロールバー float値操作
	@param label [in] スクロールバー名
	@param v [in/out] 操作対象
	@param v_min [in] 操作範囲の最小
	@param v_max [in] 操作範囲の最大
	@param power [in] 操作倍率
	@param display_format [in] 表示形式
	@return 処理時に true が返ります
	*/
	bool SliderFloat(const std::string& label, float* v, float v_min, float v_max, float power = (1.0f), const char* display_format = "%f");

	/**
	@brief ボタン
	@param label [in] ボタン名
	@param size [in] ボタンサイズ
	@return 処理時に true が返ります
	*/
	bool Button(const std::string& label, const ImVec2& size = ImVec2(0, 0));

	/**
	@brief 線を引きます
	*/
	void Separator(void);

	/**
	@brief 階層構造開始
	@param label [in] 構造名
	@param is_open [in] false デフォルトで閉じています/true デフォルトで開いています
	@param args [in] 表示したいデータ
	@return 処理時に true が返ります
	*/
	bool NewTreeNode(const std::string& label, bool is_open);

	/**
	@brief 階層構造終わり
	*/
	void EndTreeNode(void);

	/**
	@brief テキスト表示
	@param label [in] 表示内容
	*/
	void Text(const std::string& label);

	/**
	@brief 入力ボックス
	@param label [in] デフォルトの内容
	@return 入力内容
	*/
	bool InputText(const std::string& label, std::string& Out, ImGuiInputTextFlags flags = 0, ImGuiTextEditCallback callback = nullptr, void* user_data = nullptr);

	/**
	@brief 表示フレーム開始
	*/
	void NewFrame(void);

	/**
	@brief NewFrame が呼ばれたかどうかチェックします
	*/
	bool NewFrameCheckCall();

	/**
	@brief 表示フレーム開始終わり
	*/
	void EndFrame(void);

	/**
	@brief チェックボックス
	@param label [in] チェックボックス名
	@param v [in/out] 操作対象
	@return 処理時に true が返ります
	*/
	bool Checkbox(const std::string& label, bool& v);

	/**
	@brief デコイ
	@param label [in] デコイ化
	*/
	void decoy(const std::string& label, ...);

	/**
	@brief メニューバーの開始
	@return 処理時に true が返ります
	*/
	bool NewMenuBar(void);

	/**
	@brief メニューバーの終了
	*/
	void EndMenuBar(void);

	/**
	@brief メニュー内アイテムの登録
	@param label [in] アイテム名
	@param shortcut [in]
	@param selected [in]
	@param enabled [in]
	@return 処理時に true が返ります
	*/
	bool MenuItem(const std::string& label, const char* shortcut = nullptr, bool selected = false, bool enabled = true);

	/**
	@brief メニュー開始
	@param label [in] メニュー名
	@param enabled [in] falseでメニュー無効/trueで有効
	@return 処理時に true が返ります
	*/
	bool NewMenu(const std::string& label, bool enabled = true);

	/**
	@brief メニュー終わり
	*/
	void EndMenu(void);

	/**
	@brief カラーエディタ
	@param _color [in] 操作対象
	@return 操作した色が返ります
	*/
	D3DXCOLOR ColorEdit(const D3DXCOLOR& _color);

	/**
	@brief テクスチャ描画
	@param user_texture_id [in] テクスチャポインタ
	@param size [in] テクスチャサイズ
	@param master_size [in] 基準となる描画サイズ(w,h共通)
	*/
	void Image(LPDIRECT3DTEXTURE9 user_texture_id, const ImVec2& size, const ImVec4& tint_col, const ImVec4& border_col, float master_size = 100.0f);

	//==========================================================================
	//
	//
	// ImGui Wrapper
	//
	//
	//==========================================================================

	// コンテキストの作成とアクセス、複数のコンテキストを使用する場合は、モジュール間でコンテキストを共有します（DLLなど）。
	// デフォルトでは、すべてのコンテキストが同じImFontAtlasを共有します。 別のフォントアトラスが必要な場合は、それらをnew()してGetIO()。ImguiコンテキストのFonts変数を上書きすることができます。
	// これらの関数はすべて現在のコンテキストに依存しません。 
	ImGuiContext* _CreateContext(ImFontAtlas* shared_font_atlas = nullptr);
	void          _DestroyContext(ImGuiContext* ctx = nullptr);   // nullptr = Destroy current context
	ImGuiContext* _GetCurrentContext();
	void          _SetCurrentContext(ImGuiContext* ctx);

	//==========================================================================
	//
	// メイン
	//
	//==========================================================================

	ImGuiIO& _GetIO();
	ImGuiStyle& _GetStyle();
	ImDrawData* _GetDrawData();                           // io.RenderDrawListsFn()関数に渡される値と同じです。 Render()の後とNewFrame()への次の呼び出しまで有効です。
	void          _NewFrame();                              // 新しいImGuiフレームを開始するときは、Render()/EndFrame()までこのコマンドを実行することができます。
	void          _Render();                                // ImGuiフレームを終了し、描画データを確定してから、設定されている場合はio.RenderDrawListsFn()関数を呼び出します。
	void          _EndFrame();                              // 私はImGuiフレームを完成させます。 Render()によって自動的に呼び出されるため、直接呼び出す必要はありません。 レンダリングを実行する必要がない場合、EndFrame()は呼び出すことができますが、CPUを無駄にします。 レンダリングする必要がない場合は、imguiウィンドウを作成しないでください。

	//==========================================================================
	//
	// デモ、デバッグ、情報
	//
	//==========================================================================

	void          _ShowDemoWindow(bool* p_open = nullptr);        // デモ/テストウィンドウ（以前はShowTestWindowと呼ばれていました）を作成します。 ほとんどのImGuiの機能を示しています。 ライブラリについて学ぶためにこれを呼んでください！ あなたのアプリケーションでいつでも利用できるようにしてください！
	void          _ShowMetricsWindow(bool* p_open = nullptr);     // メトリックウィンドウを作成します。 ImGuiの内部を表示する：描画コマンド（個々の描画呼び出しと頂点付き）、ウィンドウリスト、基本的な内部状態など
	void          _ShowStyleEditor(ImGuiStyle* ref = nullptr);    // スタイルエディタブロックを追加します（ウィンドウではありません）。 比較するImGuiStyle構造体を渡して元に戻して保存することができます（それ以外の場合はデフォルトスタイルを使用します）
	bool          _ShowStyleSelector(const char* label);
	void          _ShowFontSelector(const char* label);
	void          _ShowUserGuide();                            // 基本的なヘルプ/情報ブロック（ウィンドウではない）を追加する：ImGuiをエンドユーザ（マウス/キーボードコントロール）として操作する方法。
	const char* _GetVersion();

	//==========================================================================
	//
	// Window
	//
	//==========================================================================

	bool          _Begin(const char* name, bool* p_open = nullptr, ImGuiWindowFlags flags = 0);   // ウィンドウをスタックにプッシュして追加を開始します。 詳細は.cppを参照してください。 ウィンドウが折りたたまれているときにfalseを返すので（コード内で早めに行うことができます）、End()を常に呼び出す必要があります。 'bool * p_open'は右上にウィジェットを作成してウィンドウを閉じます（boolをfalseに設定します）。
	void          _End();                                                              // Begin()がfalseを返す場合でも常に呼び出されます（折りたたまれたウィンドウを示します）！ 現在のウィンドウに追加を終了し、ウィンドウスタックからポップします。
	bool          _BeginChild(const char* str_id, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags flags = 0);  // スクロール領域を開始します。 size == 0.0f：残りのウィンドウサイズ、サイズ<0.0f：残りのウィンドウサイズからabs（サイズ）を引いた値を使用します。 サイズ> 0.0f：固定サイズ。 各軸は異なるモードを使用することができる。 ImVec2（0,400）。
	bool          _BeginChild(ImGuiID id, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags flags = 0);          // "
	void          _EndChild();                                                         // BeginChild()がfalseを返す場合でも常に呼び出されます（子ウィンドウが折りたたまれているかクリッピングされていることを示します）
	ImVec2        _GetContentRegionMax();                                              // 現在のコンテンツ境界（通常、スクロールを含むウィンドウ境界、または現在の列境界）、ウィンドウ座標
	ImVec2        _GetContentRegionAvail();                                            // == GetContentRegionMax() - GetCursorPos()
	float         _GetContentRegionAvailWidth();                                       //
	ImVec2        _GetWindowContentRegionMin();                                        // content boundaries min (roughly (0,0)-Scroll), ウィンドウ座標
	ImVec2        _GetWindowContentRegionMax();                                        // content boundaries max (roughly (0,0)+Size-Scroll) Sizeは、SetNextWindowContentSize()を使用してウィンドウ座標でオーバーライドすることができます
	float         _GetWindowContentRegionWidth();                                      //
	ImDrawList* _GetWindowDrawList();                                                // 独自の描画プリミティブを追加する場合は、描画コマンドリストを取得する
	ImVec2        _GetWindowPos();                                                     // 画面スペース内の現在のウィンドウ位置を取得します（DrawList APIを使用して独自の描画を行いたい場合に便利です）
	ImVec2        _GetWindowSize();                                                    // 現在のウィンドウサイズを取得する
	float         _GetWindowWidth();
	float         _GetWindowHeight();
	bool          _IsWindowCollapsed();
	bool          _IsWindowAppearing();
	void          _SetWindowFontScale(float scale);                                    // ウィンドウごとのフォントサイズ。 すべてのウィンドウを拡大/縮小する場合は、TO.Font GlobalScaleを調整します。

	void          _SetNextWindowPos(const ImVec2& pos, ImGuiCond cond = 0, const ImVec2 & pivot = ImVec2(0, 0)); // 次のウィンドウ位置を設定します。 Begin()の前に呼び出します。 ピボット=（0.5f、0.5f）を使用して、与えられた点を中心にします。
	void          _SetNextWindowSize(const ImVec2& size, ImGuiCond cond = 0);          // 次のウィンドウサイズを設定します。 この軸にオートフィットを強制するには、0.0fに軸を設定します。 Begin()の前に呼び出す
	void          _SetNextWindowSizeConstraints(const ImVec2& size_min, const ImVec2& size_max, ImGuiSizeCallback custom_callback = nullptr, void* custom_callback_data = nullptr); // 次のウィンドウサイズ制限を設定します。 X / Y軸のいずれかで-1、-1を使用して現在のサイズを維持します。 コールバックを使用して、プログラム上の制約を軽く適用します。
	void          _SetNextWindowContentSize(const ImVec2& size);                       // 次のウィンドウのコンテンツサイズを設定する（スクロールバーの範囲を強制する）。 ウィンドウ装飾（タイトルバー、メニューバーなど）は含まれません。 0.0fに軸を設定して自動にします。 Begin()の前に呼び出す
	void          _SetNextWindowCollapsed(bool collapsed, ImGuiCond cond = 0);         // 次のウィンドウの折り畳み状態を設定します。 Begin()の前に呼び出す
	void          _SetNextWindowFocus();                                               // 次のウィンドウをフォーカス/最前面に設定します。 Begin()の前に呼び出す
	void          _SetNextWindowBgAlpha(float alpha);                                  // 次のウィンドウの背景色アルファを設定します。 ImGuiCol_WindowBg / ChildBg / PopupBgを簡単に変更するヘルパー。
	void          _SetWindowPos(const char* name, const ImVec2& pos, ImGuiCond cond = 0);      // 名前付きウィンドウの位置を設定します。
	void          _SetWindowSize(const char* name, const ImVec2& size, ImGuiCond cond = 0);    // 名前付きウィンドウサイズを設定します。 この軸にオートフィットを強制するには、0.0fに軸を設定します。
	void          _SetWindowCollapsed(const char* name, bool collapsed, ImGuiCond cond = 0);   // 名前付きウィンドウの折り畳み状態を設定する
	void          _SetWindowFocus(const char* name);                                           // 指定されたウィンドウをフォーカス/最前面に設定します。 フォーカスを削除するにはNULLを使用します。

	float         _GetScrollX();                                                       // スクロール量を取得する [0..GetScrollMaxX()]
	float         _GetScrollY();                                                       // スクロール量を取得する [0..GetScrollMaxY()]
	float         _GetScrollMaxX();                                                    // 最大のスクロール量を得る ~~ ContentSize.X - WindowSize.X
	float         _GetScrollMaxY();                                                    // 最大のスクロール量を得る ~~ ContentSize.Y - WindowSize.Y
	void          _SetScrollX(float scroll_x);                                         // スクロール量を設定する [0..GetScrollMaxX()]
	void          _SetScrollY(float scroll_y);                                         // スクロール量を設定する [0..GetScrollMaxY()]
	void          _SetScrollHere(float center_y_ratio = 0.5f);                         // スクロール量を調整して、現在のカーソル位置を表示させます。 center_y_ratio = 0.0：top、0.5：center、1.0：bottom。 「デフォルト/現在のアイテム」を表示するために使用する場合は、代わりにSetItemDefaultFocus()を使用することを検討してください。
	void          _SetScrollFromPosY(float pos_y, float center_y_ratio = 0.5f);        // 指定した位置を有効にするためにスクロール量を調整します。 GetCursorPos()またはGetCursorStartPos()+ offsetを使用して有効な位置を取得します。
	void          _SetStateStorage(ImGuiStorage* tree);                                // ツリー状態のストレージを自分のものに置き換えます（自分で操作したい場合は、通常はそのサブセクションをクリアします）
	ImGuiStorage* _GetStateStorage();

	//==========================================================================
	//
	// パラメータスタック（共有）
	//
	//==========================================================================

	void          _PushFont(ImFont* font);                                             // ショートカットとしてNULLを使用してデフォルトフォントをプッシュする
	void          _PopFont();
	void          _PushStyleColor(ImGuiCol idx, ImU32 col);
	void          _PushStyleColor(ImGuiCol idx, const ImVec4& col);
	void          _PopStyleColor(int count = 1);
	void          _PushStyleVar(ImGuiStyleVar idx, float val);
	void          _PushStyleVar(ImGuiStyleVar idx, const ImVec2& val);
	void          _PopStyleVar(int count = 1);
	const ImVec4& _GetStyleColorVec4(ImGuiCol idx);                                    // ImGuiStyle構造体に格納されているスタイルカラーを取得します。 PushStyleColor()にフィードバックし、GetColorU32()を使用してスタイルカラー+アルファを取得します。
	ImFont* _GetFont();                                                          // 現在のフォントを取得する
	float         _GetFontSize();                                                      // 現在のフォントが適用されている現在のフォントサイズ（=ピクセル単位の高さ）を取得する
	ImVec2        _GetFontTexUvWhitePixel();                                           // ImDrawList APIを使用してカスタムシェイプを描画する際に便利なUV座標の取得
	ImU32         _GetColorU32(ImGuiCol idx, float alpha_mul = 1.0f);                  // 指定されたスタイルカラーをスタイルアルファを適用し、オプションのアルファアルファ
	ImU32         _GetColorU32(const ImVec4& col);                                     // 指定された色をスタイルアルファを適用して取得する
	ImU32         _GetColorU32(ImU32 col);                                             // 指定された色をスタイルアルファを適用して取得する

	//==========================================================================
	//
	// パラメータスタック（現在のウィンドウ）
	//
	//==========================================================================

	void          _PushItemWidth(float item_width);                                    // 共通アイテムのアイテムの幅+ラベルの場合、ピクセル。 0.0f =ウィンドウの幅の2/3までデフォルト、> 0.0f：ピクセルの幅、<0.0fウィンドウの右側にxxピクセルを配置する（-1.0fは常に右側に幅を揃える）
	void          _PopItemWidth();
	float         _CalcItemWidth();                                                    // プッシュされた設定のアイテムの幅と現在のカーソル位置
	void          _PushTextWrapPos(float wrap_pos_x = 0.0f);                           // Text *()コマンドのワードラップ。 <0.0f：ラッピングなし。 0.0f：ウィンドウ（またはカラム）の終わりまでラップします。 > 0.0f：ウィンドウローカルスペースの 'wrap_pos_x'の位置でラップする
	void          _PopTextWrapPos();
	void          _PushAllowKeyboardFocus(bool allow_keyboard_focus);                  // デフォルトで有効になっているTAB / Shift-Tabを使ってフォーカスを合わせることができますが、特定のウィジェットでは無効にすることができます
	void          _PopAllowKeyboardFocus();
	void          _PushButtonRepeat(bool repeat);                                      // 'repeat'モードでは、Button *()関数は（io.KeyRepeatDelay / io.KeyRepeatRate設定を使用して）typematicな方法で繰り返しtrueを返します。 Button()の後にIsItemActive()を呼び出すと、ボタンが現在のフレームに保持されているかどうかを知ることができます。
	void          _PopButtonRepeat();

	//==========================================================================
	//
	// カーソル/レイアウト
	//
	//==========================================================================

	void          _Separator();                                                        // セパレータ、一般に水平である。 メニューバーの内側または水平レイアウトモードでは、これは垂直セパレータになります。
	void          _SameLine(float pos_x = 0.0f, float spacing_w = -1.0f);              // ウィジェットまたはグループ間を呼び出してそれらを水平にレイアウトする
	void          _NewLine();                                                          // SameLine()を元に戻す
	void          _Spacing();                                                          // 垂直間隔を追加する
	void          _Dummy(const ImVec2& size);                                          // 指定されたサイズのダミーアイテムを追加する
	void          _Indent(float indent_w = 0.0f);                                      // コンテンツの位置をstyle.IndentSpacingまたは！= 0の場合はindent_wで右側に移動します。
	void          _Unindent(float indent_w = 0.0f);                                    // コンテンツの位置をstyle.IndentSpacingまたは！= 0の場合はindent_wで左に戻します。
	void          _BeginGroup();                                                       // （グループ全体でIsItemHovered()やSameLine()などのレイアウトプリミティブを使用できるように、水平開始位置+グループの境界ボックスを1つのアイテムにキャプチャします）
	void          _EndGroup();
	ImVec2        _GetCursorPos();                                                     // カーソルの位置はウィンドウの位置に相対的です
	float         _GetCursorPosX();                                                    // "
	float         _GetCursorPosY();                                                    // "
	void          _SetCursorPos(const ImVec2& local_pos);                              // "
	void          _SetCursorPosX(float x);                                             // "
	void          _SetCursorPosY(float y);                                             // "
	ImVec2        _GetCursorStartPos();                                                // 初期カーソル位置
	ImVec2        _GetCursorScreenPos();                                               // カーソル位置を絶対座標[0..io.DisplaySize]（ImDrawList APIを使用する場合に便利）
	void          _SetCursorScreenPos(const ImVec2& pos);                              // 絶対スクリーン座標のカーソル位置[0..io.DisplaySize]
	void          _AlignTextToFramePadding();                                          // 次回のテキストをFramePadding.yに垂直方向に整列/下げます。これにより、今後のウィジェットにアライメントされます（通常のウィジェットの前に行頭にテキストがある場合に呼び出されます）
	float         _GetTextLineHeight();                                                // ~ フォントサイズ
	float         _GetTextLineHeightWithSpacing();                                     // ~ FontSize + style.ItemSpacing.y（連続する2行のテキスト間の距離）
	float         _GetFrameHeight();                                                   // ~ FontSize + style.FramePadding.y * 2
	float         _GetFrameHeightWithSpacing();                                        // ~ FontSize + style.FramePadding.y * 2 + style.ItemSpacing.y （フレームウィジェットの2つの連続した行の間のピクセル単位の距離）

	//==========================================================================
	//
	// 列
	// SameLine（pos_x）を単純な列に使用することもできます。 列APIはまだ進行中であり、むしろ欠けています。
	//
	//==========================================================================

	void          _Columns(int count = 1, const char* id = nullptr, bool border = true);
	void          _NextColumn();                                                       // 次の列は、現在の行が終了した場合は現在の行または次の行にデフォルト設定されます
	int           _GetColumnIndex();                                                   // 現在の列インデックスを取得する
	float         _GetColumnWidth(int column_index = -1);                              // 列幅を取得します（ピクセル単位）。 現在の列を使用するには-1を渡す
	void          _SetColumnWidth(int column_index, float width);                      // 列幅をピクセル単位で設定します。 現在の列を使用するには-1を渡す
	float         _GetColumnOffset(int column_index = -1);                             // 列の行の位置を取得します（コンテンツ領域の左側からピクセル単位）。 現在の列を使用する場合は-1を渡し、それ以外の場合は0..GetColumnsCount()を含めます。 列0は通常0.0fです
	void          _SetColumnOffset(int column_index, float offset_x);                  // 列の行の位置を設定します（コンテンツ領域の左側からピクセル単位）。 現在の列を使用するには-1を渡す
	int           _GetColumnsCount();

	//==========================================================================
	//
	// IDスコープ
	// ループ内にウィジェットを作成する場合は、一意の識別子（オブジェクトポインタ、ループインデックスなど）をプッシュしたいと思う可能性が高いため、ImGuiで区別することができます。
	// ウィジェットラベル内の "## foobar"構文を使用して、それらを区別することもできます。 詳細については、FAQの「ラベル/ IDの使用に関するプライマー」をお読みください。
	//
	//==========================================================================

	void          _PushID(const char* str_id);                                         // 識別子をIDスタックにプッシュします。 IDはスタック全体のハッシュです！
	void          _PushID(const char* str_id_begin, const char* str_id_end);
	void          _PushID(const void* ptr_id);
	void          _PushID(int int_id);
	void          _PopID();
	ImGuiID       _GetID(const char* str_id);                                          // 一意のID（IDスタック全体のハッシュ+与えられたパラメータ）を計算します。 例えば あなたがImGuiStorageにあなた自身を照会したいのであれば
	ImGuiID       _GetID(const char* str_id_begin, const char* str_id_end);
	ImGuiID       _GetID(const void* ptr_id);

	//==========================================================================
	//
	// ウィジェット：テキスト
	//
	//==========================================================================

	void          _TextUnformatted(const char* text, const char* text_end = nullptr);               // フォーマットせずに生のテキスト。 テキスト（ "％s"、テキスト）とほぼ同じですが、A） 'text_end'が指定されている場合はNULL終了文字列を必要とせず、B）高速ですが、 テキストのメモリコピーが行われず、バッファサイズ制限もなく
	//void          _Text(const char* fmt, ...)                                     ; // 単純な書式付きテキスト
	void          _TextV(const char* fmt, va_list args);
	//void          _TextColored(const ImVec4& col, const char* fmt, va_list args; // ショートカット for PushStyleColor(ImGuiCol_Text, col); Text(fmt, ...); PopStyleColor();
	void          _TextColoredV(const ImVec4& col, const char* fmt, va_list args);
	//void          _TextDisabled(const char* fmt, ...)                             ; // ショートカット for PushStyleColor(ImGuiCol_Text, style.Colors[ImGuiCol_TextDisabled]); Text(fmt, ...); PopStyleColor();
	void          _TextDisabledV(const char* fmt, va_list args);
	//void          _TextWrapped(const char* fmt, ...)                              ; // ショートカット for PushTextWrapPos(0.0f); Text(fmt, ...); PopTextWrapPos();. ウィンドウの幅を拡張する他のウィジェットがない場合は、自動サイズ変更ウィンドウでは機能しません.YoyはSetNextWindowSize()を使用してサイズを設定する必要があります。
	void          _TextWrappedV(const char* fmt, va_list args);
	//void          _LabelText(const char* label, const char* fmt, ...)             ; // 表示テキスト+ラベルは値+ラベルウィジェットと同じ方法で整列されます
	void          _LabelTextV(const char* label, const char* fmt, va_list args);
	//void          _BulletText(const char* fmt, ...)                               ; // ショートカット for Bullet()+Text()
	void          _BulletTextV(const char* fmt, va_list args);
	void          _Bullet();                                                                     // 小さな円を描き、同じ行にカーソルを置きます。 GetTreeNodeToLabelSpacing()、TreeNode()と同じ距離でカーソルの位置を進める

	//==========================================================================
	//
	// ウィジェット：メイン
	//
	//==========================================================================

	bool          _Button(const char* label, const ImVec2& size = ImVec2(0, 0));            // ボタン
	bool          _SmallButton(const char* label);                                         // ボタンにFramePadding =（0,0）を指定すると、テキスト内に簡単に埋め込むことができます
	bool          _InvisibleButton(const char* str_id, const ImVec2& size);                // ビジュアルのないボタンの動作、パブリックAPI（IsItemActive、IsItemHoveredなど）を使用してカスタムビヘイビアを構築する場合に便利です。
	void          _Image(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), const ImVec4& tint_col = ImVec4(1, 1, 1, 1), const ImVec4& border_col = ImVec4(0, 0, 0, 0));
	bool          _ImageButton(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), int frame_padding = -1, const ImVec4 & bg_col = ImVec4(0, 0, 0, 0), const ImVec4 & tint_col = ImVec4(1, 1, 1, 1));    // <0 frame_paddingは、デフォルトのフレーム埋め込み設定を使用します。 パディングなしの場合は0
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
	// ウィジェット：コンボボックス
	// 新しいBeginCombo()/ EndCombo()APIを使用すると、コンテンツや選択状態を自由に管理できます。
	// 古いCombo()APIはBeginCombo()/EndCombo()のヘルパーであり、利便性のために利用できます。
	//
	//==========================================================================

	bool          _BeginCombo(const char* label, const char* preview_value, ImGuiComboFlags flags = 0);
	void          _EndCombo(); // BeginCombo()がtrueを返す場合にのみ、EndCombo()を呼び出してください！
	bool          _Combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items = -1);
	bool          _Combo(const char* label, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items = -1);      // Separate items with \0 within a string, end item-list with \0\0. e.g. "One\0Two\0Three\0"
	bool          _Combo(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int popup_max_height_in_items = -1);

	//==========================================================================
	//
	// ウィジェット：ドラッグ（先端：ctrl +ドラッグボックスをクリックしてキーボードで入力する。手動入力値はクランプされず、オフ境界に行くことができる）
	// すべての関数のすべてのFloat2 / Float3 / Float4 / Int2 / Int3 / Int4バージョンでは、 'float v [X]'関数の引数は 'float * v'と同じであることに注意してください。 アクセス可能であると予想される要素の数 最初の要素のアドレスを連続したセットから渡すことができます。 &myvector.x
	// 速度はマウスの動きのピクセル単位です（v_speed = 0.2f：マウスを5ピクセル移動して値を1増やす必要があります）。 ゲームパッド/キーボードナビゲーションの場合、最低速度はMax（v_speed、minimum_step_at_given_precision）です。
	//
	//==========================================================================

	bool          _DragFloat(const char* label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f);     // v_min> = v_maxの場合、バインドされていません
	bool          _DragFloat2(const char* label, float v[2], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f);
	bool          _DragFloat3(const char* label, float v[3], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f);
	bool          _DragFloat4(const char* label, float v[4], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f);
	bool          _DragFloatRange2(const char* label, float* v_current_min, float* v_current_max, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", const char* display_format_max = nullptr, float power = 1.0f);
	bool          _DragInt(const char* label, int* v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f");                                       // v_min> = v_maxの場合、バインドされていません
	bool          _DragInt2(const char* label, int v[2], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f");
	bool          _DragInt3(const char* label, int v[3], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f");
	bool          _DragInt4(const char* label, int v[4], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f");
	bool          _DragIntRange2(const char* label, int* v_current_min, int* v_current_max, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f", const char* display_format_max = nullptr);

	//==========================================================================
	//
	// ウィジェット：キーボードによる入力
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
	// ウィジェット：スライダ（ヒント：ctrl +スライダをクリックしてキーボードで入力します。手動入力値はクランプされず、オフ境界に入ることがあります）
	//
	//==========================================================================

	bool          _SliderFloat(const char* label, float* v, float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);     // display_formatを調整して、スライダ内のラベルや単位表示の接頭辞または接尾辞で値を飾ります。 対数スライダにはpower！= 1.0を使用する
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
	// ウィジェット：カラーエディタ/ピッカー（ヒント：ColorEdit *の機能には、ピッカーを開くために左クリックして右クリックしてオプションメニューを開くことができる、ちょっとした色のプレビュースクエアがあります）
	// 'float v [X]'関数の引数は 'float * v'と同じであることに注意してください。配列の構文は、アクセス可能と思われる要素の数を記録する単なる方法です。 連続する構造体のうち、最初のfloat要素のアドレスを渡すことができます。 &myvector.x
	//
	//==========================================================================

	bool          _ColorEdit3(const char* label, float col[3], ImGuiColorEditFlags flags = 0);
	bool          _ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags = 0);
	bool          _ColorPicker3(const char* label, float col[3], ImGuiColorEditFlags flags = 0);
	bool          _ColorPicker4(const char* label, float col[4], ImGuiColorEditFlags flags = 0, const float* ref_col = nullptr);
	bool          _ColorButton(const char* desc_id, const ImVec4& col, ImGuiColorEditFlags flags = 0, ImVec2 size = ImVec2(0, 0));  // 色付きの正方形/ボタンを表示し、詳細を表示するにはホバーし、押されたら真を返します。
	void          _SetColorEditOptions(ImGuiColorEditFlags flags);                         // 既定の形式、ピッカーの種類などを選択する場合は、現在のオプションを（通常はアプリケーションの起動時に）初期化します。呼び出しに_NoOptionsフラグを渡さない限り、ユーザーは多くの設定を変更できます。

	//==========================================================================
	//
	// ウィジェット：ツリー
	//
	//==========================================================================

	bool          _TreeNode(const char* label);                                            // 'true'を返すと、ノードは開いており、ツリーidはidスタックにプッシュされます。 ユーザーはTreePop()を呼び出す責任があります。
	//bool          _TreeNode(const char* str_id, const char* fmt, ...);       // なぜIDを使用するのかについてのFAQを読んでください。 任意のテキストをTreeNode()と同じレベルに揃えるには、Bullet()を使用できます。
	//bool          _TreeNode(const void* ptr_id, const char* fmt, ...);       // "
	bool          _TreeNodeV(const char* str_id, const char* fmt, va_list args);
	bool          _TreeNodeV(const void* ptr_id, const char* fmt, va_list args);
	bool          _TreeNodeEx(const char* label, ImGuiTreeNodeFlags flags = 0);
	//bool          _TreeNodeEx(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, ...);
	//bool          _TreeNodeEx(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, ...);
	bool          _TreeNodeExV(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args);
	bool          _TreeNodeExV(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args);
	void          _TreePush(const char* str_id);                                           // ~ Indent()+ PushId()。 trueを返すときにすでにTreeNode()によって呼び出されていますが、レイアウト目的でPush / Popを自分で呼び出すことができます
	void          _TreePush(const void* ptr_id = nullptr);                                    // "
	void          _TreePop();                                                              // ~ Unindent()+PopId()
	void          _TreeAdvanceToLabelPos();                                                // GetTreeNodeToLabelSpacing()によってカーソルxの位置を進める
	float         _GetTreeNodeToLabelSpacing();                                            // 通常のunframed TreeNodeの場合、TreeNode *()またはBullet()==（g.FontSize + style.FramePadding.x * 2）を使用するときのラベルの前の水平距離
	void          _SetNextTreeNodeOpen(bool is_open, ImGuiCond cond = 0);                  // 次のTreeNode / CollapsingHeaderオープン状態を設定します。
	bool          _CollapsingHeader(const char* label, ImGuiTreeNodeFlags flags = 0);      // 'true'を返す場合、ヘッダーは開いています。 インデントしたり、IDスタックを押したりしません。 ユーザーはTreePop()を呼び出す必要はありません。
	bool          _CollapsingHeader(const char* label, bool* p_open, ImGuiTreeNodeFlags flags = 0); // 'p_open'がNULLでなければ、ヘッダの右上に追加の小さな閉じるボタンを表示します

	//==========================================================================
	//
	// ウィジェット：選択可能/リスト
	//
	//==========================================================================

	bool          _Selectable(const char* label, bool selected = false, ImGuiSelectableFlags flags = 0, const ImVec2 & size = ImVec2(0, 0));  // "bool selected"は選択状態を保持します（読み取り専用）。 Selectable()がクリックされた場合はtrueを返し、選択状態を変更できます。 size.x == 0.0：残りの幅を使用する、size.x> 0.0：幅を指定する。 size.y == 0.0：ラベルの高さを使用、size.y> 0.0：高さを指定
	bool          _Selectable(const char* label, bool* p_selected, ImGuiSelectableFlags flags = 0, const ImVec2 & size = ImVec2(0, 0));       // "bool * p_selected"は便利なヘルパーとして選択状態（読み書き可能）を指します。
	bool          _ListBox(const char* label, int* current_item, const char* const items[], int items_count, int height_in_items = -1);
	bool          _ListBox(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int height_in_items = -1);
	bool          _ListBoxHeader(const char* label, const ImVec2& size = ImVec2(0, 0));     // ListBox()がカスタムデータまたはインタラクションを再実装する場合に使用します。 後でListBoxFooter()を呼び出すようにしてください。
	bool          _ListBoxHeader(const char* label, int items_count, int height_in_items = -1); // "
	void          _ListBoxFooter();                                                        // スクロール領域を終了する

	//==========================================================================
	//
	// ウィジェット：Value()ヘルパー。 "name：value"形式で単一の値を出力する（ヒント：あなたの型を扱うためにコード内でもっと自由に宣言する、ImGui名前空間に関数を追加することができる）
	//
	//==========================================================================

	void          _Value(const char* prefix, bool b);
	void          _Value(const char* prefix, int v);
	void          _Value(const char* prefix, unsigned int v);
	void          _Value(const char* prefix, float v, const char* float_format = nullptr);

	//==========================================================================
	//
	// ツールチップ
	//
	//==========================================================================

	//void          _SetTooltip(const char* fmt, ...);                     // マウスカーソルの下にテキストツールチップを設定します。通常、ImGuI::IsItemHovered()で使用します。 以前のSetTooltip()呼び出しをオーバーライドします。
	void          _SetTooltipV(const char* fmt, va_list args);
	void          _BeginTooltip();                                                     // ツールチップウィンドウを開始/追加します。 フル装備のツールチップ（あらゆる種類のコンテンツを含む）を作成します。
	void          _EndTooltip();

	//==========================================================================
	//
	// メニュー
	//
	//==========================================================================

	bool          _BeginMainMenuBar();                                                 // 作成し、フルスクリーンのメニューバーに追加します。
	void          _EndMainMenuBar();                                                   // BeginMainMenuBar()がtrueを返す場合にのみ、EndMainMenuBar()を呼び出します。
	bool          _BeginMenuBar();                                                     // 現在のウィンドウのメニューバーに追加します（親ウィンドウにImGuiWindowFlags_MenuBarフラグが設定されている必要があります）。
	void          _EndMenuBar();                                                       // BeginMenuBar()がtrueを返す場合にのみEndMenuBar()を呼び出します。
	bool          _BeginMenu(const char* label, bool enabled = true);                  // サブメニュー項目を作成します。 trueを返す場合は、EndMenu()を呼び出します。
	void          _EndMenu();                                                          // BeginMenu()がtrueを返す場合にのみ、EndBegin()を呼び出してください！
	bool          _MenuItem(const char* label, const char* shortcut = nullptr, bool selected = false, bool enabled = true);  // 起動時にtrueを返します。 ショートカットは便宜上表示されますが、現時点ではImGuiで処理されません
	bool          _MenuItem(const char* label, const char* shortcut, bool* p_selected, bool enabled = true);              // 起動時に真を返す+ p_selected！= NULLの場合はトグル（* p_selected）

	//==========================================================================
	//
	// ポップアップ
	//
	//==========================================================================

	void          _OpenPopup(const char* str_id);                                      // ポップアップを開いた状態で呼び出す（すべてのフレームを呼び出さないでください）。 ユーザーが外部をクリックするか、BeginPopup()/ EndPopup()ブロック内でCloseCurrentPopup()が呼び出されたときにポップアップが閉じられます。 デフォルトでは、Selectable()/ MenuItem()はCloseCurrentPopup()を呼び出しています。 ポップアップ識別子は現在のIDスタックとの相対的なものです（したがって、OpenPopupとBeginPopupは同じレベルにする必要があります）。
	bool          _BeginPopup(const char* str_id, ImGuiWindowFlags flags = 0);                                             // ポップアップが開いている場合はtrueを返し、出力を開始することができます。 BeginPopup()がtrueを返す場合にのみ、EndPopup()を呼び出します。
	bool          _BeginPopupContextItem(const char* str_id = nullptr, int mouse_button = 1);                                 // 最後のアイテムをクリックするとヘルパが開き、ポップアップを開始します。 前の項目にidがあった場合にのみ、NULLのstr_idを渡すことができます。 Text()などの非インタラクティブな項目でそれを使用する場合は、ここで明示的なIDを渡す必要があります。 .cppのコメントを読む！
	bool          _BeginPopupContextWindow(const char* str_id = nullptr, int mouse_button = 1, bool also_over_items = true);  // 現在のウィンドウでクリックするとポップアップを開き、ヘルパーを起動します。
	bool          _BeginPopupContextVoid(const char* str_id = nullptr, int mouse_button = 1);                                 // void（imguiウィンドウがないところ）をクリックすると、ヘルパーが開いてポップアップを開始します。
	bool          _BeginPopupModal(const char* name, bool* p_open = nullptr, ImGuiWindowFlags flags = 0);                     // モーダルダイアログ（タイトルバーを持つ通常のウィンドウ、モーダルウィンドウの後ろのやりとりをブロックする、外部をクリックしてモーダルウィンドウを閉じることはできません）
	void          _EndPopup();                                                                                             // BeginPopupXXX()がtrueを返す場合にのみ、EndPopup()を呼び出します。
	bool          _OpenPopupOnItemClick(const char* str_id = nullptr, int mouse_button = 1);                                  // 最後の項目をクリックしたときにポップアップを開くヘルパー。 開いたときにtrueを返します。
	bool          _IsPopupOpen(const char* str_id);                                    // ポップアップが開いている場合はtrueを返します。
	void          _CloseCurrentPopup();                                                // 開始したポップアップを閉じます。 MenuItemまたはSelectableをクリックすると、現在のポップアップが自動的に閉じます。

	//==========================================================================
	//
	// ロギング/キャプチャ：インターフェイスからのすべてのテキスト出力は、tty / file / clipboardにキャプチャされます。 デフォルトでは、ログ中にツリーノードが自動的に開きます。
	//
	//==========================================================================

	void          _LogToTTY(int max_depth = -1);                                       // ttyへのロギングを開始する
	void          _LogToFile(int max_depth = -1, const char* filename = nullptr);         // ファイルへのロギングを開始する
	void          _LogToClipboard(int max_depth = -1);                                 // OSクリップボードへのロギングを開始する
	void          _LogFinish();                                                        // ロギングを停止する（ファイルを閉じるなど）
	void          _LogButtons();                                                       // tty / file / clipboardへのロギングのためのボタンを表示するヘルパー
	void          _LogText(const char* fmt, va_list args);                                       // テキストデータをそのままログに渡す（表示せずに）

	//==========================================================================
	//
	// ドラッグアンドドロップ
	// [BETA API]デモコードがありません。 APIが進化するかもしれない。
	//
	//==========================================================================

	bool          _BeginDragDropSource(ImGuiDragDropFlags flags = 0);										// 現在の項目がアクティブなときに呼び出されます。 これがtrueを返す場合は、SetDragDropPayload()+ EndDragDropSource()を呼び出すことができます。
	bool          _SetDragDropPayload(const char* type, const void* data, size_t size, ImGuiCond cond = 0);// typeは最大12文字のユーザー定義文字列です。 '_'で始まる文字列は、貴重なimgui内部型のために予約されています。 データはimguiによってコピーされ、保持されます。
	void          _EndDragDropSource();                                                                    // BeginDragDropSource()がtrueを返す場合にのみ、EndDragDropSource()を呼び出します。
	bool          _BeginDragDropTarget();                                                                  // アイテムを受け取ったアイテムを送信した後に呼び出します。 trueを返す場合は、AcceptDragDropPayload()+ EndDragDropTarget()を呼び出すことができます。
	const ImGuiPayload* _AcceptDragDropPayload(const char* type, ImGuiDragDropFlags flags = 0);            // 指定された型の内容を受け入れます。 ImGuiDragDropFlags_AcceptBeforeDeliveryが設定されている場合、マウスボタンが離される前にペイロードを覗くことができます。
	void          _EndDragDropTarget();                                                                    // BeginDragDropTarget()がtrueを返す場合にのみ、EndDragDropTarget()を呼び出します。

	//==========================================================================
	//
	// クリッピング
	//
	//==========================================================================

	void          _PushClipRect(const ImVec2& clip_rect_min, const ImVec2& clip_rect_max, bool intersect_with_current_clip_rect);
	void          _PopClipRect();

	//==========================================================================
	//
	// スタイル
	//
	//==========================================================================

	void          _StyleColorsClassic(ImGuiStyle* dst = nullptr);
	void          _StyleColorsDark(ImGuiStyle* dst = nullptr);
	void          _StyleColorsLight(ImGuiStyle* dst = nullptr);

	//==========================================================================
	//
	// フォーカス、アクティブ化
	// （可能であれば "If（IsWindowAppearing()）SetScrollHere()"よりも "SetItemDefaultFocus()"を使用して、ナビゲーション分岐がマージされたときにコードをより順方向互換にすることを推奨します）
	//
	//==========================================================================

	void          _SetItemDefaultFocus();                                              // 最後の項目をウィンドウのデフォルトフォーカス項目にする。 "if（IsWindowAppearing()）SetScrollHere()"の代わりに "default item"を使用してください。
	void          _SetKeyboardFocusHere(int offset = 0);                               // フォーカスキーボードを次のウィジェットに追加します。 複数のコンポーネントウィジェットのサブコンポーネントにアクセスするには、正のオフセットを使用します。 前のウィジェットにアクセスするには-1を使用します。

	//==========================================================================
	//
	// ユーティリティー
	//
	//==========================================================================

	bool          _IsItemHovered(ImGuiHoveredFlags flags = 0);                         // 最後に見つけたアイテムですか？ （そして、使用可能、ポップアップなどでブロックされていない）。 その他のオプションについては、ImGuiHoveredFlagsを参照してください。
	bool          _IsItemActive();                                                     // 最後のアイテムはアクティブですか？ （例えば、ボタンが押されている、テキストフィールドが編集中 - 相互作用しないアイテムは常にfalseを返す）
	bool          _IsItemFocused();                                                    // キーボード/ゲームパッドナビゲーションのための最後の項目ですか？
	bool          _IsItemClicked(int mouse_button = 0);                                // 最後にクリックされた項目ですか？ （ボタン/ノードをクリックしたなど）
	bool          _IsItemVisible();                                                    // 最後の項目が表示されていますか？ （切り抜き/スクロールによる視覚障害ではありません）
	bool          _IsAnyItemHovered();
	bool          _IsAnyItemActive();
	bool          _IsAnyItemFocused();
	ImVec2        _GetItemRectMin();                                                   // 最後のアイテムの境界矩形を画面空間に取得する
	ImVec2        _GetItemRectMax();                                                   // "
	ImVec2        _GetItemRectSize();                                                  // 画面空間の最後のアイテムのサイズを取得する
	void          _SetItemAllowOverlap();                                              // 最後の項目を次の項目と重複させることができます。 使用されていない領域をキャッチするために不可視のボタンや選択可能なものなどで便利なことがあります。
	bool          _IsWindowFocused(ImGuiFocusedFlags flags = 0);                       // 現在のウィンドウにフォーカスしていますか？ またはフラグに応じてそのルート/子になります。 オプションのフラグを参照してください。
	bool          _IsWindowHovered(ImGuiHoveredFlags flags = 0);                       // 現在のウィンドウがホバリングされています（通常、ポップアップ/モーダルでブロックされません）。 オプションのフラグを参照してください。
	bool          _IsRectVisible(const ImVec2& size);                                  // 指定されたサイズの矩形がカーソル位置から始まっているかどうかをテストします。クリップされません。
	bool          _IsRectVisible(const ImVec2& rect_min, const ImVec2& rect_max);      // 矩形（画面空間内）が可視かどうかテストします。 ユーザの側で粗いクリッピングを実行する。
	double         _GetTime();
	int           _GetFrameCount();
	ImDrawList* _GetOverlayDrawList();                                               // この描画リストは最後にレンダリングされたもので、オーバーレイの図形やテキストを素早く描画するのに便利です
	ImDrawListSharedData* _GetDrawListSharedData();
	const char* _GetStyleColorName(ImGuiCol idx);
	ImVec2        _CalcTextSize(const char* text, const char* text_end = nullptr, bool hide_text_after_double_hash = false, float wrap_width = -1.0f);
	void          _CalcListClipping(int items_count, float items_height, int* out_items_display_start, int* out_items_display_end);    // 均等に大きさのあるアイテムの大きなリストのための粗いクリッピングを計算します。 可能であれば、ImGuiListClipperの上位ヘルパーを使用することをお勧めします。

	bool          _BeginChildFrame(ImGuiID id, const ImVec2& size, ImGuiWindowFlags flags = 0); // 通常のウィジェットフレームのように見える子ウィンドウ/スクロール領域を作成するヘルパー
	void          _EndChildFrame();                                                    // BeginChildFrame()の戻り値（折りたたまれたウィンドウまたはクリップされたウィンドウを示す）に関係なく、常にEndChildFrame()を呼び出します。

	ImVec4        _ColorConvertU32ToFloat4(ImU32 in);
	ImU32         _ColorConvertFloat4ToU32(const ImVec4& in);
	void          _ColorConvertRGBtoHSV(float r, float g, float b, float& out_h, float& out_s, float& out_v);
	void          _ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b);

	//==========================================================================
	//
	// 入力
	//
	//==========================================================================

	int           _GetKeyIndex(ImGuiKey imgui_key);                                    // ImGuiKey_ *の値をユーザーのキーインデックスにマップします。 == io.KeyMap [key]
	bool          _IsKeyDown(int user_key_index);                                      // キーが開催されています。 == io.KeysDown [user_key_index]。 imguiはio.KeyDown []の各エントリの意味を知らないことに注意してください。 あなたのバックエンド/エンジンがそれらをKeyDown []に保存する方法に応じて、独自のインデックス/列挙型を使用してください！
	bool          _IsKeyPressed(int user_key_index, bool repeat = true);               // キーが押された（ダウンからダウンへ）。 repeat = trueの場合、io.KeyRepeatDelay / KeyRepeatRateを使用します。
	bool          _IsKeyReleased(int user_key_index);                                  // キーがリリースされました（ダウンからダウンへ）
	int           _GetKeyPressedAmount(int key_index, float repeat_delay, float rate); // 提供された繰り返しレート/遅延を使用します。 カウントを返します。ほとんどの場合0または1ですが、RepeatRateがDeltaTime> RepeatRate
	bool          _IsMouseDown(int button);                                            // マウスボタンが押されている
	bool          _IsMouseClicked(int button, bool repeat = false);                    // マウスボタンをクリックしたか（！ダウンからダウン）
	bool          _IsMouseDoubleClicked(int button);                                   // マウスボタンをダブルクリックしました。 ダブルクリックはIsMouseClicked()でfalseを返します。 io.MouseDoubleClickTimeを使用します。
	bool          _IsMouseReleased(int button);                                        // マウスボタンが放されました（ダウンからダウンへ）
	bool          _IsMouseDragging(int button = 0, float lock_threshold = -1.0f);      // マウスドラッグです。 lock_threshold <-1.0fがio.MouseDraggingThresholdを使用する場合
	bool          _IsMouseHoveringRect(const ImVec2& r_min, const ImVec2& r_max, bool clip = true);  // マウスがマウスの上に置かれています（スクリーンスペースで）。 現在のクリッピング設定でクリップされます。 フォーカス/ウィンドウ順序の考慮の無視/ポップアップによってブロックされます。
	bool          _IsMousePosValid(const ImVec2* mouse_pos = nullptr);                    //
	ImVec2        _GetMousePos();                                                      // ImGui::GetIO()へのショートカット。ユーザーが提供するMousePos。他の呼び出しと一貫性がある
	ImVec2        _GetMousePosOnOpeningCurrentPopup();                                 // 私たちはBeginPopup()を持ってポップアップを開く時にマウスの位置のバックアップを取得
	ImVec2        _GetMouseDragDelta(int button = 0, float lock_threshold = -1.0f);    // クリックしてからドラッグします。 lock_threshold <-1.0fがio.MouseDraggingThresholdを使用する場合
	void          _ResetMouseDragDelta(int button = 0);                                //
	ImGuiMouseCursor _GetMouseCursor();                                                // ImGui::NewFrame()でリセットしたいカーソルタイプを取得します。これはフレーム中に更新されます。 Render()の前に有効です。 io.MouseDrawCursorを設定してソフトウェアレンダリングを使用する場合、ImGuiはそれらをレンダリングします
	void          _SetMouseCursor(ImGuiMouseCursor type);                              // 希望のカーソルタイプを設定する
	void          _CaptureKeyboardFromApp(bool capture = true);                        // 手動でio.WantCaptureKeyboardフラグを次のフレームにオーバーライドします（このフラグはアプリケーションハンドルのために完全に残されています）。 例えば あなたのウィジェットがホバリングされているときに強制的にキャプチャキーボード。
	void          _CaptureMouseFromApp(bool capture = true);                           // 手動でio.WantCaptureMouseフラグを次のフレームにオーバーライドします（このフラグは、アプリケーションハンドルのために完全に残されています）。

	//==========================================================================
	//
	// ヘルパーは、メモリアロケータとクリップボード関数にアクセスする機能を持っています。
	//
	//==========================================================================

	void          _SetAllocatorFunctions(void* (*alloc_func)(size_t sz, void* user_data), void(*free_func)(void* ptr, void* user_data), void* user_data = nullptr);
	void* _MemAlloc(size_t size);
	void          _MemFree(void* ptr);
	const char* _GetClipboardText();
	void          _SetClipboardText(const char* text);

	/**
	@brief テキスト生成
	@param format [in] 入力文字列
	@param args [in] 表示させたい値
	@return string テキスト
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
float        Alpha ;                       //グローバルアルファはImGui
ImVec2       WindowPaddingのすべてに適用されます。              //ウィンドウ内のパディング
ImVec2       WindowMinSize ;               //最小ウィンドウサイズ
float        WindowRounding ;              //ウィンドウコーナーの丸めの半径。0.0fに設定すると、長方形のウィンドウが表示されます
。ImGuiAlign   WindowTitleAlign ;            //タイトルバーのテキストの整列
float        ChildWindowRounding ;         //子ウィンドウの四隅の丸めの半径。長方形のウィンドウを持つように0.0fに設定
ImVec2       フレームパッディング;                //フレーム化された矩形内の
余白（ほとんどのウィジェットで使用される）float        FrameRounding ;               //フレームコーナーの丸めの半径。ほとんどのウィジェットで使用される長方形のフレームを持つには、0.0fに設定します。
ImVec2       ItemSpacing ;                 //ウィジェット/ライン間の水平方向と垂直方向の間隔
ImVec2       ItemInnerSpacing ;            //合成されたウィジェットの要素内での水平方向と垂直方向の間隔（スライダとそのラベルなど）
ImVec2       TouchExtraPadding ;          //タッチ位置が正確ではないタッチベースのシステムのリアクションバウンディングボックスを拡張する。残念ながら、我々はウィジェットをソートしないので、オーバーラップの優先順位は常に最初のウィジェットに与えられます。だからこれをあまり大きくしないでください！
float        IndentSpacing ;               //例えば、ツリーノードに入るときの横インデント。一般的に==（FontSize + FramePadding.x * 2）。
float        ColumnsMinSpacing ;           // 2つの列の間の最小の水平スペーシング
float        ScrollbarSize ;               //垂直スクロールバーの幅、水平スクロールバーの高さ
float        ScrollbarRounding ;           //スクロールバーのグラブの角の半径
float        GrabMinSize ;                //スライダ/スクロールバーのグラブボックスの最小幅/高さ
float        GrabRounding ;                //グラブ角の丸めの半径。長方形のスライダーグラブを持つには0.0fに設定します。
ImVec2       DisplayWindowPadding ;        //ウィンドウの位置は、少なくともこの量だけ表示領域内に表示されるように固定されます。通常のウィンドウのみをカバーします。
ImVec2       DisplaySafeAreaPadding ;      //画面の端を見ることができない場合（例えばTVで）、安全領域のパディングを増やしてください。通常のウィンドウと同様にポップアップ/ツールチップをカバーします。
bool         AntiAliasedLines ;            //ライン/ボーダーでアンチエイリアスを有効にする。あなたが本当にCPU / GPUでタイトな場合は無効にしてください。
bool         AntiAliasedShapes;           //塗りつぶされた図形（丸い四角形、円など）でアンチエイリアスを有効にする
float        CurveTessellationTol ;        //テッセレーション許容値。高度にテッセレーションされたカーブ（高品質、多角形）を減らし、品質を低下させます。
ImVec4の      色[ ImGuiCol_COUNT ];

  ImGuiStyle （）;
};



// Cinder-ImGui
const  auto  opts  =  ui :: Options （）の例
です。antiAliasedLines （真）
。antiAliasedShapes （true ）
です。windowRounding （0.0 F ）
。frameRounding （0.0 f ）;

ui :: initialize （opts ）;


// https://github.com/ocornut/imgui/blob/v1.49/imgui.h#L592-L638
enum  ImGuiCol_
{
ImGuiCol_Text 、
ImGuiCol_TextDisabled 、
ImGuiCol_WindowBg 、              //通常のウィンドウの
背景ImGuiCol_ChildWindowBg 、         //子ウィンドウの背景
ImGuiCol_PopupBg 、               //ポップアップ、メニュー、ツールチップウィンドウの
背景ImGuiCol_Border 、
ImGuiCol_BorderShadow 、
ImGuiCol_FrameBg 、               //チェックボックス、ラジオボタン、プロット、スライダ、テキスト入力の
背景ImGuiCol_FrameBgHovered 、
ImGuiCol_FrameBgActive 、
ImGuiCol_TitleBg 、
ImGuiCol_TitleBgCollapsed 、
ImGuiCol_TitleBgActive 、
ImGuiCol_MenuBarBg 、
ImGuiCol_ScrollbarBg 、
ImGuiCol_ScrollbarGrab 、
ImGuiCol_ScrollbarGrabHovered 、
ImGuiCol_ScrollbarGrabActive 、
ImGuiCol_ComboBg 、
ImGuiCol_CheckMark 、
ImGuiCol_SliderGrab 、
ImGuiCol_SliderGrabActive 、
ImGuiCol_Button 、
ImGuiCol_ButtonHovered 、
ImGuiCol_ButtonActive 、
ImGuiCol_Header 、
ImGuiCol_HeaderHovered 、
ImGuiCol_HeaderActive 、
ImGuiCol_Column 、
ImGuiCol_ColumnHovered 、
ImGuiCol_ColumnActive 、
ImGuiCol_ResizeGrip 、
ImGuiCol_ResizeGripHovered 、
ImGuiCol_ResizeGripActive 、
ImGuiCol_CloseButton 、
ImGuiCol_CloseButtonHovered 、
ImGuiCol_CloseButtonActive 、
ImGuiCol_PlotLines 、
ImGuiCol_PlotLinesHovered 、
ImGuiCol_PlotHistogram 、
ImGuiCol_PlotHistogramHovered 、
ImGuiCol_TextSelectedBg 、
ImGuiCol_ModalWindowDarkening 、  //モーダルウィンドウがアクティブである場合、画面全体が暗く
ImGuiCol_COUNT
}。

*/