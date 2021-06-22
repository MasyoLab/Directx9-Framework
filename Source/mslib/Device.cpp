//==========================================================================
// デバイス [Device.cpp]
// author : MasyoLab
//==========================================================================
#include "Device.h"

_MSLIB_BEGIN

namespace device
{
	Device::Device() : Component("Device"), m_lpd3d(nullptr), m_lpd3ddevice(nullptr), m_hwnd(nullptr), m_adapter(D3DADAPTER_DEFAULT),
		m_windows_size(0, 0), m_default_windows_size(1920, 1080)
	{
	}

	Device::~Device()
	{
		Release();
	}

	void Device::Init()
	{
		// Direct3D9インターフェース取得
		if (m_lpd3d == nullptr)
			m_lpd3d = Direct3DCreate9(D3D_SDK_VERSION);
	}

	void Device::Release()
	{
		DestroyComponent();
		if (m_lpd3ddevice != nullptr)
			m_lpd3ddevice->Release();
		if (m_lpd3d != nullptr)
			m_lpd3d->Release();
		m_lpd3ddevice = nullptr;
		m_lpd3d = nullptr;
		m_d3dsp_mode.clear();
	}

	bool Device::CreateWindowMode(const int2& _Size, bool _Mode)
	{
		D3DDISPLAYMODE d3dspMode;
		int nCount = 0;
		int num = 0;

		ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));

		// 現在のディスプレイモードを取得する
		if (FAILED(m_lpd3d->GetAdapterDisplayMode(m_adapter, &m_d3dpm)))
			return true;

		// 何種類ディスプレイモードあるかを調べる
		num = m_lpd3d->GetAdapterModeCount(m_adapter, m_d3dpm.Format);

		// ディスプレイモードを調べる
		for (int i = 0; i < num; i++)
		{
			// ディスプレイモードの検索
			if (FAILED(m_lpd3d->EnumAdapterModes(m_adapter, m_d3dpm.Format, i, &d3dspMode)))
			{
				ErrorMessage("ディスプレイモードの検索に失敗しました");
				return true;
			}

			// ディスプレイモードを記憶
			m_d3dsp_mode.emplace_back(d3dspMode);
		}

		// 最高のバッファを登録
		m_d3dpm = m_d3dsp_mode[m_d3dsp_mode.size() - 1];

		if (_Mode == false)
		{
			m_d3dpm.Width = _Size.x;
			m_d3dpm.Height = _Size.y;
			m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
			m_d3dpp.Windowed = true; // ウィンドウモード
		}
		else if (_Mode == true)
		{
			//フルスクリーンのとき、リフレッシュレートを変えられる
			m_d3dpp.FullScreen_RefreshRateInHz = m_d3dpm.RefreshRate;
			m_d3dpp.Windowed = false; // ウィンドウモード
		}

		//デバイスのプレゼンテーションパラメータ(デバイスの設定値)
		m_d3dpp.BackBufferWidth = m_d3dpm.Width;		//バックバッファの幅
		m_d3dpp.BackBufferHeight = m_d3dpm.Height;	//バックバッファの高さ
		m_d3dpp.BackBufferFormat = m_d3dpm.Format;    //バックバッファフォーマット
		m_d3dpp.BackBufferCount = 1;					//バッファの数
		m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		//垂直？
		m_d3dpp.EnableAutoDepthStencil = true;			//3Dの描画に必要
		//m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	// 16Bit Zバッファ作成
		m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;	// 8Bit ステンシルシャドウ
		m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

		// ウィンドウサイズ確定
		m_windows_size = D3DXVECTOR2((float)m_d3dpm.Width, (float)m_d3dpm.Height);

		return false;
	}

	bool Device::CreateDevice()
	{
		// デバイス情報テーブル
		struct DeviceTable {
			D3DDEVTYPE type;			// デバイスの種類
			DWORD      behavior;		// デバイスの動作
		};
		const DeviceTable device_table[] = {
			{ D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED }, // ハードウェアシェーダーを使う
			{ D3DDEVTYPE_HAL, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED }, // HAL
			{ D3DDEVTYPE_REF, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED }, // REF
		};
		HRESULT	hr;

		//デバイスオブジェクトを生成
		//[デバイス作成制御]<描画>と<頂点処理>
		for (auto i = 0; i < (sizeof(device_table) / sizeof(DeviceTable)); i++) {
			hr = m_lpd3d->CreateDevice(m_adapter, device_table[i].type, m_hwnd,
				device_table[i].behavior, &m_d3dpp, &m_lpd3ddevice);
			if (SUCCEEDED(hr))
				break;
		}

		if (FAILED(hr))
		{
			ErrorMessage("デバイスの生成に失敗しました。");
			return true;
		}

		// ビューポートの設定
		D3DVIEWPORT9 vp;
		vp.X = 0;
		vp.Y = 0;
		vp.Width = m_d3dpp.BackBufferWidth;
		vp.Height = m_d3dpp.BackBufferHeight;
		vp.MinZ = 0.0f;
		vp.MaxZ = 1.0f;

		if (FAILED(m_lpd3ddevice->SetViewport(&vp)))
		{
			ErrorMessage("ビューポートの設定に失敗しました。");
			return true;
		}

		// レンダーステートの設定(αブレンドの設定)
		m_lpd3ddevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // αブレンドを許可
		m_lpd3ddevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); // αソースカラーの設定
		m_lpd3ddevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); // α

		// テクスチャ ステージ ステートの設定
		m_lpd3ddevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE); // 入力1と入力2を掛け合わせる。
		m_lpd3ddevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE); // 入力1：テクスチャ
		m_lpd3ddevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE); // 入力2：ディフューズ(基本色)
		
		m_lpd3ddevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		m_lpd3ddevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		m_lpd3ddevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		// 頂点ごとの色
		m_lpd3ddevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
		m_lpd3ddevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
		m_lpd3ddevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
		m_lpd3ddevice->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);

		// サンプラーステートの設定(UV値を変えると増えるようになる)
		// WRAP...		反復する
		// CLAMP...　	引き伸ばす
		// MIRROR...　	鏡状態
		m_lpd3ddevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		m_lpd3ddevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		m_lpd3ddevice->SetSamplerState(0, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);

		// フィルタリング
		m_lpd3ddevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); // 小さくなった時に白枠
		m_lpd3ddevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); // 常に白枠
		m_lpd3ddevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR); // 元のサイズより小さい時綺麗にする

		m_lpd3ddevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); // 背景をカリング

		return false;
	}

	LPDIRECT3DDEVICE9 Device::Getd3ddevice() const
	{
		return m_lpd3ddevice;
	}

	D3DPRESENT_PARAMETERS& Device::Getd3dpp()
	{
		return m_d3dpp;
	}

	const D3DXVECTOR2& Device::GetWindowsSize() const
	{
		return m_windows_size;
	}

	const D3DXVECTOR2& Device::GetDefaultWindowsSize() const
	{
		return m_default_windows_size;
	}

	void Device::SetHwnd(HWND _hWnd)
	{
		m_hwnd = _hWnd;
	}

	HWND Device::GetHwnd() const
	{
		return m_hwnd;
	}

	bool Device::DrawBegin()
	{
		//m_lpd3ddevice->Clear(0, nullptr, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(50, 50, 50, 255), 1.0f, 0);
		m_lpd3ddevice->Clear(0, nullptr, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), D3DCOLOR_RGBA(50, 50, 50, 255), 1.0f, 0);

		//Direct3Dによる描画の開始
		if (SUCCEEDED(m_lpd3ddevice->BeginScene()))
			return true;
		return false;
	}

	HRESULT __stdcall Device::DrawEnd(const RECT* _SourceRect, const RECT* _DestRect, HWND _DestWindowOverride, const RGNDATA* _DirtyRegion)
	{
		//Direct3Dによる描画の終了
		m_lpd3ddevice->EndScene();
		HRESULT hre = m_lpd3ddevice->Present(_SourceRect, _DestRect, _DestWindowOverride, _DirtyRegion);
		if (FAILED(hre))
			m_lpd3ddevice->Reset(&m_d3dpp);
		return hre;
	}

	HRESULT __stdcall Device::DrawEnd()
	{
		return DrawEnd(nullptr, nullptr, nullptr, nullptr);
	}
}

_MSLIB_END