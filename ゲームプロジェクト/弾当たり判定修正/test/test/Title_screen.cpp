//----------------------
//gametitle_screen.cpp
//----------------------

//ヘッダーファイル
#include"Title_screen.h"
#include"Title.h"

//コンストラクタ
CTitleScreen::CTitleScreen() {
	m_state = TITLE_SCREEN;
	m_Timer = 0;
	CTaskManager::Instance()->GuardKillTask();
	new CTitle(0.1f);
	CControlSound::GetInstance()->CreateBGM(e_BGM::TITLE);
}

//デストラクタ
CTitleScreen::~CTitleScreen() {}

//実行処理
void CTitleScreen::Update() {
	try {
		CTaskManager::Instance()->Update();
	}
	catch (int menu) {
		switch (menu)
		{
		case 0:
			CTaskManager::Instance()->GuardKillTask();
			m_state = GAME_SCREEN;
			break;
		case 1:			//強制終了
			CTaskManager::Instance()->GuardKillTask();
			exit(0);
			break;
		default:
			assert(false);
		}
	}
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
	clsDx();
	ClearDrawScreen();
	CTaskManager::Instance()->Draw();

#if defined( _DEBUG) | defined( DEBUG )
	clsDx();
	DrawString(10, 100, "GameTitle Screen Hit E key to Game Screen", GetColor(255, 255, 255));
#endif
}