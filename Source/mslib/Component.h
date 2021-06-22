//==========================================================================
// Component [Component.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <cstdio>
#include <algorithm>
#include <memory>
#include <list>

#include "mslib.hpp"
#include "Reference.h"

_MSLIB_BEGIN

namespace component
{
	using namespace reference;

	//==========================================================================
	//
	// class : Component
	// Content : Component Class
	//
	//==========================================================================
	class Component
	{
	private:
		Component(const Component&) = delete;
		Component(Component&&) = delete;
		Component& operator=(const Component&) = delete;
		Component& operator=(Component&&) = delete;
	public:
		Component() : m_component_hash_code(typeid(Component).hash_code()) {
			int size = snprintf(nullptr, 0, "%p", this) + 1; // Extra space for '\0'
			std::unique_ptr<char[]> buf(new char[size]);
			snprintf(buf.get(), size, "%p", this);
			m_component_name = std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
			m_component_this = std::shared_ptr<Component>(this, [](Component* p) {p = nullptr; });
		}
		Component(const std::string& _Name) :m_component_name(_Name), m_component_hash_code(typeid(Component).hash_code()) {
			m_component_this = std::shared_ptr<Component>(this, [](Component* p) {p = nullptr; });
		}
		virtual ~Component() {
			DestroyComponent();
			m_component_child.clear();
			m_component_name.clear();
			m_component_thisptrs.clear();
		}

		/**
		English
		@brief this component
		@return Monitoring function reference class
		Japanese
		@brief this component
		@return �Ď��@�\�̎Q�ƃN���X
		*/
		IReference <Component> ThisComponent() {
			return m_component_this;
		}

		/**
		English
		@brief this component
		@return Monitoring function reference class
		Japanese
		@brief this component
		@return �Ď��@�\�̎Q�ƃN���X
		*/
		template <typename _Ty, bool isExtended = std::is_base_of<Component, _Ty>::value>
		IReference <_Ty> ThisComponent() {
			auto itr1 = m_component_thisptrs.find(typeid(_Ty).hash_code());
			if (itr1 == m_component_thisptrs.end()) {
				if (dynamic_cast<_Ty*>(this) == nullptr) {
					m_component_thisptrs[typeid(_Ty).hash_code()];
					return IReference <_Ty>();
				}
				else {
					auto itr2 = m_component_thisptrs[typeid(_Ty).hash_code()] = m_component_this;
					return std::dynamic_pointer_cast<_Ty>(m_component_this);
				}
			}
			return std::dynamic_pointer_cast<_Ty>(itr1->second);
		}

		/**
		English
		@brief Please add the component. Failure to inherit Component results in an error.
		@param _Ref [in] Raw pointer
		@return Monitoring function reference class
		Japanese
		@brief �R���|�[�l���g��ǉ����Ă��������BComponent���p�����Ȃ��ƃG���[�ɂȂ�܂��B
		@param _Ref [in] ���|�C���^
		@return �Ď��@�\�̎Q�ƃN���X
		*/
		template <typename _Ty, bool isExtended = std::is_base_of<Component, _Ty>::value>
		IReference <_Ty> AddComponent(_Ty* _Ref) {
			static_assert(isExtended, "AddComponent<> : _Ty is not inherited from Component Class");

			std::shared_ptr<_Ty> ptr(_Ref);
			ptr->m_component_hash_code = typeid(_Ty).hash_code();
			m_component_child[ptr->m_component_hash_code].emplace_back(ptr);
			ptr->m_component_parent = m_component_this;
			return ptr;
		}

		/**
		English
		@brief Get component
		@return Monitoring function reference class
		Japanese
		@brief �R���|�[�l���g�̎擾
		@return �Ď��@�\�̎Q�ƃN���X
		*/
		template <typename _Ty, bool isExtended = std::is_base_of<Component, _Ty>::value>
		IReference <_Ty> GetComponent() {
			static_assert(isExtended, "GetComponent<> : _Ty is not inherited from Component Class");

			// �擾�Ώۂ̌^�����邩�̃`�F�b�N
			auto itr = m_component_child.find(typeid(_Ty).hash_code());
			if (itr == m_component_child.end())
				return IReference <_Ty>();

			// ��p�̊Ǘ��g�����������A���Ԃ������ꍇ�I��
			if ((int)itr->second.size() == 0)
				return IReference <_Ty>();

			// ��ԍŌ�ɓo�^���ꂽ�R���|�[�l���g���擾
			return std::dynamic_pointer_cast<_Ty>((*--itr->second.end()));
		}

