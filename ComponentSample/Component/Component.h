#pragma once
#include <type_traits>
#include <concepts>
#include <memory>
#include <string>
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
		継承先で以下のように継承元の型として
		チェックを成功させる事ができるので仮想化

		class ComponentA : public Component;

		class ComponentB : public ComponentA
		{
		public:
			bool CheckUniqueID(TypeUniqueID typeUniqueID) const override
			{
				return RuntimeTypeUniqueID::Get<ComponentB>() == typeUniqueID ||
					Component::CheckUniqueID(typeUniqueID);
			}
		};

	*/
	virtual bool CheckUniqueID(TypeUniqueID typeUniqueID) const;

	virtual void Update();

	const std::string& GetName() const;

	virtual ~Component() = default;
protected:
	const std::weak_ptr<Object>& GetOwner() const;
	const TypeUniqueID& GetTypeUniqueID() const;
private:
	std::weak_ptr<Object> mOwner;
	TypeUniqueID mTypeUniqueID{};
	std::string mName{};
private:
	friend ComponentContainer;
	void SetComponentInfo(
		const std::weak_ptr<Object>& owner,
		TypeUniqueID typeUniqueID,
		const std::string& name);
};

template<class T>
concept ComponentType = std::is_same_v<Component, T> || (std::is_base_of_v<Component, T> && std::constructible_from<T>);

template<ComponentType T>
static std::shared_ptr<T> ComponentDynamicCast(const std::shared_ptr<Component>& component)
{
	// 空のコンポーネントまたは固有IDチェックに引っかからない場合はキャスト失敗
	if ((component == nullptr) ||
		!component->CheckUniqueID(UNIQUE_ID_OF(T)))
	{
		return std::shared_ptr<T>{nullptr};
	}
	return std::static_pointer_cast<T>(component);
}