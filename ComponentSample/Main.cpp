#include <DxLib.h>
#include <string>
#include "Object/Object.h"

class UIObject : public Object
{
public:
	unsigned int GetColor1() const
	{
		return GetColor(255, 255, 0);
	}

	unsigned int GetColor2() const
	{
		return GetColor(255, 0, 255);
	}
};

class Component1 : public Component
{
public:
	virtual void Update() override
	{
		auto color = ObjectDynamicCast<UIObject>(GetOwner().lock())->GetColor1();
		DrawQuadrangle(0, 0, 640 + 30, 0, 640 + 30, 720, 0, 720, color, 1);
	}
};

class Component2 : public Component
{
public:
	virtual void Update() override
	{
		auto color = ObjectDynamicCast<UIObject>(GetOwner().lock())->GetColor2();
		DrawQuadrangle(640 - 30, 0, 1280, 0, 1280, 720, 640 - 30, 720, color, 1);
	}
};

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	// ��ʃ��[�h�̃Z�b�g
	SetGraphMode(1280, 720, 16);
	ChangeWindowMode(TRUE);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		// �G���[���N�����璼���ɏI��
		return -1;
	}

	std::shared_ptr<UIObject> object = Object::Create<UIObject>();

	object->AddComponent<Component1>("1");
	object->AddComponent<Component2>("2");

	// ���C�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ��ʂ�����������
		ClearDrawScreen();

		object->UpdateComponents();

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();
	}

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}
