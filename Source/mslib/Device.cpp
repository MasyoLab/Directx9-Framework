//==========================================================================
// �f�o�C�X [Device.cpp]
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
		// Direct3D9�C���^�[�t�F�[�X�擾
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

		// ���݂̃f�B�X�v���C���[�h���擾����
		if (FAILED(m_lpd3d->GetAdapterDisplayMode(m_adapter, &m_d3dpm)))
			return true;

		// ����ރf�B�X�v���C���[�h���邩�𒲂ׂ�
		num = m_lpd3d->GetAdapterModeCount(m_adapter, m_d3dpm.Format);

		// �f�B�X�v���C���[�h�𒲂ׂ�
		for (int i = 0; i < num; i++)
		{
			// �f�B�X�v���C���[�h�̌���
			if (FAILED(m_lpd3d->EnumAdapterModes(m_adapter, m_d3dpm.Format, i, &d3dspMode)))
			{
				ErrorMessage("�f�B�X�v���C���[�h�̌����Ɏ��s���܂���");
				return true;
			}

			// �f�B�X�v���C���[�h���L��
			m_d3dsp_mode.emplace_back(d3dspMode);
		}

		// �ō��̃o�b�t�@��o�^
		m_d3dpm = m_d3dsp_mode[m_d3dsp_mode.size() - 1];

		if (_Mode == false)
		{
			m_d3dpm.Width = _Size.x;
			m_d3dpm.Height = _Size.y;
			m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
			m_d3dpp.Windowed = true; // �E�B���h�E���[�h
		}
		else if (_Mode == true)
		{
			//�t���X�N���[���̂Ƃ��A���t���b�V�����[�g��ς�����
			m_d3dpp.FullScreen_RefreshRateInHz = m_d3dpm.RefreshRate;
			m_d3dpp.Windowed = false; // �E�B���h�E���[�h
		}

		//�f�o�C�X�̃v���[���e�[�V�����p�����[�^(�f�o�C�X�̐ݒ�l)
		m_d3dpp.BackBufferWidth = m_d3dpm.Width;		//�o�b�N�o�b�t�@�̕�
		m_d3dpp.BackBufferHeight = m_d3dpm.Height;	//�o�b�N�o�b�t�@�̍���
		m_d3dpp.BackBufferFormat = m_d3dpm.Format;    //�o�b�N�o�b�t�@�t�H�[�}�b�g
		m_d3dpp.BackBufferCount = 1;					//�o�b�t�@�̐�
		m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		//�����H
		m_d3dpp.EnableAutoDepthStencil = true;			//3D�̕`��ɕK�v
		//m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	// 16Bit Z�o�b�t�@�쐬
		m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;	// 8Bit �X�e���V���V���h�E
		m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

		// �E�B���h�E�T�C�Y�m��
		m_windows_size = D3DXVECTOR2((float)m_d3dpm.Width, (float)m_d3dpm.Height);

		return false;
	}

	bool Device::CreateDevice()
	{
		// �f�o�C�X���e�[�u��
		struct DeviceTable {
			D3DDEVTYPE type;			// �f�o�C�X�̎��
			DWORD      behavior;		// �f�o�C�X�̓���
		};
		const DeviceTable device_table[] = {
			{ D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED }, // �n�[�h�E�F�A�V�F�[�_�[���g��
			{ D3DDEVTYPE_HAL, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED }, // HAL
			{ D3DDEVTYPE_REF, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED }, // REF
		};
		HRESULT	hr;

		//�f�o�C�X�I�u�W�F�N�g�𐶐�
		//[�f�o�C�X�쐬����]<�`��>��<���_����>
		for (auto i = 0; i < (sizeof(device_table) / sizeof(DeviceTable)); i++) {
			hr = m_lpd3d->CreateDevice(m_adapter, device_table[i].type, m_hwnd,
				device_table[i].behavior, &m_d3dpp, &m_lpd3ddevice);
			if (SUCCEEDED(hr))
				break;
		}

		if (FAILED(hr))
		{
			ErrorMessage("�f�o�C�X�̐����Ɏ��s���܂����B");
			return true;
		}

		// �r���[�|�[�g�̐ݒ�
		D3DVIEWPORT9 vp;
		vp.X = 0;
		vp.Y = 0;
		vp.Width = m_d3dpp.BackBufferWidth;
		vp.Height = m_d3dpp.BackBufferHeight;
		vp.MinZ = 0.0f;
		vp.MaxZ = 1.0f;

		if (FAILED(m_lpd3ddevice->SetViewport(&vp)))
		{
			ErrorMessage("�r���[�|�[�g�̐ݒ�Ɏ��s���܂����B");
			return true;
		}

		// �����_�[�X�e�[�g�̐ݒ�(���u�����h�̐ݒ�)
		m_lpd3ddevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // ���u�����h������
		m_lpd3ddevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); // ���\�[�X�J���[�̐ݒ�
		m_lpd3ddevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); // ��

		// �e�N�X�`�� �X�e�[�W �X�e�[�g�̐ݒ�
		m_lpd3ddevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE); // ����1�Ɠ���2���|�����킹��B
		m_lpd3ddevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE); // ����1�F�e�N�X�`��
		m_lpd3ddevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE); // ����2�F�f�B�t���[�Y(��{�F)
		
		m_lpd3ddevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		m_lpd3ddevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		m_lpd3ddevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		// ���_���Ƃ̐F
		m_lpd3ddevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
		m_lpd3ddevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
		m_lpd3ddevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
		m_lpd3ddevice->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);

		// �T���v���[�X�e�[�g�̐ݒ�(UV�l��ς���Ƒ�����悤�ɂȂ�)
		// WRAP...		��������
		// CLAMP...�@	�����L�΂�
		// MIRROR...�@	�����
		m_lpd3ddevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		m_lpd3ddevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		m_lpd3ddevice->SetSamplerState(0, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);

		// �t�B���^�����O
		m_lpd3ddevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); // �������Ȃ������ɔ��g
		m_lpd3ddevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); // ��ɔ��g
		m_lpd3ddevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR); // ���̃T�C�Y��菬�������Y��ɂ���

		m_lpd3ddevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); // �w�i���J�����O

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

		//Direct3D�ɂ��`��̊J�n
		if (SUCCEEDED(m_lpd3ddevice->BeginScene()))
			return true;
		return false;
	}

	HRESULT __stdcall Device::DrawEnd(const RECT* _SourceRect, const RECT* _DestRect, HWND _DestWindowOverride, const RGNDATA* _DirtyRegion)
	{
		//Direct3D�ɂ��`��̏I��
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