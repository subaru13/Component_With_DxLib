#pragma once

/*
	RTTI�̂����̎��s���^�ŗLID
	2^16��ID���쐬���邱�Ƃ��ł���̂�
	����Ȃ��Ȃ邱�Ƃ͂Ȃ��Ǝv����
	����Ȃ��Ȃ�����g������
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