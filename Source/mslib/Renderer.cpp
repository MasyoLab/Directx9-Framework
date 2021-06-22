//==========================================================================
// Renderer [Renderer.h]
// author : MasyoLab
//==========================================================================
#include "Renderer.h"
#include "EffekseerDX.h"
#include "Debug.h"

_MSLIB_BEGIN

namespace renderer
{
	std::unordered_map<RendererID, std::list<Renderer*>> Renderer::m_renderers; // �`��Ώۃ��X�g
	RendererID Renderer::m_serect_renderer = RendererID::Begin;

	Renderer::Renderer(RendererID id) :
		m_renderer_id(id)
	{
		auto itr1 = m_renderers.find(id);
		if (itr1 != m_renderers.end())
		{
			itr1->second.push_back(this);
			return;
		}

		// �ȉ��A�Ǘ��̈悪�Ȃ��ꍇ
		m_renderers[id].push_back(this);

		// �\�[�g���s���܂�
		std::map<RendererID, std::list<Renderer*>> ordered(m_renderers.begin(), m_renderers.end());

		// ��������ɁA�\�[�g�ς݃f�[�^�𕡐����܂�
		m_renderers.clear();
		for (auto& itr2 : ordered)
			m_renderers[itr2.first] = itr2.second;
	}

	Renderer::~Renderer()
	{
		auto itr_render = m_renderers.find(m_renderer_id);
		if (itr_render != m_renderers.end())
		{
			auto itr = std::find(itr_render->second.begin(), itr_render->second.end(), this);
			if (itr != itr_render->second.end())
				itr_render->second.erase(itr);
		}
	}

	void Renderer::DrawAll(LPDIRECT3DDEVICE9 device)
	{
		for (auto& itr1 : m_renderers)
		{
			ChangeRender(device, itr1.first);
			for (auto& itr2 : itr1.second)
				if (itr2->GetActivity())
					itr2->Draw(device);
		}

		// �㏈��
		ChangeRender(device, RendererID::Effect);
		effekseer_dx::Renderer::DrawAll();
		ChangeRender(device, RendererID::End);
		debug::Debug::DrawAll(device);
	}

	RendererID Renderer::GetRendererID()
	{
		return m_renderer_id;
	}

	void Renderer::Draw(LPDIRECT3DDEVICE9 device)
	{
		device;
	}

	void Renderer::ChangeRender(LPDIRECT3DDEVICE9 device, RendererID id)
	{
		if (m_serect_renderer != id)
		{
			switch (m_serect_renderer)
			{
			case RendererID::Begin:
				break;
			case RendererID::Grid:
				break;
			case RendererID::Field:
				break;
			case RendererID::Cube:
				break;
			case RendererID::Mesh:
				SetRenderALPHAREF_END(device);
				break;
			case RendererID::Shadow:
				SetRenderADD(device);
				break;
			case RendererID::Sphere:
				SetRenderALPHAREF_END(device);
				device->SetRenderState(D3DRS_WRAP0, 0);
				device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); // �J�����O���܂�
				break;
			case RendererID::Xmodel:
				break;
			case RendererID::Billboard:
				// �p���`�����I��
				device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); // �J�����O���܂�
				SetRenderALPHAREF_END(device);
				break;
			case RendererID::Effect:
				device->SetRenderState(D3DRS_LIGHTING, D3DZB_TRUE);
				device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); // �J�����O���܂�
				break;
			case RendererID::Text:
				break;
			case RendererID::End:
				break;
			default:
				break;
			}
			switch (id)
			{
			case RendererID::Begin:
				break;
			case RendererID::Grid:
				device->SetRenderState(D3DRS_LIGHTING, D3DZB_FALSE);
				break;
			case RendererID::Field:
				device->SetRenderState(D3DRS_LIGHTING, D3DZB_TRUE);
				break;
			case RendererID::Cube:
				device->SetRenderState(D3DRS_LIGHTING, D3DZB_TRUE);
				break;
			case RendererID::Mesh:
				device->SetRenderState(D3DRS_LIGHTING, D3DZB_TRUE); // ���C�g�ݒ�
				// �A���t�@�摜�ɂ��u�����h
				SetRenderALPHAREF_START(device, 100);
				break;
			case RendererID::Shadow:
				device->SetRenderState(D3DRS_LIGHTING, D3DZB_TRUE);
				// ���Z����
				SetRenderREVSUBTRACT(device);
				break;
			case RendererID::Sphere:
				device->SetRenderState(D3DRS_LIGHTING, D3DZB_TRUE);
				SetRenderALPHAREF_START(device, 100);
				device->SetRenderState(D3DRS_WRAP0, D3DWRAPCOORD_0);
				device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW); // �����v���̖ʂ�����
				break;
			case RendererID::Xmodel:
				device->SetRenderState(D3DRS_LIGHTING, D3DZB_TRUE);
				break;
			case RendererID::Billboard:
				device->SetRenderState(D3DRS_LIGHTING, D3DZB_TRUE);
				device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); // �J�����O���܂���

				// �p���`����
				SetRenderALPHAREF_START(device, 100);
				break;
			case RendererID::Effect:
				device->SetRenderState(D3DRS_LIGHTING, D3DZB_FALSE);
				device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW); // �J�����O���܂���
				break;
			case RendererID::Text:
				device->SetRenderState(D3DRS_LIGHTING, D3DZB_FALSE);
				break;
			case RendererID::End:
				device->SetRenderState(D3DRS_LIGHTING, D3DZB_FALSE);
				break;
			default:
				break;
			}
			m_serect_renderer = id;
		}
	}
}

_MSLIB_END