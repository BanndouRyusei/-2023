//------------------
//game_screen.cpp
//------------------

//ヘッダーファイル
#include"Game_screen.h"
#include"Stage.h"
#include"Player.h"
#include "Enemy.h"
#include"UI.h"
#include"ShadowManager.h"

//コンストラクタ
CGameScreen::CGameScreen()
{
	g_Score = 0;
	m_state = GAME_SCREEN;
	m_timer = 0;
	CTaskManager::Instance()->GuardKillTask();
	new CStage(0.1f);
	new CShadowManager();
	new CUI(2.1f);
	new CHP(2.1f);
	new CLife(2.1f);
	new CTime(2.1f);
	new CScore(2.1f);
	new CControlPlayer(0.1f);
	new CControlEnemy(0.2f);
	CControlSound::GetInstance()->CreateBGM(e_BGM::GAME);
}

//デストラクタ
CGameScreen::~CGameScreen() {}

//更新処理
void CGameScreen::Update()
{

	try {
		CTaskManager::Instance()->Update();			//タスクの更新
	}
	catch (CAST menu) {
		switch (menu)
		{
		case CAST::GAMECLEAR:
			CTaskManager::Instance()->GuardKillTask();
			m_state = CLEAR_SCREEN;
			break;
		case CAST::GAMEOVER:
			CTaskManager::Instance()->GuardKillTask();
			m_state = OVER_SCREEN;
			break;
		case CAST::NONE:
		default:
			assert(false);
			break;
		}
	}
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