		/**
		English
		@brief Get component
		@param _Name [in] Component name
		@return Monitoring function reference class
		Japanese
		@brief �R���|�[�l���g�̎擾
		@param _Name [in] �R���|�[�l���g��
		@return �Ď��@�\�̎Q�ƃN���X
		*/
		template <typename _Ty, bool isExtended = std::is_base_of<Component, _Ty>::value>
		IReference <_Ty> GetComponent(const std::string& _Name) {
			static_assert(isExtended, "GetComponent<> : _Ty is not inherited from Component Class");

			// �擾�Ώۂ̌^�����邩�̃`�F�b�N
			auto itr1 = m_component_child.find(typeid(_Ty).hash_code());
			if (itr1 == m_component_child.end())
				return IReference <_Ty>();

			// �Ώۂ̃R���|�[�l���g���o������܂ő����A�o�������ꍇ�͂��̎��̂�Ԃ�
			for (auto& itr2 : itr1->second)
			{
				// �ΏۃR���|�[�l���g���̎擾�Ɏ��s
				if (itr2->m_component_name != _Name)
					continue;

				// �ΏۃR���|�[�l���g�̎擾
				return std::dynamic_pointer_cast<_Ty>(itr2);
			}
			return IReference <_Ty>();
		}

		/**
		English
		@brief Get component
		@param _Name [in] Component name
		@return Monitoring function reference class
		Japanese
		@brief �R���|�[�l���g�̎擾
		@param _Name [in] �R���|�[�l���g��
		@return �Ď��@�\�̎Q�ƃN���X
		*/
		IReference <Component> GetComponent(const std::string& _Name) {
			// �Ώۂ̃R���|�[�l���g���o������܂ő����A�o�������ꍇ�͂��̎��̂�Ԃ�
			for (auto& itr1 : m_component_child)
				for (auto& itr2 : itr1.second)
					if (itr2->m_component_name == _Name)
						return itr2;
			return IReference <Component>();
		}

		/**
		English
		@brief Set component
		@param _Ref [in] Raw pointer
		@return Returns true on success, false on failure.
		Japanese
		@brief Set component
		@param _Ref [in] ���|�C���^
		@return ���������ꍇ��true�A���s�����ꍇ��false��Ԃ��܂��B
		*/
		template <typename _Ty, bool isExtended = std::is_base_of<Component, _Ty>::value>
		bool SetComponent(_Ty* _Ref) {
			static_assert(isExtended, "SetComponent<> : _Ty is not inherited from Component Class");

			_Ref->m_component_hash_code = typeid(_Ty).hash_code();
			return AddComponent(_Ref).check();
		}

		/**
		English
		@brief Set component
		@param _Ref [in] Monitoring function reference class
		@return Returns true on success, false on failure.
		Japanese
		@brief Set component
		@param _Ref [in] �Ď��@�\�̎Q�ƃN���X
		@return ���������ꍇ��true�A���s�����ꍇ��false��Ԃ��܂��B
		*/
		template <typename _Ty, bool isExtended = std::is_base_of<Component, _Ty>::value>
		bool SetComponent(IReference <_Ty>& _Ref) {
			static_assert(isExtended, "SetComponent<> : _Ty is not inherited from Component Class");

			// �Ď��Ώۂ����݂��Ȃ��ꍇ�A���s
			if (!_Ref.check())
				return false;
			if (_Ref->m_component_this == m_component_this)
				return false;
			// �Ώۂ̏��L�����ړ����܂�
			return _Ref->move(m_component_this);
		}

		/**
		English
		@brief Discard component
		Japanese
		@brief �R���|�[�l���g��j��
		*/
		void DestroyComponent() {
			m_component_child.clear();
		}

		/**
		English
		@brief Discard specified component
		@return Returns true if it succeeds, false if it fails.
		Japanese
		@brief �w�肳�ꂽ�R���|�[�l���g��j��
		@return ���������ꍇ��true�A���s�����ꍇ��false��Ԃ��܂��B
		*/
		template <typename _Ty, bool isExtended = std::is_base_of<Component, _Ty>::value>
		bool DestroyComponent() {
			(isExtended, "DestroyComponent<> : _Ty is not inherited from Component Class");

			// �w�肳�ꂽ�^�̃O���[�v��j������
			auto itr = m_component_child.find(typeid(_Ty).hash_code());
			if (itr == m_component_child.end())
				return false;
			m_component_child.erase(itr);
			return true;
		}

