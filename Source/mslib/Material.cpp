//==========================================================================
// マテリアル [Material.cpp]
// author : MasyoLab
//==========================================================================
#include "Material.h"
#include "MsImgui.h"
#include "string_encode.hpp"

_MSLIB_BEGIN

namespace material
{
	MaterialLighting::MaterialLighting()
	{
		ZeroMemory(&m_material9, sizeof(m_material9));
		m_material9.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_material9.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_material9.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_material9.Emissive = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_material9.Power = 1.0f;
	}

	MaterialLighting::~MaterialLighting()
	{
	}

	void MaterialLighting::SetAmbient(const D3DXCOLOR& color)
	{
		m_material9.Ambient = color;
	}

	void MaterialLighting::SetDiffuse(const D3DXCOLOR& color)
	{
		m_material9.Diffuse = color;
	}

	void MaterialLighting::SetSpecular(const D3DXCOLOR& color)
	{
		m_material9.Specular = color;
	}

	void MaterialLighting::SetEmissive(const D3DXCOLOR& color)
	{
		m_material9.Emissive = color;
	}

	void MaterialLighting::SetSpecularPower(float power)
	{
		m_material9.Power = power;
	}

	const D3DMATERIAL9& MaterialLighting::GetMaterialLighting()
	{
		return m_material9;
	}

	void MaterialLighting::GUIMaterialLighting()
	{
#if defined(_MSLIB_DEBUG)
		if (!imgui::NewTreeNode("Material Lighting", false))
			return;

		if (imgui::NewTreeNode("Color Pallet : Ambient", false))
		{
			imgui::Separator();
			m_material9.Ambient = imgui::ColorEdit(m_material9.Ambient);
			imgui::EndTreeNode();
		}
		if (imgui::NewTreeNode("Color Pallet : Diffuse", false))
		{
			imgui::Separator();
			m_material9.Diffuse = imgui::ColorEdit(m_material9.Diffuse);
			imgui::EndTreeNode();
		}
		if (imgui::NewTreeNode("Color Pallet : Specular", false))
		{
			imgui::Separator();
			m_material9.Specular = imgui::ColorEdit(m_material9.Specular);
			imgui::EndTreeNode();
		}
		if (imgui::NewTreeNode("Color Pallet : Emissive", false))
		{
			imgui::Separator();
			m_material9.Emissive = imgui::ColorEdit(m_material9.Emissive);
			imgui::EndTreeNode();
		}
		if (imgui::NewTreeNode("Input Edit", false))
		{
			float float4x4[4][4] = { 0.0f };
			float float1 = 0.0f;
			auto ambient_slider = imgui::CreateText("Slider : Ambient");
			auto diffuse_slider = imgui::CreateText("Slider : Diffuse");
			auto specular_slider = imgui::CreateText("Slider : Specular");
			auto emissive_slider = imgui::CreateText("Slider : Emissive");
			auto power_slider = imgui::CreateText("Slider : Power");

			auto ambient_input = imgui::CreateText("Input : Ambient");
			auto diffuse_input = imgui::CreateText("Input : Diffuse");
			auto specular_input = imgui::CreateText("Input : Specular");
			auto emissive_input = imgui::CreateText("Input : Emissive");
			auto power_input = imgui::CreateText("Input : Power");

			float4x4[0][0] = m_material9.Ambient.r;
			float4x4[0][1] = m_material9.Ambient.g;
			float4x4[0][2] = m_material9.Ambient.b;
			float4x4[0][3] = m_material9.Ambient.a;

			float4x4[1][0] = m_material9.Diffuse.r;
			float4x4[1][1] = m_material9.Diffuse.g;
			float4x4[1][2] = m_material9.Diffuse.b;
			float4x4[1][3] = m_material9.Diffuse.a;

			float4x4[2][0] = m_material9.Specular.r;
			float4x4[2][1] = m_material9.Specular.g;
			float4x4[2][2] = m_material9.Specular.b;
			float4x4[2][3] = m_material9.Specular.a;

			float4x4[3][0] = m_material9.Emissive.r;
			float4x4[3][1] = m_material9.Emissive.g;
			float4x4[3][2] = m_material9.Emissive.b;
			float4x4[3][3] = m_material9.Emissive.a;

			float1 = m_material9.Power;

			imgui::Separator();
			if (imgui::_SliderFloat4(ambient_slider.c_str(), float4x4[0], 0.0f, 1.0f))
				SetAmbient(D3DXCOLOR(float4x4[0][0], float4x4[0][1], float4x4[0][2], float4x4[0][3]));
			if (imgui::_SliderFloat4(diffuse_slider.c_str(), float4x4[1], 0.0f, 1.0f))
				SetDiffuse(D3DXCOLOR(float4x4[1][0], float4x4[1][1], float4x4[1][2], float4x4[1][3]));
			if (imgui::_SliderFloat4(specular_slider.c_str(), float4x4[2], 0.0f, 1.0f))
				SetSpecular(D3DXCOLOR(float4x4[2][0], float4x4[2][1], float4x4[2][2], float4x4[2][3]));
			if (imgui::_SliderFloat4(emissive_slider.c_str(), float4x4[3], 0.0f, 1.0f))
				SetEmissive(D3DXCOLOR(float4x4[3][0], float4x4[3][1], float4x4[3][2], float4x4[3][3]));
			if (imgui::_InputFloat(power_slider.c_str(), &float1, ImGuiInputTextFlags_EnterReturnsTrue))
			{
				if (float1 < 0)
					float1 = 0;
				m_material9.Power = float1;
			}
			imgui::EndTreeNode();
		}
		imgui::EndTreeNode();
#endif
	}

