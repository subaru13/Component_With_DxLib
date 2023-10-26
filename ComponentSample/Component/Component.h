#pragma once
#include <type_traits>
#include <concepts>
#include <memory>
#include "../RuntimeTypeUniqueID.h"

class Object;
class ComponentContainer;

class Component
{
public:
	using TypeUniqueID = RuntimeTypeUniqueID::Value;

public:
	Component() = default;

	/*
		�p����ňȉ��̂悤�Ɍp�����̌^�Ƃ���
		�`�F�b�N�𐬌������鎖���ł���̂�
		���z��

		class ComponentA : public Component
		{
			public:
			bool CheckUniqueID(TypeUniqueID typeUniqueID) const override
			{
				return GetTypeUniqueID() == typeUniqueID ||Component::CheckUniqueID(typeUniqueID) ;
			}
		};
	*/
	virtual bool CheckUniqueID(TypeUniqueID typeUniqueID) const;

	virtual void Update();

	virtual ~Component() = default;
protected:
	const std::weak_ptr<Object>& GetOwner() const;
	const TypeUniqueID& GetTypeUniqueID() const;
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