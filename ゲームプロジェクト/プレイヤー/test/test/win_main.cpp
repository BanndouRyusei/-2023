//***************
// win_main.cpp
//***************
#include "mylib.h"
#include "game.h"

//------------
//���[�J���ϐ�
//------------
CGame*	g_pMain = NULL;

//---------------
//���[�J���֐�
//---------------
void	win_main_init();
void	win_main_loop();
void	win_main_dest();

//---------------
//�E�B���h�E��ʂ̃��C��
//---------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	double dNextTime = GetNowCount();
	SetWindowIconID(IDI_ICON2);
	win_main_init();

	while (!ProcessMessage()) {
		dNextTime += FRAMETIME_MS;
		if (dNextTime > GetNowCount()) {			//60FPS����
			WaitTimer((int)dNextTime - GetNowCount());
		}
		win_main_loop();
#if defined(_DEBUG) | defined(DEBUG)
		if (CheckHitKey(KEY_INPUT_ESCAPE))break;
#endif
	}
	//�R���\�[�������
	FreeConsole();
	win_main_dest();
}

//-------------
//���C������������
//-------------
void win_main_init()
{
	//DirectX�֌W

	ChangeWindowMode(WINDOW_SCREEN);
	if (WINDOW_SCREEN)
	{
		SetGraphMode(WINDOW_W, WINDOW_H, 32);
		SetMainWindowText(_T("test"));
	}
	if (DxLib_Init() == -1)//���C�u�����̏���������
		return;

	RANDMIZE();
	SetDrawScreen(DX_SCREEN_BACK);

#if defined(_DEBUG) | defined(DEBUG)
	if (MessageBox(NULL, "�f�o�b�O����\�����܂����H", "�f�o�b�O���̕\���m�F", MB_YESNO) == IDYES) {
		DebugModeOn();
	}
#endif

	//GAME�֌W
	g_pMain = new CGame();

}
//-------------
//���C�����[�v����
//--------------
void win_main_loop()
{	
	//���C������
	g_pMain->Update();
	g_pMain->Draw();
	ScreenFlip();
}

//----------------
//���C���I������
//----------------
void win_main_dest()
{
	delete g_pMain;
	g_pMain = NULL;
}