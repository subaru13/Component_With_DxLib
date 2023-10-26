#pragma once

/*
	RTTI‚Ì‚©‚í‚è‚ÌÀsŒ^ŒÅ—LID
	2^16ŒÂID‚ğì¬‚·‚é‚±‚Æ‚ª‚Å‚«‚é‚Ì‚Å
	‘«‚è‚È‚­‚È‚é‚±‚Æ‚Í‚È‚¢‚Æv‚¤‚ª
	‘«‚è‚È‚­‚È‚Á‚½‚çŠg’£‚·‚é
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