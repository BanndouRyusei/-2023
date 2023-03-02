//-------------------------------
//Clear_screen.cpp
//-------------------------------
//ヘッダーファイル
#include"Clear_Screen.h"
#include"Task.h"
#include"TaskSystemEx.h"

//コンストラクタ
CClearScreen::CClearScreen() {
	m_state = CLEAR_SCREEN;
	m_Timer = 0;
	TaskEx::DethTask();
	//CControlSound::GetInstance()->CreateBGM(BGM::TITLE);
}

//デストラクタ
CClearScreen::~CClearScreen() {
}

//実行処理
void CClearScreen::Update() {
	TaskEx::RunTask();
	/*try
	{
		TaskEx::RunTask();
	}
	catch (int menu)
	{
		if (0) {
			TaskEx::DethTask();
			TaskEx::DeleteDeathTask();
			m_state = TITLE_SCREEN;
		}
	}*/

	if (m_Timer++%MAX_FPS == 0) TaskEx::DeleteDeathTask();//不要タスクの消去

#if defined(_DEBUG)|defined(DEBUG)
	if (CheckHitKey(KEY_INPUT_Z)) {
		TaskEx::DethTask();
		TaskEx::DeleteDeathTask();
		m_state = TITLE_SCREEN;
	}
#endif
}

//描画処理
void CClearScreen::Draw()const {
	ClearDrawScreen();
	TaskEx::DrawTask();
	clsDx();
#if defined(_DEBUG)|defined(DEBUG)
	clsDx();
	DrawString(10, 100, "Clear Screen Hit Z key to GameTitle Screen", GetColor(255, 255, 255));
#endif
}