//==========================================================================
// Sprite [Sprite.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <list>

#include "mslib.hpp"
#include "mslib_struct.h"
#include "Activity.h"
#include "Texture.h"
#include "RectTransform.h"
#include "DrawTechnique.h"
#include "GameObject.h"
#include "InOutFunction.h"
#include "Effect.h"

_MSLIB_BEGIN

namespace object
{
	using namespace object;

	//==========================================================================
	//
	// class : Sprite
	// Content : �V�F�[�_�[���g����2D
	//
	//==========================================================================
	class Sprite :
		public object::GameObject,
		public transform::RectTransform,
		public texture::SetTexture,
		public effect::SetEffect,
		public draw_technique::DrawTechnique,
		public in_out_function::InOutFunction
	{
	private:
		Sprite(const Sprite&) = delete;
		Sprite(Sprite&&) = delete;
		Sprite& operator=(const Sprite&) = delete;
		Sprite& operator=(Sprite&&) = delete;
	public:
		Sprite();
		/**
		@param _bInOutFunctionFlag [in] �ǂݎ��/�������݂�������t���O
		*/
		Sprite(bool _bInOutFunctionFlag);
		virtual ~Sprite();

		/**
		@brief �v���C�I���e�B�̐ݒ�
		@param priority [in] �v���C�I���e�B
		*/
		void SetPriority(float priority);

		/**
		@brief �v���C�I���e�B�̎擾
		*/
		float GetPriority();

		/**
		@brief UV�̎擾
		@return UV
		*/
		const floatUV& GetUV() const;

		/**
		@brief UV�̓o�^
		@param uv [in] UV
		*/
		void SetUV(const floatUV& uv);

		/**
		@brief UV�̓o�^
		@param Left [in] ��
		@param Top [in] ��
		@param Width [in] ��
		@param Height [in] ����
		*/
		void SetUV(float Left, float Top, float Width, float Height);

		/**
		@brief UV�̓o�^
		@param Left [in] ��
		@param Top [in] ��
		*/
		void SetUV_LT(float Left, float Top);

		/**
		@brief UV�̓o�^
		@param Width [in] ��
		@param Height [in] ����
		*/
		void SetUV_WH(float Width, float Height);

		/**
		@brief UV�̉��Z
		@param uv [in] UV
		*/
		void AddUV(const floatUV& uv);

		/**
		@brief UV�̉��Z
		@param Left [in] ��
		@param Top [in] ��
		@param Width [in] ��
		@param Height [in] ����
		*/
		void AddUV(float Left, float Top, float Width, float Height);

		/**
		@brief UV�̉��Z
		@param Left [in] ��
		@param Top [in] ��
		*/
		void AddUV_LT(float Left, float Top);

		/**
		@brief UV�̉��Z
		@param Width [in] ��
		@param Height [in] ����
		*/
		void AddUV_WH(float Width, float Height);

		/**
		@brief �F�̎擾
		@return �F
		*/
		const D3DXCOLOR& GetColor() const;

		/**
		@brief �F�̓o�^(0.0f~1.0f)
		@param r [in] R�l
		@param g [in] G�l
		@param b [in] B�l
		@param a [in] A�l
		*/
		void SetColor(float r, float g, float b, float a);

		/**
		@brief �F�̓o�^(0.0f~1.0f)
		@param color [in] �F
		*/
		void SetColor(const D3DXCOLOR& color);

		/**
		@brief �F�̉��Z(0.0f~1.0f)
		@param r [in] R�l
		@param g [in] G�l
		@param b [in] B�l
		@param a [in] A�l
		*/
		void AddColor(float r, float g, float b, float a);

		/**
		@brief �F�̉��Z(0.0f~1.0f)
		@param color [in] �F
		*/
		void AddColor(const D3DXCOLOR& color);

		/**
		@brief �e�N�X�`���̓o�^
		@param texture [in] �e�N�X�`��
		*/
		void SetTextureData(const texture::TextureReference& _texture) override;

		/**
		@brief �\�[�g����
		*/
		static void Sort();

		/**
		@brief �`��̍ۂɐ��������E�B���h�E�T�C�Y���g��
		@param _flag [in] true �Ŏg�p
		*/
		void SetDefaultWindowSizeModel(bool _flag);
	protected:
		/**
		@brief �X�V
		*/
		virtual void Update() override;

		/**
		@brief �p���s��̍X�V
		*/
		virtual void UpdateMatrix() override;

		/**
		@brief �`��
		*/
		virtual void Draw(LPDIRECT3DDEVICE9 device, const D3DXMATRIX& _projection);

		/**
		@brief GUI�ɕ\������@�\
		*/
		virtual void GUISystem() override;

		/**
		@brief �ǂݎ��@�\
		*/
		virtual void InputDataFunction(std::ifstream& _ifstream) override;

		/**
		@brief �������݋@�\
		*/
		virtual void OutputDataFunction(std::ofstream& _ofstream) override;

		void GUISprite();
		void InputDataSprite(std::ifstream& _ifstream);
		void OutputDataSprite(std::ofstream& _ofstream);
	public:
		/**
		@brief �X�v���C�g�`��@�\�̐���
		@param device [in] �f�o�C�X
		*/
		static void CreateRenderer(effect::EffectReference _default_effect, LPDIRECT3DDEVICE9 device);

		/**
		@brief �`�惊�X�g����C�ɕ`��
		@param device [in] �f�o�C�X
		*/
		static void DrawAll(LPDIRECT3DDEVICE9 device);

		/**
		@brief �X�v���C�g�`��@�\�̔j��
		*/
		static void DeleteRenderer();
	private:
		static LPDIRECT3DVERTEXBUFFER9 m_buffer; // ���ʒP�ʃT�C�Y�|�����_�o�b�t�@
		static LPDIRECT3DVERTEXDECLARATION9 m_declaration; // ���ʒ��_�錾
		static effect::EffectReference m_default_effect; // ���ʃG�t�F�N�g
		static std::list<Sprite*> m_sprites; // �`��Ώۃ��X�g
		D3DXCOLOR m_color; // �F
		floatUV m_uv; // UV
		bool m_size_model;
	};

	//==========================================================================
	//
	// class : SpriteAnimation
	// Content : �V�F�[�_�[���g����2D�A�j���[�V����
	//
	//==========================================================================
	class SpriteAnimation :
		public Sprite
	{
	public:
		SpriteAnimation();
		~SpriteAnimation();
		void PlayAnimation(bool loop);
		void StopAnimation();
		void SetAnimationData(int count, int frame, int pattern, int direction);
		void AddAnimationCounter(int count);
	protected:
		int m_count; // �A�j���[�V�����J�E���^
		int m_frame; // �X�V�^�C�~���O
		int m_pattern; // �A�j���[�V�����̃p�^�[����
		int m_direction; // ��s�̃A�j���[�V������
		bool m_loop; // ���[�v�Đ�
		bool m_lock; // ���b�N
	};

	using SpriteReference = reference::IReference<Sprite>;
	using SpriteAnimationReference = reference::IReference<SpriteAnimation>;
}

_MSLIB_END