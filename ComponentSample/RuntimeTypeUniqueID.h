#pragma once

/*
	RTTIのかわりの実行時型固有ID
	2^16個IDを作成することができるので
	足りなくなることはないと思うが
	足りなくなったら拡張する
*/
class RuntimeTypeUniqueID final
{
public:
	using Value = unsigned short;
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

#define UNIQUE_ID_OF(T) RuntimeTypeUniqueID::Get<T>()
