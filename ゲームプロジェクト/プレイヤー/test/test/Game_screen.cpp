//------------------
//game_screen.cpp
//------------------

//ヘッダーファイル
#include"Game_screen.h"
#include"Stage.h"
#include"Player.h"


//コンストラクタ
CGameScreen::CGameScreen()
{
	m_state = GAME_SCREEN;
	m_timer = 0;
	TaskManager::Instance()->GuardKillTask();
	new CStage(0.1f);
	new CControlPlayer(0.1f);
	//CControlSound::GetInstance()->CreateBGM(BGM::TITLE);
}

//デストラクタ
CGameScreen::~CGameScreen() {}

//更新処理
void CGameScreen::Update()
{
	TaskManager::Instance()->Update();			//タスクの更新
	/*try {
		TaskManager::Instance()->RunTask();			//タスクの更新
	}
	catch (int menu) {
		if (0) {
			TaskManager::Instance()->DethTask();		//生きているタスクの終了処理
			TaskManager::Instance()->DeleteDeathTask();
			m_state = CLEAR_SCREEN;
		}
	}*/
	//if (m_timer%MAX_FPS == 0)TaskManager::Instance()->DeleteDeathTask();//不要タスクの削除
#if defined(_DEBUG) | defined(DEBUG)
	if (CheckHitKey(KEY_INPUT_F)) {
		TaskManager::Instance()->GuardKillTask();
		m_state = CLEAR_SCREEN;
	}
	if (CheckHitKey(KEY_INPUT_G)) {
		TaskManager::Instance()->GuardKillTask();
		m_state = OVER_SCREEN;
	}
#endif
}

//描画処理
void CGameScreen::Draw() const
{
	ClearDrawScreen();
	TaskManager::Instance()->Draw();
	clsDx();

#if defined(_DEBUG)|(DEBUG)
	DrawString(10, 100, "Game Screen Hit F key to GameClear Screen Hit G key to GameOver Screen", GetColor(255, 255, 255));
#endif
}
