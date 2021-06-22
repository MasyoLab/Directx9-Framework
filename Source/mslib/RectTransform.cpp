//==========================================================================
// RectTransform [RectTransform.cpp]
// author : MasyoLab
//==========================================================================
#include "RectTransform.h"
#include "MsImGui.h"

_MSLIB_BEGIN

namespace transform
{
	RectTransform::RectTransform() :
		m_polygon(128.0f, 128.0f), m_pivot(0.5, 0.5)
	{
		SetComponentName("RectTransform");
		D3DXMatrixIdentity(&m_not_polygon_matrix);
	}
	RectTransform::~RectTransform()
	{
	}
	const D3DXVECTOR2& RectTransform::GetPolygonSize() const
	{
		return m_polygon;
	}
	void RectTransform::SetPolygonSize(float x, float y)
	{
		m_polygon = D3DXVECTOR2(x, y);
		SetUpdateKey(true);
	}
	void RectTransform::SetPolygonSize(const D3DXVECTOR2& _size)
	{
		m_polygon = _size;
		SetUpdateKey(true);
	}
	void RectTransform::AddPolygonSize(float x, float y)
	{
		m_polygon += D3DXVECTOR2(x, y);
		SetUpdateKey(true);
	}
	void RectTransform::AddPolygonSize(const D3DXVECTOR2& _size)
	{
		m_polygon += _size;
		SetUpdateKey(true);
	}
	const D3DXVECTOR2& RectTransform::GetPivot() const
	{
		return m_pivot;
	}
	void RectTransform::SetPivot(float x, float y)
	{
		m_pivot = D3DXVECTOR2(x, y);
		SetUpdateKey(true);
	}
	void RectTransform::SetPivot(const D3DXVECTOR2& _pivot)
	{
		m_pivot = _pivot;
		SetUpdateKey(true);
	}
	void RectTransform::AddPivot(float x, float y)
	{
		m_pivot += D3DXVECTOR2(x, y);
		SetUpdateKey(true);
	}
	void RectTransform::AddPivot(const D3DXVECTOR2& _pivot)
	{
		m_pivot += _pivot;
		SetUpdateKey(true);
	}
	D3DXMATRIX* RectTransform::CreateWorldMatrix()
	{
		if (m_rect_transform_parent == nullptr)
		{
			m_rect_transform_parent = GetComponentParent<RectTransform>();
			if (m_rect_transform_parent == nullptr)
				m_rect_transform_parent = ThisComponent<RectTransform>();
		}

		if (m_rect_transform_parent->GetThisPtr() == this)
		{
			if (!GetUpdateKey())
				return &m_world_matrix;
			CreateLocalMatrix();

			D3DXMATRIX polygon;

			// ポリゴンのサイズを行列に変換
			D3DXMatrixScaling(&polygon, m_polygon.x, m_polygon.y, 0.0f);

			// ピボット分オフセット
			polygon._41 -= m_polygon.x * m_pivot.x;
			polygon._42 -= m_polygon.y * m_pivot.y;

			// ポリゴンと合成
			m_world_matrix = polygon * m_not_polygon_matrix;

			// ずらしたピボットを戻します
			m_world_matrix._41 += m_polygon.x * m_pivot.x;
			m_world_matrix._42 += m_polygon.y * m_pivot.y;
		}
		else
		{
			if (!GetUpdateKey() && !m_rect_transform_parent->GetUpdateKey())
				return &m_world_matrix;

			CreateLocalMatrix();

			D3DXMATRIX polygon;

			// ポリゴンのサイズを行列に変換
			D3DXMatrixScaling(&polygon, m_polygon.x, m_polygon.y, 0.0f);

			// ピボット分オフセット
			polygon._41 -= m_polygon.x * m_pivot.x;
			polygon._42 -= m_polygon.y * m_pivot.y;

			// ポリゴンと合成
			m_not_polygon_matrix = m_local_matrix * m_rect_transform_parent->m_not_polygon_matrix;
			m_world_matrix = polygon * m_local_matrix * m_rect_transform_parent->m_not_polygon_matrix;

			// ずらしたピボットを戻します
			m_world_matrix._41 += m_polygon.x * m_pivot.x;
			m_world_matrix._42 += m_polygon.y * m_pivot.y;
		}

		SetUpdateKey(true);

		return &m_world_matrix;
	}
	D3DXMATRIX* RectTransform::CreateLocalMatrix()
	{
		if (!GetUpdateKey())
			return &m_local_matrix;

		D3DXMATRIX MatRot;
		D3DXMATRIX MatSca;

		// 拡縮行列を作成します
		D3DXMatrixScaling(&MatSca, m_parameter.scale.x, m_parameter.scale.y, 0.0f);

		// 回転行列を作成します
		m_vector.MatrixVector(MatRot);

		// マトリクスの合成
		m_local_matrix = MatRot * MatSca;

		m_local_matrix._41 = m_parameter.position.x;
		m_local_matrix._42 = m_parameter.position.y;
		m_local_matrix._43 = 0.0f;

		m_local_matrix._14 = m_local_matrix._24 = m_local_matrix._34 = 0.0f;
		m_local_matrix._44 = 1.0f;

		m_not_polygon_matrix = m_local_matrix;

		return &m_local_matrix;
	}
	void RectTransform::CopyRectTransform(reference::IReference<RectTransform> _rect)
	{
		if (_rect == nullptr)
			return;

		m_polygon = _rect->m_polygon;
		m_pivot = _rect->m_pivot;
		m_look = _rect->m_look;
		m_vector = _rect->m_vector;
		m_parameter = _rect->m_parameter;
	}
	void RectTransform::GUIRectTransform()
	{
#if defined(_MSLIB_DEBUG)
		if (!imgui::NewTreeNode("RectTransform", false))
			return;

		constexpr float move_buff = 0.1f;
		auto pos_slider = imgui::CreateText("Slider : Polygon Size");
		auto pos_input = imgui::CreateText("Input : Polygon Size");
		float float4x2[2] = { 0 };

		if (imgui::_SliderFloat2(pos_slider.c_str(), float4x2, -move_buff, move_buff))
			AddPolygonSize(D3DXVECTOR2(float4x2[0], float4x2[1]));

		float4x2[0] = m_polygon.x;
		float4x2[1] = m_polygon.y;

		if (imgui::_InputFloat2(pos_input.c_str(), float4x2, ImGuiInputTextFlags_EnterReturnsTrue))
			SetPolygonSize(D3DXVECTOR2(float4x2[0], float4x2[1]));

		// パラメーターの表示
		if (imgui::NewTreeNode("Info", false))
		{
			auto mat_w_1 = imgui::CreateText("11[%.2f],12[%.2f],13[%.2f],14[%.2f]", m_not_polygon_matrix._11, m_not_polygon_matrix._12, m_not_polygon_matrix._13, m_not_polygon_matrix._14);
			auto mat_w_2 = imgui::CreateText("21[%.2f],22[%.2f],23[%.2f],24[%.2f]", m_not_polygon_matrix._21, m_not_polygon_matrix._22, m_not_polygon_matrix._23, m_not_polygon_matrix._24);
			auto mat_w_3 = imgui::CreateText("31[%.2f],32[%.2f],33[%.2f],34[%.2f]", m_not_polygon_matrix._31, m_not_polygon_matrix._32, m_not_polygon_matrix._33, m_not_polygon_matrix._34);
			auto mat_w_4 = imgui::CreateText("41[%.2f],42[%.2f],43[%.2f],44[%.2f]", m_not_polygon_matrix._41, m_not_polygon_matrix._42, m_not_polygon_matrix._43, m_not_polygon_matrix._44);

			imgui::Separator();
			imgui::Text("Matrix NotPolygon");
			imgui::Separator();
			imgui::Text(mat_w_1);
			imgui::Text(mat_w_2);
			imgui::Text(mat_w_3);
			imgui::Text(mat_w_4);
			imgui::EndTreeNode();
		}

		imgui::Separator();
		imgui::EndTreeNode();
#endif
	}
	void RectTransform::InputDataRectTransform(std::ifstream& _ifstream)
	{
		std::vector<float> i_polygon;
		std::vector<float> i_pivot;
		std::string line_str;
		float ftemp;

		// 開始位置に
		_ifstream.clear();
		_ifstream.seekg(0, std::ios_base::beg);

		// 列ごとの読み取り
		while (std::getline(_ifstream, line_str))
		{
			// #はコメント
			if (line_str[0] == '#')
				continue;
			// 入力命令
			if (line_str.find('=') == std::string::npos)
				continue;

			std::stringstream ss_str(line_str);
			std::string name_str;

			ss_str >> name_str;
			ss_str.ignore(line_str.size(), '=');

			if (name_str == "RectTransform_Polygon")
			{
				while (ss_str >> ftemp)
					i_polygon.push_back(ftemp);
			}
			else if (name_str == "RectTransform_Pivot")
			{
				while (ss_str >> ftemp)
					i_pivot.push_back(ftemp);
			}
		}

		if ((int)i_polygon.size() == 0)
			return;

		SetPolygonSize(i_polygon[0], i_polygon[1]);
		SetPivot(i_pivot[0], i_pivot[1]);
	}
	void RectTransform::OutputDataRectTransform(std::ofstream& _ofstream)
	{
		auto& po2 = m_polygon;
		auto& pi2 = m_pivot;

		auto pol_str = std::string("RectTransform_Polygon =") + " " + std::to_string(po2.x) + " " + std::to_string(po2.y);
		auto piv_str = std::string("RectTransform_Pivot =") + " " + std::to_string(pi2.x) + " " + std::to_string(pi2.y);

		_ofstream << std::string("#Set RectTransform_Polygon") << std::endl;
		_ofstream << pol_str << std::endl;
		_ofstream << std::string("#Set RectTransform_Pivot") << std::endl;
		_ofstream << piv_str << std::endl;
	}
	RectTransform* RectTransform::GetThisPtr()
	{
		return this;
	}
}
_MSLIB_END