		/**
		English
		@brief Discard specified component
		@param _Ref [in] Monitoring function reference class
		@return Returns true if it succeeds, false if it fails.
		Japanese
		@brief �w�肳�ꂽ�R���|�[�l���g��j��
		@param _Ref [in] �Ď��@�\�̎Q�ƃN���X
		@return ���������ꍇ��true�A���s�����ꍇ��false��Ԃ��܂��B
		*/
		template <typename _Ty, bool isExtended = std::is_base_of<Component, _Ty>::value>
		bool DestroyComponent(IReference <_Ty>& _Ref) {
			static_assert(isExtended, "DestroyComponent<> : _Ty is not inherited from Component Class");
			if (_Ref == nullptr)
				return true;

			// �j���Ώۂ̌^������
			auto itr1 = m_component_child.find(typeid(_Ty).hash_code());
			if (itr1 == m_component_child.end())
				return false;

			// �j���Ώۂ̌���
			auto itr2 = std::find(itr1->second.begin(), itr1->second.end(), _Ref->m_component_this);
			if (itr2 == itr1->second.end())
				return false;

			// �j��
			itr1->second.erase(itr2);
			_Ref.clear();
			return true;
		}

		/**
		English
		@brief Discard specified component
		@param _Name [in] Component name
		@return Returns true if it succeeds, false if it fails.
		Japanese
		@brief �w�肳�ꂽ�R���|�[�l���g��j��
		@param _Name [in] �R���|�[�l���g�̖��O
		@return ���������ꍇ��true�A���s�����ꍇ��false��Ԃ��܂��B
		*/
		bool DestroyComponent(const std::string& _Name) {
			bool flag = false;
			// �^�O���[�v����
			for (auto& itr1 : m_component_child)
				// �Ώۂ̃R���|�[�l���g���o������܂ő����A�o�������ꍇ�͂��̎��̂�j������
				for (auto itr2 = itr1.second.begin(); itr2 != itr1.second.end();) {
					// �Ώۂ̃R���|�[�l���g������v���Ȃ�
					if ((*itr2)->m_component_name != _Name) {
						++itr2;
						continue;
					}
					itr2 = itr1.second.erase(itr2);
					flag = true;
				}
			return flag;
		}

		/**
		English
		@brief Discard specified component
		@param _Name [in] Component name
		@return Returns true if it succeeds, false if it fails.
		Japanese
		@brief �w�肳�ꂽ�R���|�[�l���g��j��
		@param _Name [in] �R���|�[�l���g�̖��O
		@return ���������ꍇ��true�A���s�����ꍇ��false��Ԃ��܂��B
		*/
		template <typename _Ty, bool isExtended = std::is_base_of<Component, _Ty>::value>
		bool DestroyComponent(const std::string& _Name) {
			static_assert(isExtended, "DestroyComponent<> : _Ty is not inherited from Component Class");

			bool flag = false;

			// �j���Ώۂ̌^������
			auto itr1 = m_component_child.find(typeid(_Ty).hash_code());
			if (itr1 == m_component_child.end())
				return flag;

			// �Ώۂ̃R���|�[�l���g���o������܂ő����A�o�������ꍇ�͂��̎��̂�j������
			for (auto itr2 = itr1->second.begin(); itr2 != itr1->second.end();) {
				// �Ώۂ̃R���|�[�l���g������v���Ȃ�
				if ((*itr2)->m_component_name != _Name) {
					++itr2;
					continue;
				}
				itr2 = itr1->second.erase(itr2);
				flag = true;
			}
			return flag;
		}

		/**
		English
		@brief Set component name
		@param _Name [in] Component name
		Japanese
		@brief �R���|�[�l���g����ݒ�
		@param _Name [in] �R���|�[�l���g�̖��O
		*/
		void SetComponentName(const std::string& _Name) {
			m_component_name = _Name;
		}

		/**
		English
		@brief Get component name
		@return Component name
		Japanese
		@brief �R���|�[�l���g�����擾
		@return �R���|�[�l���g�̖��O
		*/
		const std::string& GetComponentName() const {
			return m_component_name;
		}

