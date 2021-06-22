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
	// Content : シェーダーを使った2D
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
		@param _bInOutFunctionFlag [in] 読み取り/書き込みを許可するフラグ
		*/
		Sprite(bool _bInOutFunctionFlag);
		virtual ~Sprite();

		/**
		@brief プライオリティの設定
		@param priority [in] プライオリティ
		*/
		void SetPriority(float priority);

		/**
		@brief プライオリティの取得
		*/
		float GetPriority();

		/**
		@brief UVの取得
		@return UV
		*/
		const floatUV& GetUV() const;

		/**
		@brief UVの登録
		@param uv [in] UV
		*/
		void SetUV(const floatUV& uv);

		/**
		@brief UVの登録
		@param Left [in] 左
		@param Top [in] 上
		@param Width [in] 幅
		@param Height [in] 高さ
		*/
		void SetUV(float Left, float Top, float Width, float Height);

		/**
		@brief UVの登録
		@param Left [in] 左
		@param Top [in] 上
		*/
		void SetUV_LT(float Left, float Top);

		/**
		@brief UVの登録
		@param Width [in] 幅
		@param Height [in] 高さ
		*/
		void SetUV_WH(float Width, float Height);

		/**
		@brief UVの加算
		@param uv [in] UV
		*/
		void AddUV(const floatUV& uv);

		/**
		@brief UVの加算
		@param Left [in] 左
		@param Top [in] 上
		@param Width [in] 幅
		@param Height [in] 高さ
		*/
		void AddUV(float Left, float Top, float Width, float Height);

		/**
		@brief UVの加算
		@param Left [in] 左
		@param Top [in] 上
		*/
		void AddUV_LT(float Left, float Top);

		/**
		@brief UVの加算
		@param Width [in] 幅
		@param Height [in] 高さ
		*/
		void AddUV_WH(float Width, float Height);

		/**
		@brief 色の取得
		@return 色
		*/
		const D3DXCOLOR& GetColor() const;

		/**
		@brief 色の登録(0.0f~1.0f)
		@param r [in] R値
		@param g [in] G値
		@param b [in] B値
		@param a [in] A値
		*/
		void SetColor(float r, float g, float b, float a);

		/**
		@brief 色の登録(0.0f~1.0f)
		@param color [in] 色
		*/
		void SetColor(const D3DXCOLOR& color);

		/**
		@brief 色の加算(0.0f~1.0f)
		@param r [in] R値
		@param g [in] G値
		@param b [in] B値
		@param a [in] A値
		*/
		void AddColor(float r, float g, float b, float a);

		/**
		@brief 色の加算(0.0f~1.0f)
		@param color [in] 色
		*/
		void AddColor(const D3DXCOLOR& color);

		/**
		@brief テクスチャの登録
		@param texture [in] テクスチャ
		*/
		void SetTextureData(const texture::TextureReference& _texture) override;

		/**
		@brief ソート処理
		*/
		static void Sort();

		/**
		@brief 描画の際に推奨されるウィンドウサイズを使う
		@param _flag [in] true で使用
		*/
		void SetDefaultWindowSizeModel(bool _flag);
	protected:
		/**
		@brief 更新
		*/
		virtual void Update() override;

		/**
		@brief 姿勢行列の更新
		*/
		virtual void UpdateMatrix() override;

		/**
		@brief 描画
		*/
		virtual void Draw(LPDIRECT3DDEVICE9 device, const D3DXMATRIX& _projection);

		/**
		@brief GUIに表示する機能
		*/
		virtual void GUISystem() override;

		/**
		@brief 読み取り機能
		*/
		virtual void InputDataFunction(std::ifstream& _ifstream) override;

		/**
		@brief 書き込み機能
		*/
		virtual void OutputDataFunction(std::ofstream& _ofstream) override;

		void GUISprite();
		void InputDataSprite(std::ifstream& _ifstream);
		void OutputDataSprite(std::ofstream& _ofstream);
	public:
		/**
		@brief スプライト描画機能の生成
		@param device [in] デバイス
		*/
		static void CreateRenderer(effect::EffectReference _default_effect, LPDIRECT3DDEVICE9 device);

		/**
		@brief 描画リストを一気に描画
		@param device [in] デバイス
		*/
		static void DrawAll(LPDIRECT3DDEVICE9 device);

		/**
		@brief スプライト描画機能の破棄
		*/
		static void DeleteRenderer();
	private:
		static LPDIRECT3DVERTEXBUFFER9 m_buffer; // 共通単位サイズ板ポリ頂点バッファ
		static LPDIRECT3DVERTEXDECLARATION9 m_declaration; // 共通頂点宣言
		static effect::EffectReference m_default_effect; // 共通エフェクト
		static std::list<Sprite*> m_sprites; // 描画対象リスト
		D3DXCOLOR m_color; // 色
		floatUV m_uv; // UV
		bool m_size_model;
	};

	//==========================================================================
	//
	// class : SpriteAnimation
	// Content : シェーダーを使った2Dアニメーション
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
		int m_count; // アニメーションカウンタ
		int m_frame; // 更新タイミング
		int m_pattern; // アニメーションのパターン数
		int m_direction; // 一行のアニメーション数
		bool m_loop; // ループ再生
		bool m_lock; // ロック
	};

	using SpriteReference = reference::IReference<Sprite>;
	using SpriteAnimationReference = reference::IReference<SpriteAnimation>;
}

_MSLIB_END