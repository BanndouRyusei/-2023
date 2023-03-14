//----------------------
//gametitle_screen.cpp
//----------------------

//ヘッダーファイル
#include"Title_screen.h"

//コンストラクタ
CTitleScreen::CTitleScreen() {
	m_state = TITLE_SCREEN;
	m_Timer = 0;
	CTaskManager::Instance()->GuardKillTask();
	//CControlSound::GetInstance()->CreateBGM(BGM::TITLE);
}

//デストラクタ
CTitleScreen::~CTitleScreen() {}

//実行処理
void CTitleScreen::Update() {
	CTaskManager::Instance()->Update();
	//CTaskManager::Instance()->UpdateDrawPriority();
	/*try {
		CTaskManager::Instance()->RunTask();
	}
	catch (int menu) {
		switch (0)
		{
		case 0:
			CTaskManager::Instance()->DethTask();	
			CTaskManager::Instance()->DeleteDeathTask();
			m_state = GAME_SCREEN;
			break;
		case 1:			//強制終了
			CTaskManager::Instance()->GuardDethTask();
			exit(0);
			break;
		default:
			assert(false);
		}
	}*/
#if defined( _DEBUG ) | defined( DEBUG )
	if (CheckHitKey(KEY_INPUT_E)) {
		CTaskManager::Instance()->GuardKillTask();
		m_state = GAME_SCREEN;
	}
#endif
}

//描画
void CTitleScreen::Draw() const
{
	ClearDrawScreen();
	CTaskManager::Instance()->Draw();
	clsDx();

#if defined( _DEBUG) | defined( DEBUG )
	clsDx();
	DrawString(10, 100, "GameTitle Screen Hit E key to Game Screen", GetColor(255, 255, 255));
#endif
}