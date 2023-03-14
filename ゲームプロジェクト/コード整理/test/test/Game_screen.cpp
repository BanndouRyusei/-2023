//------------------
//game_screen.cpp
//------------------

//ヘッダーファイル
#include"Game_screen.h"
#include"Stage.h"
#include"Player.h"
#include "Enemy.h"

//コンストラクタ
CGameScreen::CGameScreen()
{
	m_state = GAME_SCREEN;
	m_timer = 0;
	CTaskManager::Instance()->GuardKillTask();
	new CStage(0.1f);
	new CControlPlayer(0.1f);
	new CEnemyZakoA(1000.0, 20.0, 1, 0.2);
	//CControlSound::GetInstance()->CreateBGM(BGM::TITLE);
}

//デストラクタ
CGameScreen::~CGameScreen() {}

//更新処理
void CGameScreen::Update()
{
	CTaskManager::Instance()->Update();			//タスクの更新
	/*try {
		CTaskManager::Instance()->RunTask();			//タスクの更新
	}
	catch (int menu) {
		if (0) {
			CTaskManager::Instance()->DethTask();		//生きているタスクの終了処理
			CTaskManager::Instance()->DeleteDeathTask();
			m_state = CLEAR_SCREEN;
		}
	}*/
	//if (m_timer%MAX_FPS == 0)CTaskManager::Instance()->DeleteDeathTask();//不要タスクの削除
#if defined(_DEBUG) | defined(DEBUG)
	if (CheckHitKey(KEY_INPUT_F)) {
		CTaskManager::Instance()->GuardKillTask();
		m_state = CLEAR_SCREEN;
	}
	if (CheckHitKey(KEY_INPUT_G)) {
		CTaskManager::Instance()->GuardKillTask();
		m_state = OVER_SCREEN;
	}
#endif
}

//描画処理
void CGameScreen::Draw() const
{
	clsDx();
	ClearDrawScreen();
	CTaskManager::Instance()->Draw();

#if defined(_DEBUG)|(DEBUG)
	DrawString(10, 100, "Game Screen Hit F key to GameClear Screen Hit G key to GameOver Screen", GetColor(255, 255, 255));
#endif
}
