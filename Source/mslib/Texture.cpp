//==========================================================================
// テクスチャ [Texture.cpp]
// author : MasyoLab
//==========================================================================
#include "Texture.h"
#include "MsImGui.h"
#include "get_path_and_file.h"

_MSLIB_BEGIN

namespace texture
{
	constexpr char* NotTexture = "NotTexture";

#if defined(_MSLIB_DEBUG)
	std::list<TextureData*> TextureData::m_textures;
#endif

	ImageInfo::ImageInfo()
	{
		Width = (UINT)0;
		Height = (UINT)0;
		Depth = (UINT)0;
		MipLevels = (UINT)0;
		Format = D3DFMT_FORCE_DWORD;
		ResourceType = D3DRTYPE_FORCE_DWORD;
		ImageFileFormat = D3DXIFF_FORCE_DWORD;
	}
	ImageInfo::ImageInfo(UINT _width, UINT _height, UINT _depth, UINT _mipLevels, D3DFORMAT _format, D3DRESOURCETYPE _resourceType, D3DXIMAGE_FILEFORMAT _imageFileFormat)
	{
		Width = _width;
		Height = _height;
		Depth = _depth;
		MipLevels = _mipLevels;
		Format = _format;
		ResourceType = _resourceType;
		ImageFileFormat = _imageFileFormat;
	}
	ImageInfo::~ImageInfo()
	{
	}

	TextureData::TextureData() :
		m_createID(0), m_info(), m_texture(nullptr)
	{
#if defined(_MSLIB_DEBUG)
		m_open = false;
		m_textures.push_back(this);
#endif
	}
	TextureData::~TextureData()
	{
		if (m_texture != nullptr)
			m_texture->Release();
		m_texture = nullptr;
		
#if defined(_MSLIB_DEBUG)
		auto itr = std::find(m_textures.begin(), m_textures.end(), this);
		if (itr != m_textures.end())
			m_textures.erase(itr);
#endif
	}

	const LPDIRECT3DTEXTURE9 TextureData::GetTexture() const
	{
		return m_texture;
	}

	const ImageInfo& TextureData::GetImageInfo() const
	{
		return m_info;
	}

	int64_t TextureData::GetCreateID()
	{
		return m_createID;
	}

	void TextureData::GUITexture()
	{
#if defined(_MSLIB_DEBUG)
		if (m_texture == nullptr)
			return;

		imgui::Image(m_texture, { (float)m_info.Width,(float)m_info.Height }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, 400);
		imgui::Text(imgui::CreateText("Texture Name : %s", m_tag.c_str()));
		imgui::Text(imgui::CreateText("Width : %d", (int)m_info.Width));
		imgui::Text(imgui::CreateText("Height : %d", (int)m_info.Height));
		imgui::Text(imgui::CreateText("Depth : %d", (int)m_info.Depth));
		imgui::Text(imgui::CreateText("MipLevels : %d", (int)m_info.MipLevels));
		imgui::Text(imgui::CreateText("Format : %d", (int)m_info.Format));

		switch (m_info.ResourceType)
		{
		case D3DRESOURCETYPE::D3DRTYPE_SURFACE:
			imgui::Text("Resource type : Surface");
			break;
		case D3DRESOURCETYPE::D3DRTYPE_VOLUME:
			imgui::Text("Resource type : Volume");
			break;
		case D3DRESOURCETYPE::D3DRTYPE_TEXTURE:
			imgui::Text("Resource type : Texture");
			break;
		case D3DRESOURCETYPE::D3DRTYPE_VOLUMETEXTURE:
			imgui::Text("Resource type : Volume texture");
			break;
		case D3DRESOURCETYPE::D3DRTYPE_CUBETEXTURE:
			imgui::Text("Resource type : Cube texture");
			break;
		case D3DRESOURCETYPE::D3DRTYPE_VERTEXBUFFER:
			imgui::Text("Resource type : Vertex buffer");
			break;
		case D3DRESOURCETYPE::D3DRTYPE_INDEXBUFFER:
			imgui::Text("Resource type : Index buffer");
			break;
		default:
			break;
		}
		switch (m_info.ImageFileFormat)
		{
		case D3DXIMAGE_FILEFORMAT::D3DXIFF_BMP:
			imgui::Text("Image file format : BMP");
			break;
		case D3DXIMAGE_FILEFORMAT::D3DXIFF_JPG:
			imgui::Text("Image file format : JPG");
			break;
		case D3DXIMAGE_FILEFORMAT::D3DXIFF_TGA:
			imgui::Text("Image file format : TGA");
			break;
		case D3DXIMAGE_FILEFORMAT::D3DXIFF_PNG:
			imgui::Text("Image file format : PNG");
			break;
		case D3DXIMAGE_FILEFORMAT::D3DXIFF_DDS:
			imgui::Text("Image file format : DDS");
			break;
		case D3DXIMAGE_FILEFORMAT::D3DXIFF_PPM:
			imgui::Text("Image file format : PPM");
			break;
		case D3DXIMAGE_FILEFORMAT::D3DXIFF_DIB:
			imgui::Text("Image file format : DIB");
			break;
		case D3DXIMAGE_FILEFORMAT::D3DXIFF_HDR:
			imgui::Text("Image file format : HDR");
			break;
		case D3DXIMAGE_FILEFORMAT::D3DXIFF_PFM:
			imgui::Text("Image file format : PFM");
			break;
		case D3DXIMAGE_FILEFORMAT::D3DXIFF_FORCE_DWORD:
			imgui::Text("Image file format : NONE");
			break;
		default:
			break;
		}
		imgui::Separator();
#endif
	}

