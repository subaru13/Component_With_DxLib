#include <DxLib.h>
#include <string>
#include "Object/Object.h"

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

	std::shared_ptr<Object> object = std::make_shared<Object>();

	object->AddComponent<Component>();

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