	void MaterialLighting::InputDataMaterialLighting(std::ifstream& _ifstream)
	{
		std::vector<float> i_Ambient;
		std::vector<float> i_Diffuse;
		std::vector<float> i_Specular;
		std::vector<float> i_Emissive;
		float i_Power = 0.0f;
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

			if (name_str == "Material_Ambient")
			{
				while (ss_str >> ftemp)
					i_Ambient.push_back(ftemp);
			}
			else if (name_str == "Material_Diffuse")
			{
				while (ss_str >> ftemp)
					i_Diffuse.push_back(ftemp);
			}
			else if (name_str == "Material_Specular")
			{
				while (ss_str >> ftemp)
					i_Specular.push_back(ftemp);
			}
			else if (name_str == "Material_Emissive")
			{
				while (ss_str >> ftemp)
					i_Emissive.push_back(ftemp);
			}
			else if (name_str == "Material_Power")
			{
				ss_str >> i_Power;
			}
		}

		if ((int)i_Ambient.size() == 0)
			return;

		SetAmbient(D3DXCOLOR(i_Ambient[0], i_Ambient[1], i_Ambient[2], i_Ambient[3]));
		SetDiffuse(D3DXCOLOR(i_Diffuse[0], i_Diffuse[1], i_Diffuse[2], i_Diffuse[3]));
		SetSpecular(D3DXCOLOR(i_Specular[0], i_Specular[1], i_Specular[2], i_Specular[3]));
		SetEmissive(D3DXCOLOR(i_Emissive[0], i_Emissive[1], i_Emissive[2], i_Emissive[3]));
		SetSpecularPower(i_Power);
	}

	void MaterialLighting::OutputDataMaterialLighting(std::ofstream& _ofstream)
	{
		auto& amb4 = m_material9.Ambient;
		auto& dif4 = m_material9.Diffuse;
		auto& spe4 = m_material9.Specular;
		auto& emi4 = m_material9.Emissive;
		auto& pow1 = m_material9.Power;

		auto amb_str = std::string("Material_Ambient =") + " " + std::to_string(amb4.r) + " " + std::to_string(amb4.g) + " " + std::to_string(amb4.b) + " " + std::to_string(amb4.a);
		auto dif_str = std::string("Material_Diffuse =") + " " + std::to_string(dif4.r) + " " + std::to_string(dif4.g) + " " + std::to_string(dif4.b) + " " + std::to_string(dif4.a);
		auto spe_str = std::string("Material_Specular =") + " " + std::to_string(spe4.r) + " " + std::to_string(spe4.g) + " " + std::to_string(spe4.b) + " " + std::to_string(spe4.a);
		auto emi_str = std::string("Material_Emissive =") + " " + std::to_string(emi4.r) + " " + std::to_string(emi4.g) + " " + std::to_string(emi4.b) + " " + std::to_string(emi4.a);
		auto pow_str = std::string("Material_Power =") + " " + std::to_string(pow1);

		_ofstream << std::string("#Set Material_Ambient") << std::endl;
		_ofstream << amb_str << std::endl;
		_ofstream << std::string("#Set Material_Diffuse") << std::endl;
		_ofstream << dif_str << std::endl;
		_ofstream << std::string("#Set Material_Specular") << std::endl;
		_ofstream << spe_str << std::endl;
		_ofstream << std::string("#Set Material_Emissive") << std::endl;
		_ofstream << emi_str << std::endl;
		_ofstream << std::string("#Set Material_Power") << std::endl;
		_ofstream << pow_str << std::endl;
	}
}

_MSLIB_END