	void TextureData::GUITextureList()
	{
#if defined(_MSLIB_DEBUG)
		if (imgui::NewTreeNode("Texture GUI", false))
		{
			for (auto& itr : m_textures)
				if (itr->GetTexture() != nullptr)
					imgui::Checkbox(itr->GetTag(), itr->m_open);
			imgui::EndTreeNode();
		}

		for (auto& itr : m_textures)
		{
			if (!itr->m_open)
				continue;
			imgui::_Begin(itr->GetTag().c_str(), &itr->m_open, ImGuiWindowFlags_NoSavedSettings);
			itr->GUITexture();
			imgui::EndWindow();
		}
#endif
	}

	TextureLoader::TextureLoader() :
		m_createIDCount(0), m_device(nullptr), m_hwnd(nullptr)
	{
		SetComponentName("TextureLoader");
	}
	TextureLoader::TextureLoader(LPDIRECT3DDEVICE9 _device, HWND _hwnd) :
		m_createIDCount(0), m_device(_device), m_hwnd(_hwnd)
	{
		SetComponentName("TextureLoader");
	}
	TextureLoader::~TextureLoader()
	{
	}

	TextureReference TextureLoader::Load(const std::string& _str)
	{
		auto itr = m_resource_list.find(_str);
		if (itr == m_resource_list.end())
			return LoadTexture(_str);
		return itr->second;
	}

	TextureReference TextureLoader::CreateTexture(UINT _width, UINT _height, UINT _mip_levels, DWORD _usage, D3DFORMAT _format, D3DPOOL _pool)
	{
		m_createIDCount++; // 生成カウンタを回す

		auto name = std::to_string(m_createIDCount);
		LPDIRECT3DTEXTURE9 ptexture = nullptr;

		D3DXCreateTexture(m_device, _width, _height, _mip_levels, _usage, _format, _pool, &ptexture);
		ImageInfo iinfo = ImageInfo(_width, _height, 0, _mip_levels, _format, ptexture->GetType(), D3DXIFF_FORCE_DWORD);

		return m_resource_list[name] = TextureData::Create(new TextureDataInput(m_createIDCount, iinfo, ptexture, name, ThisComponent<Loader>()));
	}

	std::list<TextureReference> TextureLoader::GetData()
	{
		std::list<TextureReference> ref_list;
		for (auto& itr : m_resource_list)
			ref_list.push_back(itr.second);
		return ref_list;
	}

	TextureReference TextureLoader::LoadTexture(const std::string& _path)
	{
		LPDIRECT3DTEXTURE9 ptexture = nullptr;
		ImageInfo iinfo;
		std::string tag_str;

		// 読み込みに失敗していない
		if (!FAILED(D3DXCreateTextureFromFile(m_device, _path.c_str(), &ptexture)))
		{
			// 画像データの格納
			D3DXGetImageInfoFromFile(_path.c_str(), &iinfo);
			tag_str = _path;
		}
		// 読み込みに失敗時
		else
		{
			ptexture = nullptr;
			tag_str = NotTexture;
			iinfo = ImageInfo();

			// 失敗対象が空以外の時に実行
			if (_path != "")
			{
				std::string text = "テクスチャが存在しません \n %s";
				size_t size = snprintf(nullptr, 0, text.c_str(), _path.c_str()) + 1; // Extra space for '\0'
				std::unique_ptr<char[]> buf(new char[size]);
				snprintf(buf.get(), size, text.c_str(), _path.c_str());
				MessageBox(m_hwnd, std::string(buf.get(), buf.get() + size - 1).c_str(), "ERROR", MB_OK | MB_ICONEXCLAMATION | MB_ICONWARNING);
			}
		}

		auto path_str = get_path_and_file::GetPathAndFile(_path);

		m_createIDCount++; // 生成カウンタを回す
		return m_resource_list[_path] =
			TextureData::Create(new TextureDataInput(
				m_createIDCount, iinfo, ptexture, path_str.m_file_name + path_str.m_ext_name, ThisComponent<Loader>()));
	}

	SetTexture::SetTexture()
	{
	}

	SetTexture::~SetTexture()
	{
	}

	void SetTexture::SetTextureData(const TextureReference& _textureData)
	{
		m_texture_data = _textureData;
	}

	TextureReference SetTexture::GetTextureData()
	{
		return m_texture_data;
	}
	void SetTexture::GUITexture()
	{
#if defined(_MSLIB_DEBUG)
		if (!imgui::NewTreeNode("Texture", false))
			return;

		if (!m_texture_data.check()) {
			imgui::EndTreeNode();
			return;
		}
		if (m_texture_data->GetTexture() == nullptr) {
			imgui::EndTreeNode();
			return;
		}
		m_texture_data->GUITexture();
		imgui::EndTreeNode();
#endif
	}
	TextureLoader::TextureDataInput::TextureDataInput()
	{
	}
	TextureLoader::TextureDataInput::TextureDataInput(int64_t _id, const ImageInfo& _info, LPDIRECT3DTEXTURE9 _texture, const std::string& _tag, resource_loader::LoaderReference _loader)
	{
		m_createID = _id;
		m_info = _info;
		m_texture = _texture;
		m_tag = _tag;
		m_loader_ptr = _loader;
	}
	TextureLoader::TextureDataInput::~TextureDataInput()
	{
	}
}

_MSLIB_END