		/**
		English
		@brief Get the number of child elements
		@return Number of child elements
		Japanese
		@brief �q�v�f�̐����擾����
		@return �q�v�f�̐�
		*/
		int GetNumChild() {
			int num = 0;
			for (auto& itr1 : m_component_child)
				num += (int)itr1.second.size();
			return num;
		}

		/**
		English
		@brief Get child elements
		@return Child element
		Japanese
		@brief �q�v�f���擾����
		@return �q�v�f
		*/
		const std::list<IReference<Component>> GetComponentChild() const {
			std::list<IReference<Component>> ref;
			for (auto& itr1 : m_component_child)
				for (auto& itr2 : itr1.second)
					ref.push_back(itr2);
			return ref;
		}

		/**
		English
		@brief Get child elements
		@return Child element
		Japanese
		@brief �q�v�f���擾����
		@return �q�v�f
		*/
		template<typename _Ty, bool isExtended = std::is_base_of<Component, _Ty>::value>
		const std::list<IReference<_Ty>> GetComponentChild() const {
			static_assert(isExtended, "GetComponentChild<> : _Ty is not inherited from Component Class");

			std::list<IReference<_Ty>> ref;

			// �擾�Ώۂ̌^�����邩�̃`�F�b�N
			auto itr1 = m_component_child.find(typeid(_Ty).hash_code());
			if (itr1 == m_component_child.end())
				return ref;

			// �w�肳�ꂽ�^�̏����擾
			for (auto& itr2 : itr1->second)
				ref.push_back(itr2);
			return ref;
		}

		/**
		English
		@brief Get parent element
		@return Parent element
		Japanese
		@brief �e�v�f���擾����
		@return �e�v�f
		*/
		IReference <Component> GetComponentParent() {
			return m_component_parent;
		}

		/**
		English
		@brief Get parent element
		@return Parent element
		Japanese
		@brief �e�v�f���擾����
		@return �e�v�f
		*/
		template<typename _Ty, bool isExtended = std::is_base_of<Component, _Ty>::value>
		IReference <_Ty> GetComponentParent() {
			static_assert(isExtended, "GetComponentParent<> : _Ty is not inherited from Component Class");

			if (!m_component_parent.check())
				return IReference<_Ty>();
			return m_component_parent->ThisComponent<_Ty>();
		}

	private:
		/**
		@brief English : Abandon administration authority
		@brief Japanese : �Ǘ��������ړ�����
		@return �ړ������� true ���Ԃ�܂�
		*/
		bool move(IReference<Component> _Par) {
			if (!m_component_parent.check())
				return false;
			if (!_Par.check())
				return false;

			// �ړ����������̌^���擾
			auto itr1 = m_component_parent->m_component_child.find(m_component_hash_code);
			if (itr1 == m_component_parent->m_component_child.end())
				return false;

			// �ړ��Ώۂ��擾
			auto itr2 = std::find(itr1->second.begin(), itr1->second.end(), m_component_this);
			if (itr2 == itr1->second.end())
				return false;

			// �Q�Ɛ��𑝂₵�܂�
			auto ptr_copy = std::shared_ptr<Component>((*itr2));
			itr1->second.erase(itr2);

			// �ړ���Ƀf�[�^��n���܂�
			_Par->m_component_child[m_component_hash_code].emplace_back(ptr_copy);
			ptr_copy->m_component_parent = _Par->m_component_this;
			return true;
		}
	private:
		std::unordered_map<size_t, std::list<std::shared_ptr<Component>>> m_component_child; // �R���|�[�l���g�̊Ǘ�
		std::unordered_map<size_t, std::shared_ptr<Component>> m_component_thisptrs; // ���g
		std::shared_ptr<Component> m_component_this; // ���g
		IReference<Component> m_component_parent; // �e�R���|�[�l���g
		std::string m_component_name; // �R���|�[�l���g��
		size_t m_component_hash_code; // �R���|�[�l���g�̃n�b�V��
	};

	template <typename _Ty, bool isExtended = std::is_base_of<Component, _Ty>::value>
	inline void Destroy(IReference<_Ty>& _Ref)
	{
		static_assert(isExtended, "Destroy <> : _Ty is not inherited from Component Class");
		if (_Ref == nullptr)
			return;
		if (!_Ref->GetComponentParent().check())
			return;
		_Ref->GetComponentParent()->DestroyComponent(_Ref);
	}

	using ComponentReference = IReference<Component>;
}

_MSLIB_END