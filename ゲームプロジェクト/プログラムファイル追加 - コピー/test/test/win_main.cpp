//***************
// win_main.cpp
//***************
#include "mylib.h"
#include "game.h"

//------------
//ローカル変数
//------------
CGame*	g_pMain = NULL;

//---------------
//ローカル関数
//---------------
void	win_main_init();
void	win_main_loop();
void	win_main_dest();

//---------------
//ウィンドウ画面のメイン
//---------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	double dNextTime = GetNowCount();
	SetWindowIconID(IDI_ICON2);
	win_main_init();

	while (!ProcessMessage()) {
		dNextTime += FRAMETIME_MS;
		if (dNextTime > GetNowCount()) {			//60FPS処理
			WaitTimer((int)dNextTime - GetNowCount());
		}
		win_main_loop();
#if defined(_DEBUG) | defined(DEBUG)
		if (CheckHitKey(KEY_INPUT_ESCAPE))break;
#endif
	}
	//コンソールを閉じる
	FreeConsole();
	win_main_dest();
}

//-------------
//メイン初期化処理
//-------------
void win_main_init()
{
	//DirectX関係

	ChangeWindowMode(WINDOW_SCREEN);
	if (WINDOW_SCREEN)
	{
		SetGraphMode(WINDOW_W, WINDOW_H, 32);
		SetMainWindowText(_T("test"));
	}
	if (DxLib_Init() == -1)//ライブラリの初期化処理
		return;

	RANDMIZE();
	SetDrawScreen(DX_SCREEN_BACK);

#if defined(_DEBUG) | defined(DEBUG)
	if (MessageBox(NULL, "デバッグ情報を表示しますか？", "デバッグ情報の表示確認", MB_YESNO) == IDYES) {
		DebugModeOn();
	}
#endif

	//GAME関係
	g_pMain = new CGame();

}
//-------------
//メインループ処理
//--------------
void win_main_loop()
{	
	//メイン処理
	g_pMain->Update();
	g_pMain->Draw();
	ScreenFlip();
}

//----------------
//メイン終了処理
//----------------
void win_main_dest()
{
	delete g_pMain;
	g_pMain = NULL;
}