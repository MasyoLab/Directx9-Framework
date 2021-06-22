//==========================================================================
// Renderer [Renderer.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"
#include "Component.h"
#include "Activity.h"
#include "RenderState.h"

_MSLIB_BEGIN

namespace renderer
{
	// RendererID
	enum class RendererID : int
	{
		Begin = -1,
		Object, // �I�u�W�F�N�g
		Grid, // �O���b�h
		Field, // �t�B�[���h
		Cube, // �L���[�u
		Shadow, // �e
		Sphere, // ����
		Xmodel, // X���f��
		Mesh, // ���b�V��
		Billboard, // �r���{�[�h
		Effect, // �G�t�F�N�g
		Text, // �e�L�X�g
		End,
	};

	//==========================================================================
	//
	// class : Renderer
	// Content : �`��@�\
	//
	//==========================================================================
	class Renderer :
		virtual public activity::Activity,
		private render_state::RenderState
	{
	private:
		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) = delete;
	public:
		Renderer(RendererID id);
		virtual ~Renderer();

		/**
		@brief �`�惊�X�g����C�ɕ`��
		@param device [in] �f�o�C�X
		*/
		static void DrawAll(LPDIRECT3DDEVICE9 device);

		RendererID GetRendererID();
	protected:
		/**
		@brief �`��
		@param device [in] �f�o�C�X
		*/
		virtual void Draw(LPDIRECT3DDEVICE9 device);
	private:
		/**
		@brief �`��@�\��؂�ւ��܂�
		@param device [in] �f�o�C�X
		*/
		static void ChangeRender(LPDIRECT3DDEVICE9 device, RendererID id);
	private:
		RendererID m_renderer_id;
		static RendererID m_serect_renderer;
		static std::unordered_map<RendererID, std::list<Renderer*>> m_renderers; // �`��Ώۃ��X�g
	};

	using RendererReference = reference::IReference<Renderer>;
}

_MSLIB_END