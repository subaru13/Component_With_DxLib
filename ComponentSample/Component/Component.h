#pragma once
#include <type_traits>
#include <concepts>
#include <memory>

class Object;
class ComponentContainer;

/*
	RTTI�̂����̎��s���^�ŗLID
	2^16��ID���쐬���邱�Ƃ��ł���̂�
	����Ȃ��Ȃ邱�Ƃ͂Ȃ��Ǝv����
	����Ȃ��Ȃ�����g������
*/
class RuntimeTypeUniqueID final
{
public:
	using Value = uint16_t;
private:
	RuntimeTypeUniqueID() = delete;
	~RuntimeTypeUniqueID() = delete;
private:
	static inline Value nextId = 0;
public:
	template<class T>
	static Value Get()
	{
		static const Value id{ nextId++ };
		return id;
	}
};

class Component
{
public:
	using TypeUniqueID = RuntimeTypeUniqueID::Value;

public:
	Component() = default;

	virtual bool CheckUniqueID(TypeUniqueID typeUniqueID) const;

	virtual void Update();

	virtual ~Component() = default;
protected:
	const std::weak_ptr<Object>& GetOwner() const;
private:
	std::weak_ptr<Object> mOwner;
	TypeUniqueID mTypeUniqueID{};
private:
	friend ComponentContainer;
	void SetComponentInfo(const std::weak_ptr<Object>& owner, TypeUniqueID typeUniqueID);
};

template<class T>
concept ComponentType = std::is_same_v<Component, T> || (std::is_base_of_v<Component, T> && std::constructible_from<T>);

template<ComponentType T>
static std::shared_ptr<T> ComponentDynamicCast(const std::shared_ptr<Component>& component)
{
	// ��̃R���|�[�l���g�܂��͌ŗLID�`�F�b�N�Ɉ���������Ȃ��ꍇ�̓L���X�g���s
	if ((component == nullptr) ||
		!component->CheckUniqueID(RuntimeTypeUniqueID::Get<T>()))
	{
		return std::shared_ptr<T>{nullptr};
	}
	return std::static_pointer_cast<T>(component);
}