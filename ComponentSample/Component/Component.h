#pragma once
#include <type_traits>
#include <concepts>
#include <memory>

class Object;
class ComponentContainer;

/*
	RTTIのかわりの実行時型固有ID
	2^16個IDを作成することができるので
	足りなくなることはないと思うが
	足りなくなったら拡張する
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
	// 空のコンポーネントまたは固有IDチェックに引っかからない場合はキャスト失敗
	if ((component == nullptr) ||
		!component->CheckUniqueID(RuntimeTypeUniqueID::Get<T>()))
	{
		return std::shared_ptr<T>{nullptr};
	}
	return std::static_pointer_cast<T>(component);
}