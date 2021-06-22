//==========================================================================
// Sprite [Sprite.cpp]
// author : MasyoLab
//==========================================================================
#include "Sprite.h"
#include "MsImGui.h"

_MSLIB_BEGIN

namespace object
{
	LPDIRECT3DVERTEXBUFFER9 Sprite::m_buffer; // ���ʒP�ʃT�C�Y�|�����_�o�b�t�@
	LPDIRECT3DVERTEXDECLARATION9 Sprite::m_declaration; // ���ʒ��_�錾
	effect::EffectReference Sprite::m_default_effect; // ���ʃG�t�F�N�g
	std::list<Sprite*> Sprite::m_sprites; // Sprite

	Sprite::Sprite() :
		m_uv(0.0f, 0.0f, 1.0f, 1.0f), m_color(1.0f, 1.0f, 1.0f, 1.0f), m_size_model(true)
	{
		SetComponentName("Sprite");
		SetActivity(true);
		m_effect_data = m_default_effect;
		m_sprites.push_back(this);
	}
	Sprite::Sprite(bool _bInOutFunctionFlag) :
		m_uv(0.0f, 0.0f, 1.0f, 1.0f), m_color(1.0f, 1.0f, 1.0f, 1.0f), m_size_model(true), InOutFunction(_bInOutFunctionFlag)
	{
		SetComponentName("Sprite");
		SetActivity(true);
		m_effect_data = m_default_effect;
		m_sprites.push_back(this);
	}
	Sprite::~Sprite()
	{
		auto itr = std::find(m_sprites.begin(), m_sprites.end(), this);
		if (itr != m_sprites.end())
			m_sprites.erase(itr);
	}
	void Sprite::SetPriority(float priority)
	{
		GetParameter().position.z = priority;
	}
	float Sprite::GetPriority()
	{
		return GetParameter().position.z;
	}
	const floatUV& Sprite::GetUV() const
	{
		return m_uv;
	}
	void Sprite::SetUV(const floatUV& uv)
	{
		m_uv = uv;
	}
	void Sprite::SetUV(float Left, float Top, float Width, float Height)
	{
		m_uv = floatUV(Left, Top, Width, Height);
	}
	void Sprite::SetUV_LT(float Left, float Top)
	{
		m_uv = floatUV(Left, Top, 0.0f, 0.0f);
	}
	void Sprite::SetUV_WH(float Width, float Height)
	{
		m_uv = floatUV(0.0f, 0.0f, Width, Height);
	}
	void Sprite::AddUV(const floatUV& uv)
	{
		m_uv += uv;
	}
	void Sprite::AddUV(float Left, float Top, float Width, float Height)
	{
		m_uv += floatUV(Left, Top, Width, Height);
	}
	void Sprite::AddUV_LT(float Left, float Top)
	{
		m_uv += floatUV(Left, Top, 0.0f, 0.0f);
	}
	void Sprite::AddUV_WH(float Width, float Height)
	{
		m_uv += floatUV(0.0f, 0.0f, Width, Height);
	}
	const D3DXCOLOR& Sprite::GetColor() const
	{
		return m_color;
	}
	void Sprite::SetColor(float r, float g, float b, float a)
	{
		m_color = D3DXCOLOR(r, g, b, a);
	}
	void Sprite::SetColor(const D3DXCOLOR& color)
	{
		m_color = color;
	}
	void Sprite::AddColor(float r, float g, float b, float a)
	{
		m_color += D3DXCOLOR(r, g, b, a);
	}
	void Sprite::AddColor(const D3DXCOLOR& color)
	{
		m_color += color;
	}
	void Sprite::SetTextureData(const texture::TextureReference& _texture)
	{
		m_texture_data = _texture;
		auto& info = _texture->GetImageInfo();
		SetPolygonSize((float)info.Width, (float)info.Height);
	}
	void Sprite::Sort()
	{
		m_sprites.sort([&](Sprite* a, Sprite* b) {
			return a->GetPriority() < b->GetPriority() ? true : false;
			});
	}
	void Sprite::SetDefaultWindowSizeModel(bool _flag)
	{
		m_size_model = _flag;
	}
	void Sprite::Update()
	{
	}
	void Sprite::UpdateMatrix()
	{
		switch (GetMatrixType())
		{
		case MatrixType::Default:
			CreateWorldMatrix();
			break;
		case MatrixType::World:
			CreateWorldMatrix();
			break;
		case MatrixType::Local:
			CreateLocalMatrix();
			break;
		default:
			CreateWorldMatrix();
			break;
		}
	}
	void Sprite::Draw(LPDIRECT3DDEVICE9 device, const D3DXMATRIX& _projection)
	{
		if (!m_effect_data.check())
			return;

		// �V�F�[�_�J�n
		UINT numPass = 0;
		auto effect = m_effect_data->GetEffect();
		effect->SetTechnique("MainShader2D");
		effect->Begin(&numPass, 0);
		effect->BeginPass(0);

		// �Ă΂ꂽ��X�V�̖�����
		SetUpdateKey(false);

		if (GetAdditiveSynthesis())
		{
			TechniqueZwriteenableStart(device);
			TechniqueSub(device);
		}

		auto v4color = D3DXVECTOR4(m_color.r, m_color.g, m_color.b, m_color.a);

		effect->SetMatrix("World", &m_world_matrix);
		effect->SetMatrix("Projection", &_projection);
		effect->SetFloat("uvLeft", m_uv.u0);
		effect->SetFloat("uvTop", m_uv.v0);
		effect->SetFloat("uvWidth", m_uv.u1);
		effect->SetFloat("uvHeight", m_uv.v1);
		effect->SetVector("Color", &v4color);

		if (m_texture_data.check())
		{
			effect->SetTexture("Texture", m_texture_data->GetTexture());
			if (m_texture_data->GetTexture() != nullptr)
				effect->SetFloat("TexFlag", true);
			else if (m_texture_data->GetTexture() == nullptr)
				effect->SetFloat("TexFlag", false);
		}
		else
		{
			effect->SetFloat("TexFlag", false);
		}

		effect->CommitChanges();

		device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		if (GetAdditiveSynthesis())
		{
			TechniqueZwriteenableEnd(device);
			TechniqueAdd(device);
		}

		effect->EndPass();
		effect->End();
	}
	void Sprite::GUISystem()
	{
		GUIGameObject();
		GUITransform();
		GUIRectTransform();
		GUISprite();
		GUITexture();
	}
	void Sprite::InputDataFunction(std::ifstream& _ifstream)
	{
		InputDataTransform(_ifstream);
		InputDataRectTransform(_ifstream);
		InputDataSprite(_ifstream);
	}
	void Sprite::OutputDataFunction(std::ofstream& _ofstream)
	{
		OutputDataTransform(_ofstream);
		OutputDataRectTransform(_ofstream);
		OutputDataSprite(_ofstream);
	}
	void Sprite::GUISprite()
	{
#if defined(_MSLIB_DEBUG)
		if (!imgui::NewTreeNode("Sprite", false))
			return;

		if (imgui::Button("�\�[�g"))
			Sort();

		if (imgui::NewTreeNode("Color Pallet", false))
		{
			imgui::Separator();
			m_color = imgui::ColorEdit(m_color);
			imgui::EndTreeNode();
		}
		imgui::Separator();
		imgui::EndTreeNode();
#endif
	}
	void Sprite::InputDataSprite(std::ifstream& _ifstream)
	{
		std::vector<float> i_color;
		std::string line_str;
		float ftemp;

		// �J�n�ʒu��
		_ifstream.clear();
		_ifstream.seekg(0, std::ios_base::beg);

		// �񂲂Ƃ̓ǂݎ��
		while (std::getline(_ifstream, line_str))
		{
			// #�̓R�����g
			if (line_str[0] == '#')
				continue;
			// ���͖���
			if (line_str.find('=') == std::string::npos)
				continue;

			std::stringstream ss_str(line_str);
			std::string name_str;

			ss_str >> name_str;
			ss_str.ignore(line_str.size(), '=');

			if (name_str == "Sprite_Color")
				while (ss_str >> ftemp)
					i_color.push_back(ftemp);
		}

		if ((int)i_color.size() == 0)
			return;

		SetColor(i_color[0], i_color[1], i_color[2], i_color[3]);
	}
	void Sprite::OutputDataSprite(std::ofstream& _ofstream)
	{
		auto& c4 = m_color;
		auto col_str = std::string("Sprite_Color =") + " " + std::to_string(c4.r) + " " + std::to_string(c4.g) + " " + std::to_string(c4.b) + " " + std::to_string(c4.a);

		_ofstream << std::string("#Set Sprite_Color") << std::endl;
		_ofstream << col_str << std::endl;
	}
	void Sprite::CreateRenderer(effect::EffectReference _default_effect, LPDIRECT3DDEVICE9 device)
	{
		// �o�b�t�@�����݂��Ȃ��Ƃ�
		if (m_buffer == nullptr)
		{
			// �e���v���[�g�o�[�e�b�N�X�̐錾
			float commonVtx[] = {
				0.0f, 0.0f, 0.0f,   0.0f, 0.0f,  // 0
				1.0f, 0.0f, 0.0f,   1.0f, 0.0f,  // 1
				0.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // 2
				1.0f, 1.0f, 0.0f,   1.0f, 1.0f,  // 3
			};

			// ��b�o�b�t�@�𐶐�
			device->CreateVertexBuffer(sizeof(commonVtx), 0, 0, D3DPOOL_MANAGED, &m_buffer, nullptr);

			// �o�b�t�@�����݂���ۂɁA�o�b�t�@�����Ƀe���v���[�g�o�[�e�b�N�X��o�^���܂�
			if (m_buffer != nullptr)
			{
				float* p = nullptr;
				m_buffer->Lock(0, 0, (void**)& p, 0);
				memcpy(p, commonVtx, sizeof(commonVtx));
				m_buffer->Unlock();
			}
		}

		// �V�F�[�_�[�̓o�^
		m_default_effect = _default_effect;

		// ���_�錾�쐬
		if (m_declaration == nullptr)
		{
			D3DVERTEXELEMENT9 elems[] = {
				{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
				{0, sizeof(float) * 3, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
				D3DDECL_END()
			};
			device->CreateVertexDeclaration(elems, &m_declaration);
		}
	}
	void Sprite::DeleteRenderer()
	{
		if (m_buffer != nullptr)
			m_buffer->Release();
		if (m_declaration != nullptr)
			m_declaration->Release();
		m_buffer = nullptr;
		m_declaration = nullptr;
		m_default_effect.clear();
		m_sprites.clear();
	}

	void Sprite::DrawAll(LPDIRECT3DDEVICE9 device)
	{
		if (m_buffer == nullptr || m_declaration == nullptr)
			return;	// �`��s��

		// �`��@�\��ύX
		device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); // �������Ȃ������ɔ��g
		device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); // ��ɔ��g
		device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE); // ���̃T�C�Y��菬�������Y��ɂ���
		device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); // �w�i���J�����O���Ȃ�

		D3DXVECTOR2 float2x2[2] =
		{
			D3DXVECTOR2(2.0f / GetDevice()->GetDefaultWindowsSize().x,-2.0f / GetDevice()->GetDefaultWindowsSize().y),
			D3DXVECTOR2(2.0f / GetDevice()->GetWindowsSize().x,-2.0f / GetDevice()->GetWindowsSize().y)
		};

		// 2D�`��p�ˉe�ϊ��s��
		D3DXMATRIX proj;
		D3DXMatrixIdentity(&proj);
		proj._41 = -1.0f;
		proj._42 = 1.0f;

		// ���_�o�b�t�@�E���_�錾�ݒ�
		device->SetStreamSource(0, m_buffer, 0, sizeof(float) * 5);
		device->SetVertexDeclaration(m_declaration);

		// �`�惊�X�g�ɓo�^����Ă���X�v���C�g����C�ɕ`�悷��
		for (auto& itr : m_sprites)
		{
			if (!itr->GetActivity())
				continue;

			if (itr->m_size_model)
			{
				proj._11 = float2x2[0].x;
				proj._22 = float2x2[0].y;
			}
			else
			{
				proj._11 = float2x2[1].x;
				proj._22 = float2x2[1].y;
			}

			itr->Draw(device, proj);
		}

		// �`��@�\��ύX
		device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); // �������Ȃ������ɔ��g
		device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); // ��ɔ��g
		device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR); // ���̃T�C�Y��菬�������Y��ɂ���
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); // �w�i���J�����O
		device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	}
	SpriteAnimation::SpriteAnimation() :
		m_count(0), m_frame(0), m_pattern(0), m_direction(0), m_loop(false), m_lock(false)
	{
		SetComponentName("SpriteAnimation");
	}
	SpriteAnimation::~SpriteAnimation()
	{
	}
	void SpriteAnimation::PlayAnimation(bool loop)
	{
		m_loop = loop;
		m_lock = true;
	}
	void SpriteAnimation::StopAnimation()
	{
		m_lock = false;
	}
	void SpriteAnimation::SetAnimationData(int count, int frame, int pattern, int direction)
	{
		m_count = count;
		m_frame = frame;
		m_pattern = pattern;
		m_direction = direction;

		int nCount = 0;
		auto fuv = GetUV();

		// �c�̖���������
		for (int i = 0;; i += m_direction)
		{
			if (m_pattern <= i)
				break;
			nCount++;
		}

		fuv.u1 = 1.f / m_direction;
		fuv.v1 = 1.f / nCount;
		SetUV(fuv);

		auto& info = m_texture_data->GetImageInfo();

		SetPolygonSize(info.Width * fuv.u1, info.Height * fuv.v1);
		SetPivot(GetPolygonSize() / 2.0f);
	}
	void SpriteAnimation::AddAnimationCounter(int count)
	{
		if (!m_lock)
			return;

		m_count += count;

		if ((m_frame * m_pattern) <= m_count)
		{
			m_count = 0;
			if (!m_loop)
				m_lock = false;
		}

		int PattanNum = (m_count / m_frame) % m_pattern; // �t���[����1��	�p�^�[����
		int patternV = PattanNum % m_direction; // �������̃p�^�[��
		int patternH = PattanNum / m_direction; // �c�����̃p�^�[��
		auto fuv = GetUV();

		fuv.u0 = patternV * fuv.u1;
		fuv.v0 = patternH * fuv.v1;
		SetUV(fuv);
	}
}

_MSLIB_END