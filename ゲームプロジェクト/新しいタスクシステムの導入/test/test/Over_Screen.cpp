//-------------------------------
//Over_screen.cpp
//-------------------------------
//ヘッダーファイル
#include"Over_Screen.h"

//コンストラクタ
COverScreen::COverScreen() {
	m_state = OVER_SCREEN;
	m_Timer = 0;
	TaskManager::Instance()->GuardKillTask();
	//CControlSound::GetInstance()->CreateBGM(BGM::TITLE);
}

//デストラクタ
COverScreen::~COverScreen() {
}

//実行処理
void COverScreen::Update() {
	TaskManager::Instance()->Update();
	/*try
	{
		TaskManager::Instance()->RunTask();
	}
	catch (int menu)
	{
		if (0) {
			TaskManager::Instance()->DethTask();
			TaskManager::Instance()->DeleteDeathTask();
			m_state = TITLE_SCREEN;
		}
	}*/

#if defined(_DEBUG)|defined(DEBUG)
	if (CheckHitKey(KEY_INPUT_Z)) {
		TaskManager::Instance()->GuardKillTask();
		m_state = TITLE_SCREEN;
	}
#endif
}

//描画処理
void COverScreen::Draw()const {
	ClearDrawScreen();
	TaskManager::Instance()->Draw();
	clsDx();
#if defined(_DEBUG)|defined(DEBUG)
	clsDx();
	DrawString(10, 100, "Over Screen Hit Z key to GameTitle Screen", GetColor(255, 255, 255));
#endif
}
