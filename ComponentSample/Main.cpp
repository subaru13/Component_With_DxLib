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
	// 画面モードのセット
	SetGraphMode(1280, 720, 16);
	ChangeWindowMode(TRUE);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		// エラーが起きたら直ちに終了
		return -1;
	}

	std::shared_ptr<UIObject> object = Object::Create<UIObject>();

	object->AddComponent<Component1>("1");
	object->AddComponent<Component2>("2");

	// メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// 画面を初期化する
		ClearDrawScreen();

		object->UpdateComponents();

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();
	}

	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}
